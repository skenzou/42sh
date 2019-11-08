/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtin_editor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:37:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/11/08 12:04:10 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**init_editor(char *arg, char *path_random)
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

int			exec_command(char *arg, int index, int max)
{
	char	**editor;
	int		pid;
	int		status;
	char	*path;

	if (!(path = randomize_path("/tmp")) ||
		!(editor = init_editor(arg, path)))
		return (1);
	write_in_file(path, index, max);
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
			ft_printf("42sh: fc command not found: %s\n", editor[0]);
	}
	ft_splitdel(editor);
	ft_strdel(&path);
	return (1);
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
	exec_command(editor, index, max);
	return (0);
}

int			fc_editor_multi_arg(char *editor, char *av1, char *av2, int param)
{
	int index;
	int max;
	char *it;

	if (!(it = ft_itoa(ft_max(g_shell->history->len - 2, 0))))
		return (0);
	if (!ft_strcmp(av1, "noarg"))
		arg_to_number(it, av2, &index, &max);
	else
		arg_to_number(av1, av2, &index, &max);
	index_to_exec(index, max, param, editor);
	ft_strdel(&it);
	return (1);
}

int			fc_editor(int argc, char **av, int param)
{
	int i;

	i = 1;
	while (i < argc && av[i][0] == '-' && !~ft_indexof(av[i], 'e'))
		i++;
	while (i < argc && av[i + 1] && av[i + 1][0] == '-' && av[i + 1][1] == 'e')
		i++;
	if (argc - 1 > i && av[i + 1][0] == '-')
		return (ft_printf("erreur param apres -e\n") ? 1 : 1);
	if (i == argc - 1)
		return (ft_printf("Aucun argument pour -e\n") ? 1 : 1);
	else
	{
		i++;
		if (argc - 1 > i)
			fc_editor_multi_arg(av[i], av[i + 1],
								argc - 1 - i == 2 ? av[i + 2] : NULL, param);
		else
			exec_command(av[i], -1, -1);
	}
	return (0);
}
