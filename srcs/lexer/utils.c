/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 00:33:06 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/15 03:43:32 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void 	lex_delone(void *data, size_t size)
{
	t_token token;

	(void)size;
	if (data)
	{
		token = *((t_token *)(data));
		ft_splitdel(token.content);
		free(data);
	}
}

void  lex_del_list(t_list **lexer)
{
	t_list *temp;
	t_list *list;

	list = *lexer;
	while (list)
	{
		temp = list;
		list = list->next;
		ft_lstdelone(&temp, lex_delone);
	}
  *lexer = NULL;
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
