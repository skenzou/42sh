/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 00:20:29 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/04 23:53:31 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		home_event(t_cap *tcap)
{
	if (tcap->cursx == tcap->prompt_len && (!tcap->cursy))
		return (1);
	ft_move(tcap, "up", 1);
	ft_move(tcap, "down", 1);
	while (tcap->cursy)
	{
		tcap->cursx = 0;
		tcap->cursy--;
		ft_move(tcap, "up", 1);
	}
	ft_move(tcap, "!right", tcap->prompt_len);
	tcap->cursx = tcap->prompt_len;
	return (1);
}

int		end_event(t_cap *tcap)
{
	int i;
	int reste;
	int y_reste;

	if (tcap->char_len + tcap->prompt_len > (tcap->cursx_max))
	{
		reste = tcap->char_len - (tcap->cursx_max - tcap->prompt_len) - 1;
		y_reste = reste / ft_max(tcap->cursx_max, 1);
		if (tcap->cursx < (tcap->cursx_max - 1) && !tcap->cursy)
		{
			ft_move(tcap, "down", 1);
			tcap->cursy++;
			tcap->cursx = 0;
		}
		i = tcap->cursy - 2;
		while (++i < y_reste)
		{
			ft_move(tcap, "down", 1);
			tcap->cursy++;
			tcap->cursx = 0;
		}
		ft_move(tcap, "right", ((reste % ft_max(tcap->cursx_max, 1)) - y_reste)
																- tcap->cursx);
	}
	else
		ft_move(tcap, "right", tcap->char_len - (tcap->cursx - tcap->prompt_len));
	return (1);
}
