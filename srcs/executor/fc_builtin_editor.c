/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtin_editor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:37:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/11/10 18:12:38 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**init_editor(char *arg, char *path_random)
{
	char **bin;
	char *path;
	char *editor;
	char **editors;

	if (!(editor = ft_strcjoin(arg, path_random, ' '))
				&& handle_error(FC_MALLOC_ERR))
		return (NULL);
	if (!(editors = ft_strsplit(editor, ' '))
				&& handle_error(FC_MALLOC_ERR))
		return (NULL);
	if (!(path = get_all_key_value("PATH", g_shell->env_tmp))
				&& handle_error(FC_NO_PATH))
		return (NULL);
	if (!(bin = ft_strsplit(path, ':'))
				&& handle_error(FC_MALLOC_ERR))
		return (NULL);
	if (!(editors[0] = (char *)add_path(bin, (unsigned char *)editors[0]))
				&& handle_error(FC_BIN_NFOUND))
		return (NULL);
	ft_strdel(&editor);
	ft_splitdel(bin);
	return (editors);
}

int			exec_command(char *arg, int index, int max)
{
	char	**editor;
	int		pid;
	int		status;
	char	*path;

	if ((!(path = randomize_path("/tmp")) && handle_error(FC_MALLOC_ERR)) ||
		!(editor = init_editor(arg, path)) || write_in_file(path, index, max))
		return (1);
	if (!(pid = fork()) && !~execve(editor[0], editor, g_shell->env_tmp))
	{
		exit(ft_printf("42sh: fc: unable to launch command %s [%d]\n",
				editor[0], errno) || 1);
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status) && !WEXITSTATUS(status))
			status = read_file(path);
		else
			status = ft_printf("42sh: fc: command not found: %s\n", editor[0]);
	}
	ft_splitdel(editor);
	ft_strdel(&path);
	return (status);
}

static int	index_to_exec(int tindex, int tmax, int p, char *editor)
{
	int			index;
	int			max;
	int			tmp;
	t_history	*history;

	history = g_shell->history;
	max = ~tmax ? ft_max(0, tindex) : tindex;
	index = ~tmax ? ft_max(0, tmax) : history->len - 2;
	if (max >= history->len || index >= history->len)
		return (-2);
	else if (!tindex || !tmax)
		return (-3);
	if (p & FC_REVERSE)
	{
		tmp = max;
		max = index;
		index = tmp;
	}
	return (exec_command(editor, index, max));
}

int			fc_editor_multi_arg(char *editor, char *av1, char *av2, int param)
{
	int		index;
	int		max;
	char	*it;

	if (!(it = ft_itoa(ft_max(g_shell->history->len - 2, 0))))
		return (handle_error(FC_MALLOC_ERR));
	if (!av1)
		arg_to_number(it, av2, &index, &max);
	else
		arg_to_number(av1, av2, &index, &max);
	ft_strdel(&it);
	return (index_to_exec(index, max, param, editor));
}

int			fc_editor(int argc, char **av, int param)
{
	int			i;
	t_history	*history;

	history = g_shell->history;
	i = 1;
	while (i < argc && av[i][0] == '-' && !~ft_indexof(av[i], 'e'))
		i++;
	while (i < argc && av[i + 1] && av[i + 1][0] == '-' && av[i + 1][1] == 'e')
		i++;
	if (argc - 1 > i && av[i + 1][0] == '-')
		return (handle_error(FC_ERR_PARAM));
	if (i == argc - 1)
		return (handle_error(FC_NO_ARG_E));
	else
	{
		i++;
		if (argc - 1 > i)
			i = fc_editor_multi_arg(av[i], av[i + 1],
								argc - 1 - i == 2 ? av[i + 2] : NULL, param);
		else
			i = exec_command(av[i], (history->len - 2), (history->len - 2));
	}
	return (i);
}
