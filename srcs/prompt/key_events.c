/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:23:43 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/27 06:27:33 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		enter_event(t_cap *tcap)
{
	t_ab *autocomp;

	autocomp = g_shell->autocomp;
	g_shell->history->position = -1;
	if (autocomp->state)
	{
		autocomp->state = 0;
		ft_clear_replace(tcap);
		tputs(tcap->clr_all_line, 1, ft_put_termcaps);
		ft_insert(ft_strjoin(autocomp->match,
			autocomp->data[autocomp->pos].name), tcap);
		autocomp->pos = 0;
		return (1);
	}
	return (-2);
}

int		backspace_event(t_cap *tcap)
{
	return (ft_delete_back(tcap));
}

int		space_event(t_cap *tcap)
{
	ft_insert(" ", tcap);
	tputs(tcap->clr_all_line, 1, ft_put_termcaps);
	g_shell->autocomp->match = ft_strdup(tcap->command);
	g_shell->autocomp->state = 0;
	return (1);
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
		autocomp->match = ft_strdup(tcap->command);
	}
	else
	{
		autocomp->pos++;
		if (autocomp->pos == autocomp->len)
			autocomp->pos = 0;
	}
	dprintf(debug(), "pos: %d\n", autocomp->pos);
	ft_tab(tcap, autocomp);
	return (1);
}
