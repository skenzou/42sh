/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 23:37:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/14 06:28:37 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_ast *newnode(t_token *token, t_list *pointer)
{
	t_ast *node =  (t_ast *)malloc(sizeof(t_ast));

	if (token)
	{
		node->token = token;
	}
	else
		node->token = NULL;
	node->left = node->right = NULL;
	node->list_pointer = pointer;
	return node;
}
int		is_in_lexer(t_list *lexer, e_op_type optype)
{
	t_token *token;

	while (lexer)
	{
		token = (t_token *)(lexer->content);
		if (token->op_type == optype)
			return (1);
		lexer = lexer->next;
	}
	return (0);
}


void	build_tree_op(t_list *lexer, t_ast **root, e_op_type optype)
{
	t_list *save2;
	t_list *save1;
	t_list *origin;
	t_token *token;
	t_list *prev;

	save2 = NULL;
	save1 = NULL;
	origin= lexer;

	if (!lexer)
		return ;
	prev = lexer;
	while(lexer)
	{
		token = (t_token*)(lexer->content);
		//printf("test: %s\n", token->content);
		if (token->op_type == optype)
		{
			save1 = prev;
			save2 = lexer->next;
		}
		prev = lexer;
		lexer = lexer->next;
	}
	prev = save1;
	if (save1)
		save1 = save1->next;
	if (prev)
		prev->next = NULL;
	if (!is_in_lexer(origin, optype) && !save1)
	{
				if (is_in_lexer(origin, DBL_AND))
					build_tree_op(origin, root, DBL_AND);
				else if (is_in_lexer(origin, DBL_PIPE))
					build_tree_op(origin, root, DBL_PIPE);
				else if (is_in_lexer(origin, PIPE))
					build_tree_op(origin, root, PIPE);
				else
					*root = newnode((t_token *)(origin->content), origin);
	}
	if (save1)
	{
		//	printf("1 / %s -- 2 / %s\n",((t_token *)(save1->content))->content, ((t_token *)(save2->content))->content);
			*root = newnode((t_token *)(save1->content), save1);
			if (save2)
			{
				if (is_in_lexer(save2, DBL_AND))
					build_tree_op(save2, &((*root)->right), DBL_AND);
				else if (is_in_lexer(save2, DBL_PIPE))
					build_tree_op(save2, &((*root)->right), DBL_PIPE);
				else if (is_in_lexer(save2, PIPE))
					build_tree_op(save2, &((*root)->right), PIPE);
				else
					(*root)->right = newnode((t_token *)(save2->content), save2);
			}
			build_tree_op(origin, &((*root)->left) , optype);
	}
}


void print_ast(t_ast *root,char *str)
{
  int ret;
	size_t i;

  ret = ft_strcmp(str, "root");
  if (!ret)
    ft_printf("============================AST=============================\n");
	if (root != NULL)
	{
		print_ast(root->left,ft_strjoin(str , " - > left"));
		if (root->token)
		{
			i = 0;
			while (i < root->token->size)
				ft_printf("%s ", root->token->content[i++]);
			ft_printf("--- %s\n", str);
		}
		print_ast(root->right,ft_strjoin(str ,"- > right"));
	}
  if (!ret)
    ft_printf("============================================================\n");
	ft_strdel(&str);
}

void ast (t_list *lexer, t_ast **root, e_op_type optype)
{
//	if (is_in_lexer(lexer, optype))
		*root = NULL;
		build_tree_op(lexer, root, optype);
//	if (root->left)
//		ast(lexer, root->left, optype);
}




/*
** Cherche si un erreur de syntax existing_token
** Renvoie une erreur si un TOKEN_REDIR est pas suivie d'un TOKEN_WORD ou
** si deux TOKEN_CTL_OPERATOR se suivent (pour l'instant)
*/

char		*check_syntax_errors(t_list *tokens)
{
  t_token *curr;
  t_token *next;

	if (tokens && ((t_token *)(tokens->content))->type == TOKEN_CTL_OPERATOR)
		return (((t_token *)(tokens->content))->content[0]);
	while (tokens && tokens->next)
	{
		curr = (t_token *)(tokens->content);
		next = (t_token *)(tokens->next->content);
		if (curr->type == TOKEN_REDIR && next->type != TOKEN_WORD)
			return (next->content[0]);
		if (curr->type == TOKEN_CTL_OPERATOR && next->type == TOKEN_CTL_OPERATOR)
			return (next->content[0]);
		tokens = tokens->next;
	}
	curr = (t_token *)(tokens->content);
	if (curr->type == TOKEN_REDIR)
		return "\\n";
	return (NULL);
}

static void		exec_inhib(char inhib, t_list *lexer)
{
	(void)inhib;
	(void)lexer;
}

static void		check_inhib(char *str, t_list *lexer)
{
	char inhib;

	while (*str)
	{
		if (*str == DQUOTE || *str == QUOTE || *str == BSLASH)
		{
			inhib = *str++;
			while (*str && *str != inhib)
				str++;
			if (!*str)
			{
				exec_inhib(inhib, lexer);
				return ;
			}
		}
		str++;
	}
}

void			handle_inhibitors(t_list *lexer)
{
	t_token *token;
	size_t i;

	while (lexer)
	{
		token = (t_token *)lexer->content;
		if (token->type == TOKEN_WORD)
		{
			i = 0;
			while (i < token->size)
			{
				check_inhib(token->content[0], lexer);
				i++;
			}
		}
		lexer = lexer->next;
	}
}

