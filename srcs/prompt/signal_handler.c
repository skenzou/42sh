/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:31:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/25 23:49:35 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sigint_handler(int sig)
{
	t_cap *tcap;

	tcap = g_shell->tcap;
	if (sig == SIGINT)
	{
		signal(SIGINT, sigint_handler);
		end_event(tcap);
		if (g_shell->autocomp->state)
		{
			tputs(tcap->clr_all_line, 1, ft_put_termcaps);
			g_shell->autocomp->state = 0;
			g_shell->autocomp->pos = 0;
		}
		ft_printf("\n");
		print_prompt_prefix();
		g_shell->lastsignal = 1;
		g_shell->autocomp->state = 0;
		ft_bzero(tcap->command, BUFFSIZE);
		tcap->char_len = 0;
		tcap->cursx = tcap->prompt_len;
		tcap->cursy = 0;
	}
}

void	sigfork(int sig)
{
	if (sig == SIGINT)
	{
		close_fd();
		ft_putchar('\n');
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
		if (g_shell->autocomp->state)
		{
			tputs(tcap->clr_all_line, 1, ft_put_termcaps);
			ft_tab(tcap, g_shell->autocomp);
		}
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
