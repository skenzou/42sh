/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:31:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/07 00:48:15 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	add_to_cmd(char buffer[4], int pos, int len)
{
	int i;

	i = 0;
	if (pos == -1)
		pos = ft_strlen(g_curs.command);
	if (len == 1)
	{
		while (i < 3)
		{
			if (ft_isprint(buffer[i]))
			{
				len++;
				g_curs.x++;
			}
			i++;
		}
	}
	else
		g_curs.x += wcharlen(buffer[0]) - 1;
	g_curs.last = g_curs.x;
	ft_strncpy(g_curs.command + pos, buffer, len);
}

int			read_buffer(char buffer[4])
{
	char key;

	if (is_arrow(buffer))
		return (read_arrow(buffer[2]));
	else if ((key = is_shift_arrow(buffer)) != -1)
		return (read_arrow(key + 10));
	else if ((key = is_key(buffer)) != -1)
		return (read_key(key));
	else if (DEBUG_LOG)
		ft_printf("%c|%hhd", buffer[0], buffer[0]);
	return (1);
}