//  void		join_redir(t_list *lexer)
// {
// 	t_token *left;
// 	t_token *redir;
// 	t_token *right;
// 	char	*temp;
// 	t_list	*save_to_destroy;
//
// 	left = (t_token *)lexer->content;
// 	redir = (t_token *)lexer->next->content;
// 	right = (t_token *)lexer->next->next->content;
// 	left->redir = 1;
// 	temp = left->content;
// 	left->content = ft_strcjoin(left->content, redir->content, ' ');
// 	ft_strdel(&temp);
// 	temp = left->content;
// 	left->content = ft_strcjoin(left->content, right->content, ' ');
// 	ft_strdel(&temp);
// 	save_to_destroy = lexer->next;
// 	lexer->next = lexer->next->next->next;
// 	ft_lstdelone(&(save_to_destroy->next), lex_delone);
// 	ft_lstdelone(&(save_to_destroy), lex_delone);
// }

static void		join_2(t_list *lexer)
{
	t_token *curr;
	t_token *next;
	t_list *tmp;

	curr = (t_token *)lexer->content;
	next = (t_token *)lexer->next->content;
	curr->type = TOKEN_WORD;
	if (curr->type == TOKEN_REDIR || next->type == TOKEN_REDIR)
		curr->redir = 1;
	tmp = lexer->next;
	lexer->next = tmp->next;
	curr->content = join_2tab(curr->content, next->content, curr->size, next->size);
	curr->size = curr->size + next->size;
	ft_lstdelone(&tmp, lex_delone);
}

static void		join_all_redir(t_list *lexer)
{
	t_token *curr;
	t_token *next;

	while (lexer && lexer->next)
	{
		curr = (t_token *)lexer->content;
		next = (t_token *)lexer->next->content;
		if ((curr->type == TOKEN_WORD || curr->type == TOKEN_REDIR)
			&& (next->type == TOKEN_WORD || next->type == TOKEN_REDIR))
		{
			join_2(lexer);
			continue ;
		}
		lexer = lexer->next;
	}
}

static void		create_redir(t_list **redirs, char **dest, size_t size, e_op_type redir_type)
{
	t_redir redir;
	t_list *node;

	redir.dest = dup_tab(dest, size);
	redir.op_type = redir_type;
	if (redir_type == OTHER_OP)
		redir.end_of_leaf = 1;
	else
		redir.end_of_leaf = 0;
	node = ft_lstnew((void *)&redir, sizeof(redir));
	if (!node)
		ft_exit("Failed to malloc a node for my redir list");
	ft_lstadd(redirs, node);
}

static t_list		*get_next_redir(t_list *lexer)
{
	t_list *save;
	t_token *curr;

	save = lexer;
	while(lexer)
	{
		curr = (t_token *)lexer->content;
		if (curr->type == TOKEN_REDIR)
			return (save);
		else if (curr->type == TOKEN_CTL_OPERATOR)
			save = lexer->next;
		lexer = lexer->next;
	}
	return (NULL);
}

static t_list		*handle_redir(t_list *lexer)
{
	t_list *redir;
	t_token *curr;
	t_token *next;
	char	**cmd;
	t_list	*prev;
	size_t cmd_size;

	redir = NULL;
	prev = NULL;
	cmd = NULL;
	lexer = get_next_redir(lexer);
	while (lexer)
	{
		curr = (t_token *)lexer->content;
		if (curr->type == TOKEN_WORD && !cmd && (!prev || (prev
			&& ((t_token *)prev->content)->type != TOKEN_REDIR)))
			{
				cmd = curr->content;
				cmd_size = curr->size;
			}
		if (curr->type == TOKEN_REDIR)
		{
			next = (t_token *)lexer->next->content;
			create_redir(&redir, next->content, next->size, curr->op_type);
		}
		else if (curr->type == TOKEN_CTL_OPERATOR
			|| (curr->type != TOKEN_CTL_OPERATOR && !lexer->next))
		{
			create_redir(&redir, cmd, cmd_size, OTHER_OP);
			cmd = NULL;
			lexer = get_next_redir(lexer);
			prev = NULL;
			continue ;
		}
		prev = lexer;
		lexer = lexer->next;
	}
	ft_lstrev(&redir);
	return (redir);
}


t_ast  *ft_parse(t_list *lexer, t_list **redir)
{
	char *error;
	t_ast *root;

	if (!lexer)
		return (NULL);
	root = NULL;
	error = check_syntax_errors(lexer);
	if (error)
	{
		ft_putstr_fd(ANSI_RED"21sh: parse error near'", 2);
		ft_putstr_fd(error, 2);
		ft_putendl_fd("'", 2);
		return (NULL);
	}
	handle_inhibitors(lexer);
	*redir = handle_redir(lexer);
  if (g_shell->print_flags & PRINT_REDIR)
    print_redir(*redir);
	join_all_redir(lexer);
	if (is_in_lexer(lexer, SEMI))
		ast(lexer, &root, SEMI);
	else if (is_in_lexer(lexer, DBL_AND))
		ast(lexer, &root, DBL_AND);
	else if (is_in_lexer(lexer, DBL_PIPE))
		ast(lexer, &root, DBL_PIPE);
	else
		ast(lexer, &root, PIPE);
	if (g_shell->print_flags & PRINT_AST)
		print_ast(root, ft_strdup("root"));
	return root;
}
