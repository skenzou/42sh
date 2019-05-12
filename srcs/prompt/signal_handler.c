/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:31:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/12 02:08:40 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, sigint_handler);
		ft_printf("\n");
		print_prompt_prefix();
		exit(0);
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
