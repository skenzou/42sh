/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 01:26:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/15 01:26:54 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
