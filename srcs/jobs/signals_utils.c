/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 13:41:37 by tlechien          #+#    #+#             */
/*   Updated: 2019/06/26 04:11:40 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sigint_inhib_handler(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, sigint_inhib_handler);
		ft_lstdel(&g_shell->redir, redir_delone);
		if (g_shell->ast)
			del_ast(&g_shell->ast);
		else
			lex_del_list(&g_shell->lexer);
		ft_printf("\n");
		g_shell->lastsignal = 1;
		g_shell->tcap->prompt = NULL;
		g_shell->dprompt = 1;
		g_shell->inhib_mod = 2;
	}
}

int	get_nb_len(long long nb)
{
	int i;

	i = 1;
	while ((nb /= 10) > 1)
		i++;
	return (1);
}

int	waitabit(int min, int nsec)
{
	struct timespec	slp;

	slp.tv_sec = min;
	slp.tv_nsec = nsec;
	nanosleep(&slp, NULL);
	return (0);
}
