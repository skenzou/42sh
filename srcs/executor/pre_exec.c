/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:50:03 by midrissi          #+#    #+#             */
/*   Updated: 2019/10/22 05:11:47 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#define NB_BUILTINS 20

static const t_builtin g_builtins[NB_BUILTINS] = {
	{"echo", &echo_builtin},
	{"cd", &cd_builtin},
	{"env", &env_builtin},
	{"setenv", &setenv_builtin},
	{"unsetenv", &unsetenv_builtin},
	{"exit", &exit_builtin},
	{"set", &set_builtin},
	{"export", &export_builtin},
	{"unset", &unset_builtin},
	{"jobs", &jobs_builtin},
	{"fg", &fg_builtin},
	{"bg", &bg_builtin},
	{"type", &type_builtin},
	{"test", &test_builtin},
	{"hash", &hash_builtin},
	{"alias", &alias_builtin},
	{"unalias", &unalias_builtin},
	{"[", &test_builtin},
	{"history", &history_builtin},
	{"fc", &fc_builtin}
};

t_builtin		*get_builtin(char *cmd)
{
	int i;

	i = -1;
	while (++i < NB_BUILTINS)
		if (ft_strequ(cmd, g_builtins[i].cmd))
			return ((t_builtin *)&g_builtins[i]);
	return (NULL);
}

int				ft_pre_execution(char ***args, int redir, t_builtin **builtin)
{
	int err;

	*builtin = NULL;
	err = 0;
	handle_intern_var(*args);
	ft_expand(*args);
	if ((*args)[0])
	{
		if (redir)
			*args = handle_redir();
		if (!(*args) || !(*args)[0])
			return (-1);
		*builtin = (t_builtin *)get_builtin((*args)[0]);
		if (!(*builtin))
		{
			if (is_path((*args)[0]))
				err = check_file((*args)[0]);
			else if ((err = hash_table(&((*args)[0]), g_shell->env)))
				err = hash_table(&((*args)[0]), g_shell->intern);
		}
		if (err)
			err_handler(err, (*args)[0]);
	}
	return (err);
}
