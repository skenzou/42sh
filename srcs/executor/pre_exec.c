/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:50:03 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/24 14:16:41 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		get_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (ECHO_BUILTIN);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (CD_BUILTIN);
	else if (ft_strcmp(cmd, "setenv") == 0)
		return (SETENV_BUILTIN);
	else if (ft_strcmp(cmd, "unsetenv") == 0)
		return (UNSETENV_BUILTIN);
	else if (ft_strcmp(cmd, "env") == 0)
		return (ENV_BUILTIN);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (EXIT_BUILTIN);
	return (0);
}

static void		exec_builtin(char **builtin, int id, char ***env)
{
	int	ac;
	int	err_id;

	ac = ft_split_count(builtin);
	err_id = 0;
	if (id == ECHO_BUILTIN)
		err_id = echo_builtin(ac, builtin);
	if (id == CD_BUILTIN)
		err_id = cd_builtin(ac, builtin, env);
	if (id == ENV_BUILTIN && ac == 1)
		print_env(*env);
	if (id == SETENV_BUILTIN)
		err_id = setenv_builtin(ac, builtin, env);
	if (id == UNSETENV_BUILTIN)
		err_id = unsetenv_builtin(ac, builtin, env);
	if (id == EXIT_BUILTIN)
		exit_builtin();
	if (err_id != 0)
		err_handler(err_id, builtin[0]);
}

int		ft_pre_execution(char ***args, int redir)
{
	int err;
	int id;

	err = 0;
	if (redir)
		*args = handle_redir();
	ft_expand(*args);
	id = get_builtin((*args)[0]);
	if (id)
	{
		exec_builtin(*args, id, &g_shell->env);
		err = -1;
	}
	else
	{
		if (is_path((*args)[0]))
			err = check_file((*args)[0]);
		else
			err = hash_table(&((*args)[0]), g_shell->env);
	}
	if (err && err != -1)
		err_handler(err, (*args)[0]);
	return (err);
}
