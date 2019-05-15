/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:04:00 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/15 07:48:33 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_clear_replace(t_cap *tcap)
{
	ft_clear_all_lines(tcap);
	ft_bzero(tcap->command, BUFFSIZE);
	tcap->char_len = 0;
	tcap->cursx = tcap->prompt_len;
	tcap->cursy = 0;
	ft_replace_cursor(tcap);
}

int		arrow_up_event(t_cap *tcap)
{
	if (g_shell->autocomp->state)
	{
		;
	}
	else
	{
		histo_up(tcap, g_shell->history);
	}
	return (1);
}

int		arrow_down_event(t_cap *tcap)
{
	if (g_shell->autocomp->state)
	{
		;
	}
	else
	{
		histo_down(tcap, g_shell->history);
	}
	return (1);
}

int		arrow_right_event(t_cap *tcap)
{
	return (ft_right(tcap));
}

int		arrow_left_event(t_cap *tcap)
{
	return (ft_left(tcap));
}
