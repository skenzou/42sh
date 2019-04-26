/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 21:23:47 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/26 13:35:54 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		get_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (ECHO);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (CD);
	else if (ft_strcmp(cmd, "setenv") == 0)
		return (SETENV);
	else if (ft_strcmp(cmd, "unsetenv") == 0)
		return (UNSETENV);
	else if (ft_strcmp(cmd, "env") == 0)
		return (ENV);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (EXIT);
	return (0);
}

static void		exec_builtin(char **builtin, int id, char ***env)
{
	int	ac;
	int	err_id;

	ac = ft_split_count(builtin);
	err_id = 0;
	if (id == ECHO)
		err_id = echo_builtin(ac, builtin);
	if (id == CD)
		err_id = cd_builtin(ac, builtin, env);
	if (id == ENV && ac == 1)
		print_env(*env);
	if (id == SETENV)
		err_id = setenv_builtin(ac, builtin, env);
	if (id == UNSETENV)
		err_id = unsetenv_builtin(ac, builtin, env);
	if (id == EXIT)
		exit_builtin();
	if (err_id != 0)
		err_handler(err_id, builtin[0]);
}

void			cmd_handler(char *cmd, char ***env)
{
	char	**args;
	int		id;
	int		i;

	if (!(args = ft_strsplitstr(cmd, " \t")))
		exit(1);
	if (ft_split_count(args) > 0)
	{
		i = -1;
		while (args[++i])
			manage_expansions(&args[i], *env);
		id = get_builtin(args[0]);
		if (id > 0)
			exec_builtin(args, id, env);
		else
			exec_bin(args, *env);
	}
	ft_splitdel(args);
}
