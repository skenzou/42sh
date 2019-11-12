/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 02:39:58 by aben-azz          #+#    #+#             */
/*   Updated: 2019/11/12 20:07:58 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*make_prompt(char *format)
{
	char	*prompt;

	(void)format;
	prompt = format;
	g_shell->tcap->prompt_len = ft_strlen2(prompt) + 1;
	g_shell->tcap->cursx = g_shell->tcap->prompt_len;
	return (prompt);
}

static int	display_prompt(char *n, char *git, char *string, int prompt_len)
{
	ft_putstr_fd(g_shell->lastsignal ? PROMPT1_ERR : PROMPT1, 0);
	multi_putstr_fd("\x1b[36m\x1b[1m",
						(string + ft_lastindexof(string, '/') + 1), " \x1b[0m");
	ft_strdel(&string);
	if (git && (prompt_len += 7 + ft_strlen2(git)))
		multi_putstr_fd("\x1b[1m\x1b[34mgit:(\x1b[31m",
				git, "\x1b[34m) \x1b[0m") ? ft_strdel(&git) : ft_strdel(&git);
	multi_putstr_fd("\x1b[1m\x1b[31m", n, "\x1b[0m\x1b[33m\x1b[1m ✗ \x1b[0m");
	return (prompt_len);
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
	prompt_len = ft_strlen2((string + ft_lastindexof(string, '/') + 1)) +
													ft_strlen2(name) + 6 + 1;
	return (display_prompt(name, git, string, prompt_len));
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
		multi_putstr_fd(make_prompt(prompt), " ", NULL);
		return ;
	}
	print_default_prompt_prefix();
}
