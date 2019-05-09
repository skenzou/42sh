/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_arrow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:31:35 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/09 07:01:50 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	is_shift_arrow(char key[4])
{
	char	k[4];

	if (key[0] == SHIFT_CODE1 && key[1] == SHIFT_CODE2 && key[2] == SHIFT_CODE3)
	{
		ft_bzero(k, 4);
		read(0, &k, 3);
		if (k[0] == ARROW_CODE3 && k[1] == ARROW_CODE4)
			if (k[2] == RIGHT || k[2] == UP || k[2] == LEFT || k[2] == DOWN)
				return (k[2]);
	}
	else
		return (-1);
	return (-1);
}

int		is_arrow(char key[4])
{
	if (key[0] == ARROW_CODE1 && key[1] == ARROW_CODE2)
		return (key[2] == RIGHT || key[2] == UP || key[2] == LEFT ||
																key[2] == DOWN);
	else
		return (0);
	return (0);
}

int		read_arrow(char buffer, t_cap *tcap)
{
	int i;

	i = -1;
	while (g_arrow_event[++i].key)
		if (g_arrow_event[i].key == buffer && g_arrow_event[i].function)
			return (g_arrow_event[i].function(tcap));
	return (1);
}
