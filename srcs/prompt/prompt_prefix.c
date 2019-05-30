/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 02:39:58 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/25 06:13:42 by aben-azz         ###   ########.fr       */
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

static void	print_default_prompt_prefix(void)
{
	char *string;
	char *name;
	char *git;
	int prompt_len;
	name = getenv("USER");
	name || (name = "42sh");
	string = NULL;
	string = getcwd(string, 20);
	git = get_git_status();
	!ft_strcmp(string, "/") && (string = "/");
	prompt_len = ft_strlen((string + ft_lastindexof(string, '/') + 1)) +
														ft_strlen(name) + 6 + 1;
	if (g_shell->lastsignal)
		ft_printf(PROMPT1_ERR);
	else
		ft_printf(PROMPT1);
	ft_printf(PROMPT2, (string + ft_lastindexof(string, '/') + 1));
	if (git)
	{
		prompt_len += 7 + ft_strlen(git);
		ft_printf(PROMPT3, git);
	}
	ft_printf(PROMPT4, name);
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
	char *ps1;
	char *custom_prompt;
	char *prompt;

	prompt = g_shell->tcap->prompt;
	if (prompt)
	{
		ft_printf("%s ", make_prompt(prompt));
		return ;
	}
	ps1 = get_string_var("PS1", g_shell->var);
	if (ps1 && ft_strcmp(ps1, "NULL") && ft_strcmp(ps1, "null"))
	{
		if (!(custom_prompt = make_prompt(ps1)))
			print_default_prompt_prefix();
		else
			ft_printf(custom_prompt);
	}
	else
		print_default_prompt_prefix();
	ft_putstr(DEFAULT_PROMPT_COLOR);
}
