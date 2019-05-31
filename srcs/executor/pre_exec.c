/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:50:03 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/31 20:37:43 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		get_builtin(char *cmd)
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
	else if (ft_strcmp(cmd, "set") == 0)
		return (SET_BUILTIN);
	else if (ft_strcmp(cmd, "export") == 0)
		return (EXPORT_BUILTIN);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (UNSET_BUILTIN);
	else if (ft_strcmp(cmd, "jobs") == 0)
		return (JOBS_BUILTIN);
	else if (ft_strcmp(cmd, "type") == 0)
		return (TYPE_BUILTIN);
	else if (ft_strcmp(cmd, "test") == 0)
		return (TEST_BUILTIN);
	return (0);
}

int		ft_pre_execution(char ***args, int redir, int *builtin)
{
	int err;

	*builtin = -1;
	err = 0;
	handle_intern_var(*args);
	ft_expand(*args);
	if ((*args)[0])
	{
		if (redir)
			*args = handle_redir();
		if (!(*args) || !(*args)[0])
			return (-1);
		*builtin = get_builtin((*args)[0]);
		if (!(*builtin))
		{
			if (is_path((*args)[0]))
				err = check_file((*args)[0]);
			else
				err = hash_table(&((*args)[0]), g_shell->env);
		}
		if (err)
			err_handler(err, (*args)[0]);
	}
	return (err);
}
