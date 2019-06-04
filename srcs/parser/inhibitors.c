/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 01:26:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/29 16:54:06 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		exec_inhib(char inhib, t_list *lexer, int i)
{
	char *input;
	char **content;
	char *save;

	if (inhib == '"')
		g_shell->tcap->prompt = "dquote>";
	else if (inhib == '\'')
		g_shell->tcap->prompt = "quote>";
	else if (inhib == '\\')
		g_shell->tcap->prompt = ">";
	content = ((t_token *)(lexer->content))->content;
	save = content[i];
	if (!(content[i] = ft_strjoin(content[i], "\n")))
		ft_exit("Malloc failed in exec_inhib");
	free(save);
	while (42)
	{
		input = read_line(g_shell->tcap);
		if (ft_strchr(input, inhib) || inhib == '\\')
			input[ft_strlen(input) - 1] = '\0';
		save = content[i];
		if (!(content[i] = ft_strjoin(content[i], input)))
			ft_exit("Malloc failed in exec_inhib");
		free(save);
		if (ft_strchr(input, inhib) || inhib == '\\')
			break ;
	}
	g_shell->tcap->prompt = NULL;
}

static void		check_inhib(char *str, t_list *lexer, int i)
{
	char inhib;

	while (*str)
	{
		if (*str == BSLASH)
		{
			str++;
			if (*str)
				str++;
			else
			{
				exec_inhib(BSLASH, lexer, i);
				return ;
			}
		}
		if (*str == DQUOTE || *str == QUOTE)
		{
			inhib = *str++;
			while (*str && *str != inhib)
			{
				if (*str == BSLASH && *(str + 1))
					str += 2;
				else
					str++;
			}
			if (!*str)
			{
				exec_inhib(inhib, lexer, i);
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
				check_inhib(token->content[i], lexer, i);
				i++;
			}
		}
		lexer = lexer->next;
	}
}
