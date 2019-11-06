/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtin_editor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:37:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/11/06 17:56:02 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		write_in_file(char *file, int index, int max)
{
	int fd;
	t_history *history;

	if (!(fd = open(file, O_RDWR | O_TRUNC |O_CREAT, 0666)))
		return (1);
	history = g_shell->history;
	if (!~index && !~max)
	{
		index = g_shell->history->len - 2;
		max = index + 1;
	}
	if (max > index)
	{
		while (max >= index)
		{
			ft_putstr_fd(history->data[max], fd);
			ft_putchar_fd(10, fd);
			max--;
		}
	}
	else
	{
		while (max <= index)
		{
			ft_putstr_fd(history->data[max], fd);
			ft_putchar_fd(10, fd);
			max++;
		}
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
		return (1);
	while ((ret = get_next_line(fd, &line, '\n')))
	{
		if (!(string = ft_strnew(ft_strlen(line) + 1)))
			return (1);
		ft_strcpy(string, line);
		string[ft_strlen(string)] = '\n';
		lex_del_list(&g_shell->lexer);
		ft_putstr(string);
		handler(string);
		if (!~add_cmd_to_history(string, g_shell->history))
			return (0);
		ft_strdel(&line);
	}
	close(fd);
	remove(file);
	return (1);
}

char **init_editor(char *arg, char *path_random)
{
	char **bin;
	char *path;
	char *editor;
	char **editors;

	if (!(editor = ft_strcjoin(arg, path_random, ' ')))
		return (NULL);
	if (!(editors = ft_strsplit(editor, ' ')))
		return (NULL);
	ft_printf("ok la\n");
	if (!(path = get_all_key_value("PATH", g_shell->env_tmp)))
		return (NULL);
	if (!(bin = ft_strsplit(path, ':')))
		return (NULL);
	if (!(editors[0] = (char *)add_path(bin, (unsigned char *)editors[0])))
		return (NULL);
	ft_strdel(&editor);
	ft_splitdel(bin);
	return (editors);
}

int		exec_command(char *arg, int index, int max)
{
	char **editor;
	int pid;
	int status;
	char *path;

	if (!(path = randomize_path("/tmp")))
		return (1);
	if (!(editor = init_editor(arg, path)))
	{
		ft_putstr_fd("Erreur d'allocation dans init_editor\n", 2);
		return (1);
	}

	write_in_file(path , index, max);
	if (!(pid = fork()) && !~execve(editor[0], editor, g_shell->env_tmp))
	{
		ft_printf("42sh: unable to launch command %s [%d]\n", editor[0], errno);
		exit(1);
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status) && !WEXITSTATUS(status))
			read_file(path);
		else
		{
			ft_putstr_fd("42sh: fc command not found: ", 2);
			ft_putstr_fd(editor[0], 2);
			ft_putchar_fd(10, 2);
		}
	}
	return (1);
}


static int			get_editor_history_index(int x, int y, int p, char *editor)
{
	int			index;
	int			max;
	int			tmp;
	t_history	*history;

	history = g_shell->history;
	max = ~y ? ft_max(0, x) : history->len - 1;
	index = ~y ? ft_max(0, y) : x;
	if (max >= history->len || index >= history->len)
		return (-2);
	else if (!x || !y)
		return (-3);
	if (p & FC_REVERSE)
	{
		tmp = max;
		max = index;
		index = tmp;
	}
	exec_command(editor, index, max);
	return (0);
}

int		fc_editor_multi_arg(char *editor, char *av1, char *av2, int param)
{
	int index;
	int max;

	arg_to_number(av1, av2, &index, &max);
	get_editor_history_index(index, max, param, editor);
	return 1;
}

int		fc_editor(int argc, char **argv, int param)
{
	int i = 1;
	while (i < argc && argv[i][0] == '-' && !~ft_indexof(argv[i], 'e'))
		i++;
	while (i < argc && argv[i + 1] && argv[i + 1][0] == '-' && argv[i + 1][1] == 'e')
		i++;
	if (argc - 1 > i && argv[i + 1][0] == '-')
		return (ft_printf("erreur param apres -e\n") ? 1 : 1);
	if (i == argc - 1)
		return (ft_printf("Aucun argument pour -e\n") ? 1 : 1);
	else
	{
		i++;
		if (argc - 1 > i)
			fc_editor_multi_arg(argv[i], argv[i + 1],
								argc - 1 - i == 2 ? argv[i + 2] : NULL, param);
		else
			exec_command(argv[i], -1, -1);
	}
	return (0);
}
