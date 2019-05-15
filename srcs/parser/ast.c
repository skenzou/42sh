/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 01:18:26 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/15 03:42:27 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		del_one_ast(t_ast *root)
{
	ft_lstdelone(&root->list_pointer, lex_delone);
	free(root);
}

void 		del_ast(t_ast **root)
{
	if (!(*root))
		return ;
	if ((*root)->left)
		del_ast(&(*root)->left);
	if ((*root)->right)
		del_ast(&(*root)->right);
	del_one_ast(*root);
	*root = NULL;
}

t_ast *newnode(t_token *token, t_list *pointer)
{
	t_ast *node;

	if (!(node =  (t_ast *)ft_memalloc(sizeof(t_ast))))
		ft_exit("Malloc failed in newnode");
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
