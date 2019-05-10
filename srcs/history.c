/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:45:36 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/10 09:00:19 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int	add_cmd_to_history(char *str, t_history *history)
{
	if (history->len)
		if (!ft_strcmp(str, history->data[history->len - 1]))
			return (1);
	if (!(history->data[history->len++] = ft_strdup(str)))
		return (0);
	history->data[history->len] = NULL;
	if (!write_history(str, history))
		return (-1);
	return (1);
}

int	debug_history(t_history *history)
{
	int i;

	i = 0;
	ft_printf("Len of history: %d;\n", history->len);
	while (history->data[i])
	{
		ft_printf("[%d]:  '%s';\n", i, history->data[i]);
		i++;
	}
	return (1);
}

int	write_history(char *string, t_history *history)
{
	int fd;

	fd = open(history->file_name, O_RDWR | O_APPEND | O_CREAT, 0666);
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

int	read_history(t_history *history)
{
	char		*str;
	int			ret;
	int			fd;

	fd = open(history->file_name, O_RDWR | O_APPEND | O_CREAT, 0666);
	if (fd > 0)
	{
		while ((ret = get_next_line(fd, &str, '#')) > 0)
		{
			history->read++;
			if (!(history->data[history->len++] =
					ft_strdup(str)))
				return (-1);
		}
	}
	close(fd);
	return (1);
}
