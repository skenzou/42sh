/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:45:36 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/01 21:16:41 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

t_history *g_history;

int	add_cmd_to_history(char *string)
{
	ft_printf("ajout de : %s\n", string);
	if (g_history->len)
		if (!ft_strcmp(string, g_history->history[g_history->len - 1]))
			return (1);
	if (!(g_history->history[g_history->len++] = ft_strdup(string)))
		return (0);
	g_history->history[g_history->len] = NULL;
	if (!write_history(string))
		return (-1);
	return (1);
}

int	debug_history(void)
{
	int i;

	i = 0;
	ft_printf("Len of history: %d;\n", g_history->len);
	while (g_history->history[i])
	{
		ft_printf("[%d]:  '%s';\n", i, g_history->history[i]);
		i++;
	}
	return (1);
}

int	init_history(void)
{
	if (!(g_history = malloc(sizeof(t_history))))
		return (-1);
	g_history->len = 0;
	g_history->history[0] = NULL;
	g_history->read = 0;
	if (read_history() == -1)
		return (-1);
	return (1);
}

int	write_history(char *string)
{
	int fd;

	fd = open(HISTORY_FILE_NAME, O_RDWR | O_APPEND | O_CREAT, 0666);
	if (fd > 0)
	{
		ft_dprintf(fd, "%s#", string);
		close(fd);
		return (1);
	}
	else
	{
		ft_dprintf(2, "21sh: History:  Error opening file\n");
	}
	return (-1);
}

int	read_history(void)
{
	char		*str;
	int			ret;
	int			fd;

	fd = open(HISTORY_FILE_NAME, O_RDWR | O_APPEND | O_CREAT, 0666);
	if (fd > 0)
	{
		while ((ret = get_next_line(fd, &str, '#')) > 0)
		{
			g_history->read++;
			if (!(g_history->history[g_history->len++] = ft_strdup(str)))
				return (-1);
		}
	}
	ft_strdel(&str);
	close(fd);
	return (1);
}
