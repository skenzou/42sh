/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 01:26:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/11/09 15:51:04 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**free *word ?
*/

static void		read_inhib(char inhib, char **word)
{
	char *save;
	char *input;

	while (42 && g_shell->inhib_mod != 2)
	{
		input = read_line(g_shell->tcap);
		if (g_shell->inhib_mod == 2)
			return ;
		if (ft_strchr(input, inhib) || inhib == '\\')
			input[ft_strlen(input) - 1] = '\0';
		save = *word;
		if (!(*word = ft_strjoin(*word, input)))
			ft_exit("Malloc failed in exec_inhib");
		free(save);
		if (ft_strchr(input, inhib) || inhib == '\\')
			break ;
	}
}

static void		exec_inhib(char inhib, char **str)
{
	char *save;

	if (inhib == DQUOTE)
		g_shell->tcap->prompt = "dquote>";
	else if (inhib == QUOTE)
		g_shell->tcap->prompt = "quote>";
	else if (inhib == BSLASH)
		g_shell->tcap->prompt = ">";
	save = *str;
	if (inhib != BSLASH && !(*str = ft_strjoin(*str, "\n")))
		ft_exit("Malloc failed in exec_inhib");
	else
		(*str)[ft_strlen(*str) - 1] = '\n';
	if (inhib != BSLASH)
		free(save);
	read_inhib(inhib, str);
	g_shell->tcap->prompt = NULL;
}

static int		check_bslash(char **str, char **cmd)
{
	if (**str == BSLASH)
	{
		(*str)++;
		if (**str)
			(*str)++;
		else
		{
			exec_inhib(BSLASH, cmd);
			return (1);
		}
		return (-1);
	}
	return (0);
}

static int		check_quotes(char **str, char **cmd)
{
	char inhib;

	if (**str == DQUOTE || **str == QUOTE)
	{
		inhib = *(*str)++;
		while (**str && **str != inhib)
		{
			if (**str == BSLASH && *((*str) + 1))
				(*str) += 2;
			else
				(*str)++;
		}
		if (!**str)
		{
			exec_inhib(inhib, cmd);
			return (1);
		}
	}
	return (0);
}

void			check_inhib(char **cmd)
{
	char	*str;
	int		ret;

	g_shell->inhib_mod = 1;
	str = *cmd;
	while (*str)
	{
		ret = check_bslash(&str, cmd);
		if (ret == -1)
			continue ;
		else if (ret == 1)
			return ;
		if (g_shell->inhib_mod == 2)
			return ;
		if (check_quotes(&str, cmd))
			return ;
		str++;
	}
}
