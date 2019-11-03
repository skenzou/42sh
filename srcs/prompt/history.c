/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:45:36 by aben-azz          #+#    #+#             */
/*   Updated: 2019/11/03 05:26:18 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	add_cmd_to_history(char *str, t_history *history)
{
	if (history->len)
		if (!ft_strcmp(str, history->data[history->len - 1]))
			return (1);
	if (!(history->data[history->len++] = ft_strdup(str)))
		return (0);
	history->data[history->len - 1][ft_strlen(str) - 1] = '\0';
	history->data[history->len] = NULL;
	if (!write_history(str, history))
		return (-1);
	return (1);
}

int	history_builtin(int argc, char **argv)
{
	t_history	*history;
	int			i;

	(void)argc;
	(void)argv;
	i = -1;
	history = g_shell->history;
	ft_printf("Len of history: %d\n", history->len);
	while (history->data[++i])
		ft_printf("[%d]:\t'%s'\n", i, history->data[i]);
	return (1);
}

int	write_history(char *string, t_history *history)
{
	int fd;

	if (!ft_strlen(string) || !ft_strcmp(string, " \n") ||
		!ft_strcmp(string, "\n"))
		return (1);
	fd = open(history->file_name, O_RDWR | O_APPEND | O_CREAT, 0666);
	if (fd > 0)
	{
		write(fd, string, ft_strlen(string) - 1);
		ft_putchar_fd(1, fd);
		close(fd);
		return (1);
	}
	return (-1);
}

int	read_history(t_history *history)
{
	char		*str;
	int			ret;
	int			fd;

	str = NULL;
	if ((fd = open(history->file_name, O_RDWR | O_APPEND | O_CREAT, 0666)) > 0)
	{
		while ((ret = get_next_line(fd, &str, 1)) > 0)
		{
			history->read++;
			if (!(history->data[history->len++] = ft_strdup(str)))
			{
				ft_strdel(&str);
				return (-1);
			}
			ft_strdel(&str);
		}
		close(fd);
	}
	return (1);
}
