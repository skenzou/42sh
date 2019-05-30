/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:04:00 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/30 06:40:17 by aben-azz         ###   ########.fr       */
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
	int index;

	index = ft_indexof(tcap->command + (tcap->cursx - tcap->prompt_len), ' ');
	while (((tcap->cursx - tcap->prompt_len) + index) < tcap->char_len)
		if (tcap->command[(tcap->cursx - tcap->prompt_len) + index] == ' ')
			index++;
		else
			break ;
	if (index)
		ft_move(tcap, "right", index);
	else
		tputs(tcap->sound, 1, ft_put_termcaps);
	return (1);
}

int		shift_arrow_left_event(t_cap *tcap)
{
	int position;
	int i;

	i = 0;
	position = tcap->cursx - tcap->prompt_len - 1;
	if (tcap->command[position] == ' ')
		while (tcap->command[position] == ' ')
			position--;
	if (tcap->command[position] != ' ')
		while (tcap->command[position] != ' ')
			position--;
	ft_move(tcap, "left", ((tcap->cursx - tcap->prompt_len) - position) - 1);
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
