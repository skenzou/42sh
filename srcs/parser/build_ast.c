/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 01:28:47 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/24 14:23:15 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	build_ast(t_list *lexer, t_ast **root, e_op_type optype)
{
	t_list *save2;
	t_list *save1;
	t_list *origin;
	t_token *token;
	t_list *prev;

	save2 = NULL;
	save1 = NULL;
	origin = lexer;
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
					build_ast(origin, root, DBL_AND);
				else if (is_in_lexer(origin, DBL_PIPE))
					build_ast(origin, root, DBL_PIPE);
				else if (is_in_lexer(origin, PIPE))
					build_ast(origin, root, PIPE);
				else
					*root = newnode((t_token *)(origin->content), origin);
	}
	if (save1)
	{
			*root = newnode((t_token *)(save1->content), save1);
			if (save2)
			{
				if (is_in_lexer(save2, DBL_AND))
					build_ast(save2, &((*root)->right), DBL_AND);
				else if (is_in_lexer(save2, DBL_PIPE))
					build_ast(save2, &((*root)->right), DBL_PIPE);
				else if (is_in_lexer(save2, PIPE))
					build_ast(save2, &((*root)->right), PIPE);
				else
					(*root)->right = newnode((t_token *)(save2->content), save2);
			}
			build_ast(origin, &((*root)->left) , optype);
	}
}
