/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:31:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/12 08:11:32 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

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
	t_cap	*tcap;
	int		char_len;
	char	command[BUFFSIZE];
	int		pos;

	if (sig == SIGWINCH)
	{
		tcap = g_shell->tcap;
		(void)sig;
		pos = tcap->cursy * (tcap->cursx_max + 1)
			+ tcap->cursx - tcap->prompt_len;
		ft_bzero(command, BUFFSIZE);
		ft_strcpy(command, tcap->command);
		char_len = tcap->char_len;
		init_termcap(tcap);
		ft_strcpy(tcap->command, command);
		tcap->char_len = char_len;
		tcap->cursy = (pos + tcap->prompt_len)
								/ (tcap->cursx_max + 1);
		tcap->cursx = (pos + tcap->prompt_len)
								% (tcap->cursx_max + 1);
	}
}
