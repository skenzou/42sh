/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:31:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/01 16:16:09 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int	is_arrow(char key[4])
{
	if (key[0] == ARROW_CODE1 && key[1] == ARROW_CODE2)
		return (key[2] == RIGHT || key[2] == UP || key[2] == LEFT ||
																key[2] == DOWN);
	else
		return (0);
	return (0);
}

static int	is_key(int key)
{
	return (key == ENTER || key == BACKSPACE);
}

static int	read_arrow(char buffer, t_curs *curseur)
{
	int i;

	i = -1;
	while (g_arrow_event[++i].key)
		if (g_arrow_event[i].key == buffer && g_arrow_event[i].function)
			return (g_arrow_event[i].function(curseur));
	return (1);
}

static int	read_key(char buffer, t_curs *curseur, char *c)
{
	int i;

	i = -1;
	while (g_key_event[++i].key)
		if (g_key_event[i].key == buffer && g_key_event[i].function)
			return (g_key_event[i].function(curseur, c));
	return (1);
}

int			read_buffer(char buffer[5], t_curs *curseur, char *cmd, int unicode)
{
	if (is_arrow(buffer))
		return (read_arrow(buffer[2], curseur));
	else if (is_key(buffer[0]))
		return (read_key(buffer[0], curseur, command));
	else if (ft_isprint(buffer[0]) || unicode)
	{
		command[curseur->x += wcharlen(buffer[0])] = buffer[0];
		ft_printf("%s", buffer);
		return (1);
	}
	else
		ft_printf("%c|%hhd", buffer[0], buffer[0]);
	return (1);
}
