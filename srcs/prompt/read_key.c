/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:30:02 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/25 23:50:45 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_key(char key[3])
{
	if (key[0] == HOME_END1 && key[1] == HOME_END2)
	{
		if (key[2] == HOME || key[2] == END)
			return (key[2]);
		else
			return (-1);
	}
	else if (key[0] == ENTER || key[0] == BACKSPACE || key[0] == CTRL_R ||
						key[0] == CTRL_D || key[0] == TAB || key[0] == SPACE)
		return (key[0]);
	else
		return (-1);
}

int		read_key(char buffer, t_cap *tcap)
{
	int i;

	i = -1;
	while (g_key_event[++i].key)
		if (g_key_event[i].key == buffer && g_key_event[i].function)
			return (g_key_event[i].function(tcap));
	return (1);
}
