/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:31:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/26 07:13:23 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, sigint_handler);
		ft_printf("\n");
		g_shell->lastsignal = 1;
		ft_bzero(g_shell->tcap->command, BUFFSIZE);
		g_shell->ctrl_r->state = 0;
		g_shell->tcap->overflow = 0;
		if (g_shell->inhib_mod == 1)
		{
			fcntl(0, F_SETFL, O_NONBLOCK);
			ft_lstdel(&g_shell->redir, redir_delone);
			if (g_shell->ast)
				del_ast(&g_shell->ast);
			else
				lex_del_list(&g_shell->lexer);
			g_shell->tcap->prompt = NULL;
			g_shell->inhib_mod = 2;
		}
		else
			print_prompt_prefix();
		ft_bzero(g_shell->tcap->carry, 2);
		g_shell->dprompt = 1;
	}
}

void	sigfork(int sig)
{
	if (sig == SIGINT)
	{
		close_fd();
		signal(SIGINT, sigfork);
	}
}

void	sigwinch_handler(int sig)
{
	t_cap	*tcap;
	int		p;
	int		prompt_len;

	tcap = g_shell->tcap;
	p = tcap->cursy * (tcap->cursx_max + 1) + (tcap->cursx) - tcap->prompt_len;
	prompt_len = tcap->init_len;
	if (sig == SIGWINCH)
	{
		init_termcap(tcap);
		if (prompt_len >= g_shell->tcap->cursx_max + 1)
			tcap->prompt_len = prompt_len % (tcap->cursx_max + 1);
		else
			tcap->prompt_len = prompt_len;
		tcap->cursy = (p + tcap->prompt_len) / (tcap->cursx_max + 1);
		tcap->cursx = (p + tcap->prompt_len) % (tcap->cursx_max + 1);
	}
}

void	sigtstp_dflhandler(int sig)
{
	if (sig == SIGTSTP)
	{
		ft_putchar(7);
		signal(SIGTSTP, sigtstp_dflhandler);
	}
}

void	sigtstp_handler(int sig)
{
	if (sig == SIGTSTP)
		signal(SIGTSTP, sigtstp_handler);
}
