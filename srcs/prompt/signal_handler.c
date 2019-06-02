/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:31:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/02 15:04:19 by midrissi         ###   ########.fr       */
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
		print_prompt_prefix();
		// exit(0);
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
	struct winsize	*w;

	if (sig == SIGWINCH)
	{
		signal(SIGWINCH, sigwinch_handler);
		if (!(w = ft_memalloc(sizeof(*w))))
			return ;
		if (ioctl(1, TIOCGWINSZ, w))
			g_shell->tcap->cursx_max = w->ws_col - 1;
		ft_printf("redimensionnement:{%d, %d}\n", tgetnum("co"), tgetnum("li"));
		print_prompt_prefix();
	}
}
