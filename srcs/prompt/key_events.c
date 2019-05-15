/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:23:43 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/15 04:48:18 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_tab(t_cap *tcap, t_ab *autocomp)
{
	char *string[] = {"oui", "jsp", "gros", "delire", "jpp de ouf",
		"ta kiff", "xdd", "ta kiffer ou quoi negro", "jm la vi", "jm la mort", NULL};
	int i;
	int max_offset;
	int offset;
	int j;
	int k;
	int row;
	int col;

	max_offset = 23;
	row = tcap->cursx_max / max_offset;
	autocomp->len = ft_split_count(string);
	col = autocomp->len / row;
	ft_putchar('\n');
	i = 0;
	k = 0;
	while (k < col)
	{
		j = 0;
		while (j < row)
		{
			offset = max((max_offset + 2) - ft_strlen(string[i]), 2);
			if (i == autocomp->pos)
				ft_printf("\x1b[7m%-s\x1b[0m%-*s", string[i], offset, "");
			else
				ft_printf("%-s%-*s", string[i], offset, "");
			j++;
			i++;
		}
		ft_putchar('\n');
		k++;
	}
	ft_replace_cursor(tcap);
	i = -1;
	while (i < col)
	{
		tputs(tcap->up, 1, ft_put_termcaps);
		i++;
	}
	return (1);
}

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
		if (autocomp->pos == autocomp->len - 2)
			autocomp->pos = 0;
		else
			autocomp->pos++;
	}
	ft_tab(tcap, autocomp);
	return (1);
}
