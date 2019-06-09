/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:23:43 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/05 00:34:12 by aben-azz         ###   ########.fr       */
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
	t_ctrl_r *ctrl_r;

	ctrl_r = g_shell->ctrl_r;
	if (ctrl_r->state)
	{
		ctrl_r->index--;
		ctrl_r->index = ft_max(ctrl_r->index, 0);
		ctrl_r->data[ctrl_r->index] = '\0';
		return (clear_before_ctrl_r(tcap, ctrl_r));
	}
	else
		return (ft_delete_back(tcap));
	return (1);
}

int		space_event(t_cap *tcap)
{
	int index;

	index = 0;
	if (g_shell->autocomp->state)
	{
		tputs(tcap->clr_all_line, 1, ft_put_termcaps);
		ft_insert(g_shell->autocomp->data[g_shell->autocomp->pos].name, tcap);
		g_shell->autocomp->match = ft_strdup(tcap->command);
		g_shell->autocomp->state = 0;
		g_shell->autocomp->pos = 0;
	}
	if (~(index = ft_lastindexof(tcap->command, '!')))
		expansion_history(tcap->command, tcap, index);
	ft_insert(" ", tcap);
	return (1);
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
	// ft_insert("ctrl_d", tcap);
	ft_printf("exit\n");
	exit(0);
	return (1);
}

int		tab_event(t_cap *tcap)
{
	t_ab *autocomp;

	autocomp = g_shell->autocomp;
	// if (!autocomp->state)
	// {
	// 	autocomp->state = 1;
	// 	autocomp->match = ft_strdup(tcap->command);
	// }
	// else
	// {
	// 	autocomp->pos++;
	// 	if (autocomp->pos == autocomp->len)
	// 		autocomp->pos = 0;
	// }
	dprintf(debug(), "pos: %d\n", autocomp->pos);
	ft_tab(tcap, autocomp);
	return (1);
}
