/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 01:28:47 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/22 21:33:11 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			op_not_found(t_list *origin, t_ast **root)
{
	if (is_in_lexer(origin, DBL_AND))
		build_ast(origin, root, DBL_AND, OTHER_OP);
	else if (is_in_lexer(origin, DBL_PIPE))
		build_ast(origin, root, DBL_PIPE, OTHER_OP);
	else if (is_in_lexer(origin, PIPE))
		build_ast(origin, root, PIPE, OTHER_OP);
	else
		*root = newnode((t_token *)(origin->content), origin);
}

static int			op_found(t_list *save1, t_list *save2, t_ast **root)
{
	if (save1)
	{
		*root = newnode((t_token *)(save1->content), save1);
		if (save2)
		{
			if (is_in_lexer(save2, DBL_AND))
				build_ast(save2, &((*root)->right), DBL_AND, OTHER_OP);
			else if (is_in_lexer(save2, DBL_PIPE))
				build_ast(save2, &((*root)->right), DBL_PIPE, OTHER_OP);
			else if (is_in_lexer(save2, PIPE))
				build_ast(save2, &((*root)->right), PIPE, OTHER_OP);
			else
				(*root)->right = newnode((t_token *)(save2->content), save2);
		}
		return (1);
	}
	else
		return (0);
}

static void			init_ptrs(t_list **origin, t_list **prev, t_list *lexer)
{
	*origin = lexer;
	*prev = lexer;
}

#define SAVE1 0
#define SAVE2 1
#define ORIGIN 2
#define PREV 3

void				build_ast(t_list *lexer, t_ast **root, t_op_type op1,
															t_op_type op2)
{
	t_list *ptrs[4];

	if (!lexer)
		return ;
	ft_bzero((void *)ptrs, sizeof(ptrs));
	init_ptrs(&ptrs[ORIGIN], &ptrs[PREV], lexer);
	while (lexer)
	{
		if (((t_token*)(lexer->content))->op_type == op1 ||
		(op2 != OTHER_OP && ((t_token*)(lexer->content))->op_type == op2))
		{
			ptrs[SAVE1] = ptrs[PREV];
			ptrs[SAVE2] = lexer->next;
		}
		ptrs[PREV] = lexer;
		lexer = lexer->next;
	}
	ptrs[PREV] = ptrs[SAVE1];
	ptrs[SAVE1] && (ptrs[SAVE1] = ptrs[SAVE1]->next);
	ptrs[PREV] && (ptrs[PREV]->next = NULL);
	if ((!is_in_lexer(ptrs[ORIGIN], op1) ||
		(op2 != OTHER_OP && !is_in_lexer(ptrs[ORIGIN], op2))) && !ptrs[SAVE1])
		op_not_found(ptrs[ORIGIN], root);
	if (op_found(ptrs[SAVE1], ptrs[SAVE2], root))
		build_ast(ptrs[ORIGIN], &((*root)->left), op1, op2);
}
