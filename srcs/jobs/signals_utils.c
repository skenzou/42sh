/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 13:41:37 by tlechien          #+#    #+#             */
/*   Updated: 2019/10/23 11:13:35 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Handler for TSTP signal.
*/

void	sigtstp_handler(int sig)
{
	if (sig == SIGTSTP)
		signal(SIGTSTP, sigtstp_handler);
}

/*
** Handler for QUIT signal.
*/

void		sigquit_dflhandler(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putchar(7);
		signal(SIGQUIT, sigquit_dflhandler);
	}
}

/*
** Sets the needed signal_handlers.
*/

void	init_signal(void)
{
	g_shell->inhib_mod = 0;
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGALRM, SIG_IGN);
	signal(SIGTSTP, sigtstp_dflhandler);
	signal(SIGQUIT, sigquit_dflhandler);
	signal(SIGINT, sigint_handler);
	signal(SIGWINCH, sigwinch_handler);
	signal(SIGCHLD, sigchld_handler);
}

/*
** Get the len of an int. (prob dupe)
*/

int		get_nb_len(long long nb)
{
	int i;

	i = 1;
	while ((nb /= 10) > 1)
		i++;
	return (i);
}

/*
** Idle for a given period of time
*/

int		waitabit(int min, int nsec)
{
	struct timespec	slp;

	slp.tv_sec = min;
	slp.tv_nsec = nsec;
	nanosleep(&slp, NULL);
	return (0);
}
