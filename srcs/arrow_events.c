/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:04:00 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/01 17:20:24 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		arrow_up_event(t_curs *curseur)
{
	ft_printf("{U}");
	curseur->x += 3;
	return (1);
}

int		arrow_down_event(t_curs *curseur)
{
	ft_printf("{D}");
	curseur->x += 3;
	return (1);
}

int		arrow_right_event(t_curs *curseur)
{
	tputs(tgoto(tgetstr("RI", NULL), 1, UNUSED), 0, ft_put_termcaps);
	curseur->x++;
	return (1);
}

int		arrow_left_event(t_curs *curseur)
{
	if (curseur->x != 0)
	{
		tputs(tgoto(tgetstr("LE", NULL), 1, UNUSED), 0, ft_put_termcaps);
		curseur->x--;
	}
	return (1);
}

int		shift_arrow_up_event(t_curs *curseur)
{
	ft_printf("{LU}");
	curseur->x += 3;
	return (1);
}

int		shift_arrow_down_event(t_curs *curseur)
{
	ft_printf("{LD}");
	curseur->x += 3;
	return (1);
}

int		shift_arrow_right_event(t_curs *curseur)
{
	ft_printf("{LR}");
	curseur->x += 3;
	return (1);
}

int		shift_arrow_left_event(t_curs *curseur)
{
	ft_printf("{LL}");
	curseur->x += 3;
	return (1);
}
