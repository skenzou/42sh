/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 00:20:29 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/22 20:24:10 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		home_event(t_cap *tc)
{
	if (tc->cursx == tc->prompt_len && (!tc->cursy))
		return (1);
	ft_move(tc, "up", 1);
	ft_move(tc, "down", 1);
	while (tc->cursy)
	{
		tc->cursx = 0;
		tc->cursy--;
		ft_move(tc, "up", 1);
	}
	ft_move(tc, "!right", tc->prompt_len);
	tc->cursx = tc->prompt_len;
	return (1);
}

int		end_event(t_cap *tc)
{
	int i;
	int reste;
	int y_reste;

	if (!(tc->char_len + tc->prompt_len > (tc->cursx_max)))
		return
		(ft_move(tc, "right", tc->char_len - (tc->cursx - tc->prompt_len)));
	reste = tc->char_len - (tc->cursx_max - tc->prompt_len) - 1;
	y_reste = reste / ft_max(tc->cursx_max, 1);
	if (tc->cursx < (tc->cursx_max - 1) && !tc->cursy)
	{
		ft_move(tc, "down", 1);
		tc->cursy++;
		tc->cursx = 0;
	}
	i = tc->cursy - 2;
	while (++i < y_reste)
	{
		ft_move(tc, "down", 1);
		tc->cursy++;
		tc->cursx = 0;
	}
	ft_move(tc, "right", ((reste % ft_max(tc->cursx_max, 1)) - y_reste)
															- tc->cursx);
	return (1);
}
