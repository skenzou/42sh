/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_prefix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 02:39:58 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/12 07:07:43 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

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

	name = getenv("USER");
	name || (name = "21sh");
	string = NULL;
	string = getcwd(string, 20);
	git = get_git_status();
	!ft_strcmp(string, "/") && (string = "/");
	g_shell->tcap->prompt_len =
		ft_strlen((string + ft_lastindexof(string, '/') + 1)) +
															ft_strlen(name) + 6 + 1;
	ft_printf(PROMPT1);
	ft_printf(PROMPT2, (string + ft_lastindexof(string, '/') + 1));
	if (git)
	{
		g_shell->tcap->prompt_len += 7 + ft_strlen(git);
		ft_printf(PROMPT3, git);
	}
	ft_printf(PROMPT4, name);
	g_shell->tcap->cursx = g_shell->tcap->prompt_len;
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
