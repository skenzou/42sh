/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:51:02 by midrissi          #+#    #+#             */
/*   Updated: 2019/11/09 16:03:34 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const t_oplist g_existing_token[] =
{
	{">>-", 3, TOKEN_REDIR, DBL_GREAT_DASH},
	{"<<-", 3, TOKEN_REDIR, DBL_LESS_DASH},
	{"0>&", 3, TOKEN_REDIR, GREAT_AND},
	{"1>&", 3, TOKEN_REDIR, GREAT_AND},
	{"2>&", 3, TOKEN_REDIR, GREAT_AND},
	{"3>&", 3, TOKEN_REDIR, GREAT_AND},
	{"4>&", 3, TOKEN_REDIR, GREAT_AND},
	{"5>&", 3, TOKEN_REDIR, GREAT_AND},
	{"6>&", 3, TOKEN_REDIR, GREAT_AND},
	{"7>&", 3, TOKEN_REDIR, GREAT_AND},
	{"8>&", 3, TOKEN_REDIR, GREAT_AND},
	{"9>&", 3, TOKEN_REDIR, GREAT_AND},
	{"0<&", 3, TOKEN_REDIR, LESS_AND},
	{"1<&", 3, TOKEN_REDIR, LESS_AND},
	{"2<&", 3, TOKEN_REDIR, LESS_AND},
	{"3<&", 3, TOKEN_REDIR, LESS_AND},
	{"4<&", 3, TOKEN_REDIR, LESS_AND},
	{"5<&", 3, TOKEN_REDIR, LESS_AND},
	{"6<&", 3, TOKEN_REDIR, LESS_AND},
	{"7<&", 3, TOKEN_REDIR, LESS_AND},
	{"8<&", 3, TOKEN_REDIR, LESS_AND},
	{"9<&", 3, TOKEN_REDIR, LESS_AND},
	{"&>", 2, TOKEN_WORD, OTHER_OP},
	{"0>", 2, TOKEN_REDIR, GREAT},
	{"1>", 2, TOKEN_REDIR, GREAT},
	{"2>", 2, TOKEN_REDIR, GREAT},
	{"3>", 2, TOKEN_REDIR, GREAT},
	{"4>", 2, TOKEN_REDIR, GREAT},
	{"5>", 2, TOKEN_REDIR, GREAT},
	{"6>", 2, TOKEN_REDIR, GREAT},
	{"7>", 2, TOKEN_REDIR, GREAT},
	{"8>", 2, TOKEN_REDIR, GREAT},
	{"9>", 2, TOKEN_REDIR, GREAT},
	{"0<", 2, TOKEN_REDIR, LESS},
	{"1<", 2, TOKEN_REDIR, LESS},
	{"2<", 2, TOKEN_REDIR, LESS},
	{"3<", 2, TOKEN_REDIR, LESS},
	{"4<", 2, TOKEN_REDIR, LESS},
	{"5<", 2, TOKEN_REDIR, LESS},
	{"6<", 2, TOKEN_REDIR, LESS},
	{"7<", 2, TOKEN_REDIR, LESS},
	{"8<", 2, TOKEN_REDIR, LESS},
	{"9<", 2, TOKEN_REDIR, LESS},
	{">>", 2, TOKEN_REDIR, DBL_GREAT},
	{"<<", 2, TOKEN_REDIR, DBL_LESS},
	{"||", 2, TOKEN_CTL_OPERATOR, DBL_PIPE},
	{">|", 2, TOKEN_REDIR, CLOBBER},
	{"<>", 2, TOKEN_REDIR, LESS_GREAT},
	{"<&", 2, TOKEN_REDIR, LESS_AND},
	{">&", 2, TOKEN_REDIR, GREAT_AND},
	{"&&", 2, TOKEN_CTL_OPERATOR, DBL_AND},
	{";;", 2, TOKEN_CTL_OPERATOR, DBL_SEMI},
	{"|", 1, TOKEN_CTL_OPERATOR, PIPE},
	{"&", 1, TOKEN_CTL_OPERATOR, AND},
	{">", 1, TOKEN_REDIR, GREAT},
	{"<", 1, TOKEN_REDIR, LESS},
	{";", 1, TOKEN_CTL_OPERATOR, SEMI},
	{" ", 1, TOKEN_EAT, OTHER_OP},
	{"\n", 1, TOKEN_EAT, OTHER_OP},
	{"\v", 1, TOKEN_EAT, OTHER_OP},
	{"\t", 1, TOKEN_EAT, OTHER_OP},
	{"\r", 1, TOKEN_EAT, OTHER_OP},
	{"\f", 1, TOKEN_EAT, OTHER_OP},
	{NULL, 1, 0, OTHER_OP}
};

static int			join_if_2words(t_list **lexer, char *str, t_token_type type)
{
	t_token		*token;
	size_t		i;

	i = 0;
	if (type == TOKEN_WORD && *lexer &&
		((t_token *)((*lexer)->content))->type == TOKEN_WORD && (!(*lexer)->next
		|| ((t_token *)(((*lexer)->next)->content))->type != TOKEN_REDIR))
	{
		token = (t_token *)(*lexer)->content;
		token->content = realloc_new_tab(str, token->content, token->size);
		token->size++;
		return (1);
	}
	return (0);
}

static void			create_token(t_list **lexer, char *str,
										t_token_type type, t_op_type op_type)
{
	t_token		token;
	t_list		*list;

	if (!str)
		ft_exit("Malloc fail");
	if (join_if_2words(lexer, str, type))
		return ;
	if (op_type == SEMI && (*lexer == NULL || (*lexer &&
		((t_token *)((*lexer)->content))->op_type == SEMI)))
	{
		free(str);
		return ;
	}
	if (!(token.content = (char **)ft_memalloc((sizeof(char *) * 2))))
		ft_exit("Malloc failed in create_token");
	token.content[0] = str;
	token.content[1] = NULL;
	token.size = 1;
	token.type = type;
	token.is_op = op_type != OTHER_OP;
	token.op_type = op_type;
	token.redir = op_type == TOKEN_REDIR;
	if (!(list = ft_lstnew((void *)&token, sizeof(token))))
		ft_exit("Failed to malloc a node of my lexer list");
	ft_lstadd(lexer, list);
}

t_oplist			check_ops(char *str)
{
	const t_oplist		*curr;
	int					i;

	curr = g_existing_token;
	i = -1;
	while (curr[++i].op)
		if (ft_strncmp(str, curr[i].op, curr[i].len) == 0)
			return (curr[i]);
	return (curr[i]);
}

static void			build_lexer_helper(t_list **lexer,
									t_oplist *curr, char **input, char **prev)
{
	char	quote;

	if (curr->op)
	{
		if (curr->type != TOKEN_EAT)
			create_token(lexer, ft_strdup(curr->op), curr->type, curr->op_type);
		*input += curr->len;
		*prev = *input;
	}
	else if (**input == '\'' || **input == '"')
	{
		quote = *(*input)++;
		while (**input && **input != quote)
		{
			// if (**input == '\\' && *((*input) + 1) == quote)
			// 	(*input) += 2;
			// else
			(*input)++;
		}
		if (**input)
			(*input)++;
	}
	else
		(*input)++;
}

int					build_lexer(char *input, t_list **lexer)
{
	t_oplist	curr;
	char		*prev;

	prev = input;
	while (input && *input)
	{
		if (*input == '\\' && *(input + 1))
			input += 2;
		curr = check_ops(input);
		if ((curr.op) && prev != input)
			create_token(lexer, ft_strsub(prev, 0, input - prev),
														TOKEN_WORD, OTHER_OP);
		build_lexer_helper(lexer, &curr, &input, &prev);
	}
	if (prev != input)
		create_token(lexer, ft_strsub(prev, 0, input - prev),
														TOKEN_WORD, OTHER_OP);
	ft_lstrev(lexer);
	return (1);
}
