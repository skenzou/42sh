/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtin_editor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:37:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/23 14:15:28 by tlechien         ###   ########.fr       */
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
			//ft_printf("on ecrit: %s dans fd\n", history->data[i]);
			max--;
		}
	}
	else
	{
		while (max <= index)
		{
			ft_putstr_fd(history->data[max], fd);
			ft_putchar_fd(10, fd);
			//ft_printf("on ecrit: %s dans fd\n", history->data[i]);
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

char **init_editor(char *arg)
{
	char **bin;
	char *path;
	char *editor;
	char **editors;

	if (!(editor = ft_strcjoin(arg, "/tmp/42shtmp", ' ')))
		return (NULL);
	if (!(editors = ft_strsplit(editor, ' ')))
		return (NULL);
	if (!(path = get_all_key_value("PATH", g_shell->env_tmp)))
		return (NULL);
	if (!(bin = ft_strsplit(path, ':')))
		return (NULL);
	if (!(editors[0] = (char *)add_path(bin, (unsigned char *)editors[0])))
		return (NULL);
	return (editors);
}
int		exec_command(char *arg, int index, int max)
{
	char **editor;
	int pid;
	int status;

	if (!(editor = init_editor(arg)))
		ft_putstr_fd("Erreur d'allocation dans init_editor", 2);
	write_in_file("/tmp/42shtmp", index, max);
	if (!(pid = fork()) && !~execve(editor[0], editor, g_shell->env_tmp))
	{
		ft_printf("42sh: unable to launch command %s [%d]\n", editor[0], errno);
		exit(1);
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status) && !WEXITSTATUS(status))
			read_file("/tmp/42shtmp");
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
	char *fcedit;

	fcedit = get_all_key_value("FCEDIT", g_shell->env_tmp);
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
