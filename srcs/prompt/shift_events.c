/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:04:00 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/15 07:49:42 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		shift_arrow_up_event(t_cap *tcap)
{
	(void)tcap;
	return (1);
}

int		shift_arrow_down_event(t_cap *tcap)
{
	(void)tcap;
	return (1);
}

int		shift_arrow_right_event(t_cap *tcap)
{
	(void)tcap;
	return (1);
}

int		shift_arrow_left_event(t_cap *tcap)
{
	(void)tcap;
	return (1);
}

int		shift_tab_event(t_cap *tcap)
{
	(void)tcap;

	t_ab *autocomp;

	autocomp = g_shell->autocomp;
	if (autocomp->state)
	{
		autocomp->pos--;
		if (autocomp->pos == -1)
			autocomp->pos = autocomp->len - 1;
	}
	ft_tab(tcap, autocomp);
	return (1);
}
