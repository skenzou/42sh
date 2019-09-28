/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 20:28:50 by aben-azz          #+#    #+#             */
/*   Updated: 2019/09/28 08:15:05 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		backspace_event(t_cap *tcap)
{
	t_ctrl_r *ctrl_r;
	int i;

	ctrl_r = g_shell->ctrl_r;
	if (ctrl_r->state)
	{
		ctrl_r->index--;
		ctrl_r->index = ft_max(ctrl_r->index, 0);
		ctrl_r->data[ctrl_r->index] = '\0';
		return (clear_before_ctrl_r(tcap, ctrl_r));
	}
	else if (g_shell->autocomp->state)
	{
		tputs(tcap->clr_all_line, 1, ft_put_termcaps);
		g_shell->autocomp->state = 0;
		i = -1;
		while (++i < g_shell->autocomp->len)
		{
			ft_strdel(&(g_shell->autocomp->data[i]));
		}
		g_shell->autocomp->pos = 0;
		return (1);
	}
	else
		return (ft_delete_back(tcap));
	return (1);
}

int		space_event(t_cap *tcap)
{
	int	index;
	int	i;
	t_ab *autocomp;

	autocomp = g_shell->autocomp;
	index = 0;
	if (autocomp->state)
	{
		tputs(tcap->clr_all_line, 1, ft_put_termcaps);
		i = ft_strlen(autocomp->match);
		while (i--)
			ft_delete_back(tcap);
		ft_insert(autocomp->data[autocomp->pos], tcap);
		if (autocomp->data[autocomp->pos] && autocomp->data[autocomp->pos]
						[ft_strlen(autocomp->data[autocomp->pos]) - 1] != '/')
		{
			if (autocomp->after[0])
				ft_insert(autocomp->after, tcap);
			ft_insert(" ", tcap);
		}
		autocomp->state = 0;
		i = -1;
		while (++i < autocomp->len)
		{
			ft_strdel(&(autocomp->data[i]));
		}
		autocomp->pos = 0;
		autocomp->isdir = 0;
		autocomp->len = 0;
		return (1);
	}
	else if (~(index = ft_lastindexof(tcap->command, '!')))
		expansion_history(tcap->command, tcap, index);
	ft_insert(" ", tcap);
	return (1);
}
