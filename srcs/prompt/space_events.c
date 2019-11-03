/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 20:28:50 by aben-azz          #+#    #+#             */
/*   Updated: 2019/11/03 05:27:42 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		backspace_event(t_cap *tcap)
{
	t_ctrl_r *ctrl_r;

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
		int i = -1;
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

	index = 0;
	if (g_shell->autocomp->state)
	{
		tputs(tcap->clr_all_line, 1, ft_put_termcaps);
		i = ft_strlen(g_shell->autocomp->match);
		while (i--)
			ft_delete_back(tcap);
		ft_insert(g_shell->autocomp->data[g_shell->autocomp->pos], tcap);
		if (g_shell->autocomp->data[g_shell->autocomp->pos]
			[ft_strlen(g_shell->autocomp->data[g_shell->autocomp->pos]) - 1]
																		!= '/')
		{
			if (g_shell->autocomp->after[0])
				ft_insert(g_shell->autocomp->after, tcap);
			ft_insert(" ", tcap);
		}
		g_shell->autocomp->state = 0;
		i = -1;
		while (++i < g_shell->autocomp->len)
		{
			ft_strdel(&(g_shell->autocomp->data[i]));
		}
		g_shell->autocomp->pos = 0;
		g_shell->autocomp->isdir = 0;
		g_shell->autocomp->len = 0;
		return (1);
	}
	else if (~(index = ft_lastindexof(tcap->command, '!')))
		expansion_history(tcap->command, tcap, index);
	ft_insert(" ", tcap);
	return (1);
}
