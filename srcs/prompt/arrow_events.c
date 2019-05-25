/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:04:00 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/25 06:13:16 by aben-azz         ###   ########.fr       */
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
	int		new_x;
	int		new_y;

	if ((autocomp = g_shell->autocomp) && g_shell->autocomp->state)
	{
		new_x = autocomp->pos % autocomp->row;
		new_y = (autocomp->pos / autocomp->col) - 1;
		if (new_y < 0 && new_x > 0 && --new_x)
		{
			(new_x < 0) && (new_x = 0);
			new_y = autocomp->col - 1;
			(autocomp->carry && new_x + 1 <= autocomp->carry) && new_y++;
		}
		else if (new_y < 0 && new_x == 0)
		{
			new_y = autocomp->col - 1;
			(autocomp->carry && new_x <= autocomp->carry) && new_y++;
		}
		g_shell->autocomp->pos = (new_y * autocomp->col) + new_x;
		ft_tab(tcap, autocomp);
	}
	else
		histo_up(tcap, g_shell->history);
	return (1);
}

int		arrow_down_event(t_cap *tcap)
{
	t_ab	*autocomp;
	int		new_x;
	int		new_y;

	autocomp = g_shell->autocomp;
	if (g_shell->autocomp->state)
	{
		new_x = autocomp->pos % autocomp->row;
		new_y = (autocomp->pos / autocomp->col) + 1;
		if ((new_y > (autocomp->row - 1 + (autocomp->carry > new_x))) &&
													new_x < autocomp->col - 1)
		{
			new_x++;
			if (new_x > autocomp->col - 1)
				new_x = autocomp->col - 1;
			new_y = 0;
		}
		else if (new_y > autocomp->row - 1 && new_x == autocomp->col - 1)
			new_y = 0;
		g_shell->autocomp->pos = (new_y * autocomp->col) + new_x;
		ft_tab(tcap, autocomp);
	}
	else
		histo_down(tcap, g_shell->history);
	return (1);
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
		ft_tab(tcap, autocomp);
	}
	else
		return (ft_move(tcap, "right", 1));
	return (1);
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
		ft_tab(tcap, autocomp);
	}
	else
		return (ft_move(tcap, "left", 1));
	return (1);
}
