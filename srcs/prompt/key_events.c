/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:23:43 by aben-azz          #+#    #+#             */
/*   Updated: 2019/11/12 18:22:01 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		enter_event(t_cap *tcap)
{
	t_ab	*autocomp;
	int		i;

	autocomp = g_shell->autocomp;
	g_shell->history->position = -1;
	if (!autocomp->state)
		return (-2);
	tputs(tcap->clr_all_line, 1, ft_put_termcaps);
	i = ft_strlen2(g_shell->autocomp->match);
	while (i--)
		ft_delete_back(tcap);
	ft_insert(g_shell->autocomp->data[g_shell->autocomp->pos], tcap);
	if (!g_shell->autocomp->isdir && g_shell->autocomp->after[0])
		ft_insert(g_shell->autocomp->after, tcap);
	if (!g_shell->autocomp->isdir)
		ft_insert(" ", tcap);
	g_shell->autocomp->state = 0;
	i = -1;
	while (++i < g_shell->autocomp->len)
		ft_strdel(&(g_shell->autocomp->data[i]));
	g_shell->autocomp->pos = 0;
	g_shell->autocomp->isdir = 0;
	g_shell->autocomp->len = 0;
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
	if (!g_shell->inhib_mod && !tcap->char_len)
	{
		save_alias(1);
		kill_pids();
		ft_printf("exit\n");
		exit(0);
	}
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
