/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:31:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/04/28 15:46:15 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int	is_arrow(int key)
{
	return (key == ARROW_RIGHT || key == ARROW_UP ||
		key == ARROW_LEFT || key == ARROW_DOWN);
}

static int	is_key(int key)
{
	return (key == ENTER || key == BACKSPACE);
}

static int	read_arrow(int buffer, t_curs *curseur)
{
	int i;

	i = -1;
	while (g_arrow_event[++i].key)
		if (g_arrow_event[i].key == buffer && g_arrow_event[i].function)
			return (g_arrow_event[i].function(curseur));
	return (1);
}

static int	read_key(int buffer, t_curs *curseur, char *c)
{
	int i;

	i = -1;
	while (g_key_event[++i].key)
		if (g_key_event[i].key == buffer && g_key_event[i].function)
			return (g_key_event[i].function(curseur, c));
	return (1);
}

int			read_buffer(int buffer, t_curs *curseur, char *command)
{
	if (ft_isprint(buffer))
	{
		command[curseur->x++] = buffer;
		ft_printf("%c", buffer);
		return (1);
	}
	else if (is_arrow(buffer))
		return (read_arrow(buffer, curseur));
	else if (is_key(buffer))
		return (read_key(buffer, curseur, command));
	return (1);
}
