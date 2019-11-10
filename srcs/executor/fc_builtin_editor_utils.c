/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtin_editor_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 01:41:47 by aben-azz          #+#    #+#             */
/*   Updated: 2019/11/10 16:51:44 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		write_in_file(char *file, int index, int max)
{
	int			fd;
	t_history	*history;

	if (!(fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0666)))
		return (handle_error(FC_CANT_OPEN));
	history = g_shell->history;
	if (!~index && !~max && (index = g_shell->history->len - 2))
		max = index + 1;
	if (max > index)
		while (max >= index)
		{
			ft_putstr_fd(history->data[max], fd);
			ft_putchar_fd(10, fd);
			max--;
		}
	else
		while (max <= index)
		{
			ft_putstr_fd(history->data[max], fd);
			ft_putchar_fd(10, fd);
			max++;
		}
	close(fd);
	return (0);
}

int		read_file(char *file)
{
	int		ret;
	int		fd;
	char	*line;
	char	*string;

	if (!(fd = open(file, O_RDONLY, 0666)))
		return (handle_error(FC_CANT_OPEN));
	while ((ret = get_next_line(fd, &line, '\n')))
	{
		if (!(string = ft_strnew(ft_strlen(line) + 1)))
			return (handle_error(FC_MALLOC_ERR));
		ft_strcpy(string, line);
		string[ft_strlen(string)] = '\n';
		lex_del_list(&g_shell->lexer);
		ft_putstr(string);
		handler(string);
		if (!~add_cmd_to_history(string, g_shell->history))
			return (handle_error(FC_MALLOC_ERR));
		ft_strdel(&line);
		ft_strdel(&string);
	}
	close(fd);
	remove(file);
	return (0);
}
