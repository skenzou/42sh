/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 00:33:06 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/05 00:50:59 by midrissi         ###   ########.fr       */
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
    free(token.content);
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

void  del_all_front_semis(t_list **lexer)
{
	t_list *list;
	t_token token;
	t_list *tmp;

	list = *lexer;
	while (list)
	{
		token = *((t_token *)(list->content));
		if (token.op_type == SEMI)
		{
			tmp = list;
			list = list->next;
			ft_lstdelone(&tmp, lex_delone);
		}
		else
			break ;
	}
	*lexer = list;
}
