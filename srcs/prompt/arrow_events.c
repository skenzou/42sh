/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:04:00 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/26 00:03:15 by aben-azz         ###   ########.fr       */
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
	t_ab	*comp;
	int		x;

	if ((comp = g_shell->autocomp) && g_shell->autocomp->state)
	{
		if (comp->pos - comp->row > -1)
			comp->pos -= comp->row;
		else
		{
			if ((x = comp->pos % ft_max(comp->row, 1)) < comp->carry)
			{
				comp->pos = comp->len - 1;
				if (comp->pos)
					comp->pos -= comp->carry - x - 1;
			}
			else
			{
				comp->pos = comp->len - 1;
				comp->pos -= comp->carry;
				comp->pos -= comp->row - x - 1;
			}
		}
		return (ft_tab(tcap, comp));
	}
	return (histo_up(tcap, g_shell->history));
}

int		arrow_down_event(t_cap *tcap)
{
	t_ab	*autocomp;
	int		new_x;

	if (g_shell->autocomp->state)
	{
		autocomp = g_shell->autocomp;
		new_x = autocomp->pos % ft_max(autocomp->row, 1);
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
	return (ft_move(tcap, "left", 1));
}
