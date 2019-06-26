/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:23:43 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/25 23:54:37 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		enter_event(t_cap *tcap)
{
	t_ab	*autocomp;
	int		i;

	autocomp = g_shell->autocomp;
	g_shell->history->position = -1;
	if (autocomp->state)
	{
		tputs(tcap->clr_all_line, 1, ft_put_termcaps);
		i = ft_strlen(g_shell->autocomp->match);
		while (i--)
			ft_delete_back(tcap);
		ft_insert(g_shell->autocomp->data[g_shell->autocomp->pos], tcap);
		if (g_shell->autocomp->after[0] && !g_shell->autocomp->isdir)
			ft_insert(g_shell->autocomp->after, tcap);
		g_shell->autocomp->state = 0;
		int i = -1;
		while (++i < g_shell->autocomp->len)
		{
			ft_strdel(&(g_shell->autocomp->data[i]));
		}
		g_shell->autocomp->pos = 0;
		g_shell->autocomp->isdir = 0;
		g_shell->autocomp->len = 0;
		return (1);
	}
	return (-2);
}

int		ctrl_r_event(t_cap *tcap)
{
	t_ctrl_r *ctrl_r;

	(void)tcap;
	ctrl_r = g_shell->ctrl_r;
	if ((ctrl_r->state = !ctrl_r->state))
	{
		ctrl_r->index = 0;
		return (back_i_search(ctrl_r, tcap));
	}
	else
	{
		ft_bzero(ctrl_r->data, BUFFSIZE);
		ctrl_r->index = 0;
	}
	return (1);
}

int		ctrl_d_event(t_cap *tcap)
{
	(void)tcap;
	ft_printf("exit\n");
	exit(0);
	return (1);
}

int		tab_event(t_cap *tcap)
{
	t_ab *autocomp;

	autocomp = g_shell->autocomp;
	if (autocomp->state)
	{
		autocomp->pos++;
		if (autocomp->pos == autocomp->len)
			autocomp->pos = 0;
		process_completion(autocomp);
	}
	else
		ft_tab(tcap, autocomp);
	return (1);
}
