/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 02:39:58 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/15 17:48:03 by ghamelek         ###   ########.fr       */
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

int get_prompt_lenght(void)
{
	int len;

	len = 0;


	return (len);
}

static int print_prefix(void)
{
	int prompt_len;
	char *string;
	char *git;
	char *name;
	
	git = NULL;
	name = getenv("USER");
	name || (name = "42sh");
	string = NULL;
	string = getcwd(NULL, 20);
	git = get_git_status();
	!ft_strcmp(string, "/") && (string = "/");
	prompt_len = ft_strlen((string + ft_lastindexof(string, '/') + 1)) +
														ft_strlen(name) + 6 + 1;
	ft_printf(g_shell->lastsignal ? PROMPT1_ERR : PROMPT1);
	ft_printf(PROMPT2, (string + ft_lastindexof(string, '/') + 1));
	ft_strdel(&string);
	if (git)
	{
		prompt_len += 7 + ft_strlen(git);
		ft_printf(PROMPT3, git);
		ft_strdel(&git);
	}
	ft_printf(PROMPT4, name);
	return (prompt_len);
}

static void	print_default_prompt_prefix(void)
{
	int prompt_len;

	prompt_len = print_prefix();
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
	if (g_shell->tcap->prompt)
	{
		ft_printf("%s ", make_prompt(g_shell->tcap->prompt));
		return ;
	}
	print_default_prompt_prefix();
	tputs(g_shell->tcap->save, 1, ft_put_termcaps);
}
