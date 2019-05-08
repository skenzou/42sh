/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:04:00 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/08 02:43:42 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		arrow_up_event(t_cap *tcap)
{
	ft_printf("{U}");
	tcap->cursx += 3;
	return (1);
}

int		arrow_down_event(t_cap *tcap)
{
	ft_printf("{D}");
	tcap->cursx += 3;
	return (1);
}

int		arrow_right_event(t_cap *tcap)
{
	if (tcap->cursx < tcap->char_len)
	{
		tputs(tgoto(tgetstr("RI", NULL), 1, UNUSED), 0, ft_put_termcaps);
		tcap->cursx++;
	}
	return (1);
}

int		arrow_left_event(t_cap *tcap)
{
	if (tcap->cursx != 0)
	{
		tputs(tgoto(tgetstr("LE", NULL), 1, UNUSED), 0, ft_put_termcaps);
		tcap->cursx--;
	}
	return (1);
}

int		shift_arrow_up_event(t_cap *tcap)
{
	ft_printf("{LU}");
	tcap->cursx += 3;
	return (1);
}

int		shift_arrow_down_event(t_cap *tcap)
{
	ft_printf("{LD}");
	tcap->cursx += 3;
	return (1);
}

int		shift_arrow_right_event(t_cap *tcap)
{
	ft_printf("{LR}");
	tcap->cursx += 3;
	return (1);
}

int		shift_arrow_left_event(t_cap *tcap)
{
	ft_printf("{LL}");
	tcap->cursx += 3;
	return (1);
}
