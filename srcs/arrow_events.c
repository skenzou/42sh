/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:04:00 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/07 00:48:09 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		arrow_up_event()
{
	ft_printf("{U}");
	g_curs.x += 3;
	return (1);
}

int		arrow_down_event()
{
	ft_printf("{D}");
	g_curs.x += 3;
	return (1);
}

int		arrow_right_event()
{
	if (g_curs.x < g_curs.last)
	{
		tputs(tgoto(tgetstr("RI", NULL), 1, UNUSED), 0, ft_put_termcaps);
		g_curs.x++;
	}
	return (1);
}

int		arrow_left_event()
{
	if (g_curs.x != 0)
	{
		tputs(tgoto(tgetstr("LE", NULL), 1, UNUSED), 0, ft_put_termcaps);
		g_curs.x--;
	}
	return (1);
}

int		shift_arrow_up_event()
{
	ft_printf("{LU}");
	g_curs.x += 3;
	return (1);
}

int		shift_arrow_down_event()
{
	ft_printf("{LD}");
	g_curs.x += 3;
	return (1);
}

int		shift_arrow_right_event()
{
	ft_printf("{LR}");
	g_curs.x += 3;
	return (1);
}

int		shift_arrow_left_event()
{
	ft_printf("{LL}");
	g_curs.x += 3;
	return (1);
}
