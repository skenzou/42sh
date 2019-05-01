/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:31:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/01 17:21:11 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static char	is_shift_arrow(char key[4])
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

static int	is_arrow(char key[4])
{
	if (key[0] == ARROW_CODE1 && key[1] == ARROW_CODE2)
		return (key[2] == RIGHT || key[2] == UP || key[2] == LEFT ||
																key[2] == DOWN);
	else
		return (0);
	return (0);
}

static int	is_key(char key[3])
{
	if (key[0] == HOME_END1 && key[1] == HOME_END2)
	{
		if (key[2] == HOME || key[2] == END)
			return (key[2]);
		else
			return (-1);
	}
	else if (key[0] == ENTER || key[0] == BACKSPACE || key[0] == CTRL_R ||
															key[0] == TAB)
		return (key[0]);
	else
		return (-1);
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
	//ft_printf("key: %d\n", buffer);
	int i;

	i = -1;
	while (g_key_event[++i].key)
		if (g_key_event[i].key == buffer && g_key_event[i].function)
			return (g_key_event[i].function(curseur, c));
	return (1);
}

int			read_buffer(char buffer[5], t_curs *curseur, char *cmd, int unicode)
{
	char key;

	//ft_printf("key: {%d, %d, %d}\n", buffer[0], buffer[1], buffer[2]);
	if (is_arrow(buffer))
		return (read_arrow(buffer[2], curseur));
	else if ((key = is_shift_arrow(buffer)) != -1)
		return (read_arrow(key + 10, curseur));
	else if ((key = is_key(buffer)) != -1)
		return (read_key(key, curseur, cmd));
	else if (ft_isprint(buffer[0]) || unicode)
	{
		cmd[curseur->x += wcharlen(buffer[0])] = buffer[0];
		ft_printf("%s", buffer);
		return (1);
	}
	else if (DEBUG_LOG)
		ft_printf("%c|%hhd", buffer[0], buffer[0]);
	return (1);
}
