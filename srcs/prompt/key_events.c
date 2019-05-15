/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:23:43 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/15 07:48:30 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		enter_event(t_cap *tcap)
{
	(void)tcap;
	if (g_shell->autocomp->state)
		g_shell->autocomp->state = 0;
	g_shell->history->position = -1;
	return (-2);
}

int		backspace_event(t_cap *tcap)
{
	return (ft_delete_back(tcap));
}

int		ctrl_r_event(t_cap *tcap)
{
	ft_insert("ctrl_r", tcap);
	return (1);
}

int		ctrl_d_event(t_cap *tcap)
{
	(void)tcap;
	ft_insert("ctrl_d", tcap);
	exit(0);
	return (1);
}

int		tab_event(t_cap *tcap)
{
	t_ab *autocomp;

	autocomp = g_shell->autocomp;
	if (!autocomp->state)
	{
		autocomp->state = 1;
	}
	else
	{
		autocomp->pos++;
		ft_dprintf(debug(), "pos: %d\n", autocomp->pos);
		if (autocomp->pos == autocomp->len)
			autocomp->pos = 0;

	}
	ft_tab(tcap, autocomp);
	return (1);
}
