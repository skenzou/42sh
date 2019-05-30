/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:04:00 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/27 06:43:44 by aben-azz         ###   ########.fr       */
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
	t_ab	*autocomp;
	int		x;

	if ((autocomp = g_shell->autocomp) && g_shell->autocomp->state)
	{
		x = autocomp->pos % autocomp->row;
		if (autocomp->pos - autocomp->row > -1)
			autocomp->pos -= autocomp->row;
		else
		{

			if (x < autocomp->carry)
			{
				autocomp->pos = autocomp->len - 1;
				if (autocomp->pos)
					autocomp->pos -= autocomp->carry - x - 1;
			}
			else
			{
				autocomp->pos = autocomp->len - 1;
				autocomp->pos -= autocomp->carry;
				autocomp->pos -= autocomp->row - x - 1;
			}
		}
		return (ft_tab(tcap, autocomp));
	}
	return (histo_up(tcap, g_shell->history));
}

int		arrow_down_event(t_cap *tcap)
{
	t_ab	*autocomp;
	int		new_x;

	autocomp = g_shell->autocomp;
	new_x = autocomp->pos % autocomp->row;
	if (g_shell->autocomp->state)
	{
		if (autocomp->pos + autocomp->row < autocomp->len)
			autocomp->pos += autocomp->row;
		else
		{
			if (new_x < autocomp->carry)
				autocomp->pos = new_x;
			else
				autocomp->pos = new_x;
		}
		return (ft_tab(tcap, autocomp));
	}
	return (histo_down(tcap, g_shell->history));
}

int		arrow_right_event(t_cap *tcap)
{
	t_ab	*autocomp;

	autocomp = g_shell->autocomp;
	if (g_shell->autocomp->state)
	{
		autocomp->pos++;
		if (autocomp->pos == autocomp->len)
			autocomp->pos = 0;
		return (ft_tab(tcap, autocomp));
	}
	return (ft_move(tcap, "right", 1));
}

int		arrow_left_event(t_cap *tcap)
{
	t_ab	*autocomp;

	autocomp = g_shell->autocomp;
	if (g_shell->autocomp->state)
	{
		autocomp->pos--;
		if (autocomp->pos == -1)
			autocomp->pos = autocomp->len - 1;
		return (ft_tab(tcap, autocomp));
	}
	return (ft_move(tcap, "left", 1));;
}
