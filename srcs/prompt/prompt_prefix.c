/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 02:39:58 by aben-azz          #+#    #+#             */
/*   Updated: 2019/11/03 05:12:47 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*make_prompt(char *format)
{
	char	*prompt;

	(void)format;
	prompt = format;
	g_shell->tcap->prompt_len = ft_strlen(prompt) + 1;
	g_shell->tcap->cursx = g_shell->tcap->prompt_len;
	return (prompt);
}

static int	print_prefix(void)
{
	int		prompt_len;
	char	*string;
	char	*git;
	char	*name;

	name = get_all_key_value("USER", g_shell->env);
	name || (name = "42sh");
	string = NULL;
	git = get_git_status();
	string = getcwd(string, 20);
	if (!string)
	{
		if (git)
			ft_strdel(&git);
		return (-1);
	}
	prompt_len = ft_strlen((string + ft_lastindexof(string, '/') + 1)) +
														ft_strlen(name) + 6 + 1;
	ft_printf(g_shell->lastsignal ? PROMPT1_ERR : PROMPT1);
	ft_printf(PROMPT2, (string + ft_lastindexof(string, '/') + 1));
	ft_strdel(&string);
	if (git && (prompt_len += 7 + ft_strlen(git)))
		ft_printf(PROMPT3, git) ? ft_strdel(&git) : ft_strdel(&git);
	ft_printf(PROMPT4, name);
	return (prompt_len);
}

static void	print_default_prompt_prefix(void)
{
	int prompt_len;

	prompt_len = print_prefix();
	if (!~prompt_len)
		return ;
	if (prompt_len >= g_shell->tcap->cursx_max + 1)
	{
		g_shell->tcap->prompt_len = prompt_len % (g_shell->tcap->cursx_max + 1);
		if (prompt_len == g_shell->tcap->cursx_max + 1)
			ft_move(g_shell->tcap, "down", 1);
	}
	else
		g_shell->tcap->prompt_len = prompt_len;
	g_shell->tcap->cursx = g_shell->tcap->prompt_len;
	g_shell->tcap->init_len = prompt_len;
}

void		print_prompt_prefix(void)
{
	char *prompt;

	prompt = g_shell->tcap->prompt;
	if (prompt)
	{
		ft_printf("%s ", make_prompt(prompt));
		return ;
	}
	print_default_prompt_prefix();
}
