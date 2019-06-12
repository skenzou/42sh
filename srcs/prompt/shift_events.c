/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:04:00 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/04 23:54:58 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		shift_arrow_up_event(t_cap *tcap)
{
	if (!tcap->cursy || tcap->char_len + tcap->prompt_len < tcap->cursx_max + 2)
		tputs(tcap->sound, 1, ft_put_termcaps);
	else if (tcap->cursy == 1)
	{
		if (tcap->cursx >= tcap->prompt_len)
		{
			ft_move(tcap, "up", 1);
			tcap->cursy--;
		}
		else
			home_event(tcap);
	}
	else
	{
		ft_move(tcap, "up", 1);
		tcap->cursy--;
	}
	return (1);
}

int		shift_arrow_down_event(t_cap *tcap)
{
	int p;
	int ligne;

	p = tcap->cursy * (tcap->cursx_max + 1) + (tcap->cursx) - tcap->prompt_len;
	ligne = (tcap->char_len - p) - (tcap->cursx_max + 1 - tcap->cursx);
	if (tcap->char_len + tcap->prompt_len < tcap->cursx_max + 2 || ligne < 0)
		tputs(tcap->sound, 1, ft_put_termcaps);
	else
	{
		ft_move(tcap, "down", 1);
		tcap->cursy++;
		if (tcap->cursx <= ligne)
			ft_move(tcap, "!right", tcap->cursx);
		else
		{
			ft_move(tcap, "!right", ligne);
			tcap->cursx = ligne;
		}
	}
	return (1);
}

int		shift_arrow_right_event(t_cap *tcap)
{
	int p;

	p = tcap->cursy * (tcap->cursx_max + 1) + (tcap->cursx) - tcap->prompt_len;
	if (p == tcap->char_len)
	{
		tputs(tcap->sound, 1, ft_put_termcaps);
		return (1);
	}
	while (tcap->command[p] && tcap->command[p] != ' ')
	{
		ft_move(tcap, "right", 1);
		p++;
	}
	while (tcap->command[p] == ' ')
	{
		ft_move(tcap, "right", 1);
		p++;
	}
	return (1);
}

int		shift_arrow_left_event(t_cap *tcap)
{
	int p;

	p = tcap->cursy * (tcap->cursx_max + 1) + (tcap->cursx) - tcap->prompt_len;

	if (p)
	{
		ft_move(tcap, "left", 1);
		p--;
	}
	else
	{
		tputs(tcap->sound, 1, ft_put_termcaps);
		return (1);
	}
	while (p && tcap->command[p] == ' ')
	{
		ft_move(tcap, "left", 1);
		p--;
	}
	while (p && tcap->command[p] && tcap->command[p] != ' ')
	{
		ft_move(tcap, "left", 1);
		p--;
	}
	p && ft_move(tcap, "right", 1);
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
