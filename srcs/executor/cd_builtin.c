/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 11:44:34 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/04 05:31:49 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			*get_homepath(char **env)
{
	int i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "HOME=", 5))
			return (env[i] + 5);
	}
	return (NULL);
}

static char		*get_oldpwd(char **env)
{
	int i;
	char *str;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
		{
			if (!(str = ft_strdup(env[i] + 7)))
				ft_exit("Malloc failed in get_oldpwd");
			return (str);
		}
	}
	return (NULL);
}

static int		change_dir(char *path)
{
	int				err;
	char			cwd[MAX_PATH_LEN];

	err = check_dir(path);
	if (!err)
	{
		ft_setenv("OLDPWD", getcwd(cwd, sizeof(cwd)), &g_shell->env);
		chdir(path);
		ft_setenv("PWD", getcwd(cwd, sizeof(cwd)), &g_shell->env);
	}
	return (err);
}

int				cd_err(int err_id, char *dest)
{
	if (err_id == NON_EXISTENT)
		ft_putstr_fd("cd: no such file or directory: ", 2);
	if (err_id == NOT_DIR)
		ft_putstr_fd("cd: not a directory: ", 2);
	if (err_id == NO_RIGHT)
		ft_putstr_fd("cd: permission denied: ", 2);
	if (err_id)
		ft_putendl_fd(dest, 2);
	return (err_id > 0);
}

int				cd_builtin(int argc, char **argv)
{
	char	*path;
	int		err;
	int		same;

	same = g_shell->env == g_shell->env_tmp;
	path = NULL;
	err = 0;
	if (argc == 1 && (path = get_key_value("HOME", g_shell->env_tmp)))
		err = change_dir(path);
	else if (argc > 1)
	{
		if (ft_strlen(argv[1]) == 1 && argv[1][0] == '-')
		{
			path = get_oldpwd(g_shell->env);
			if (!path)
			{
				ft_putendl_fd("42sh: cd: OLDPWD not set", 2);
				return (1);
			}
			ft_printf("%s\n", path);
			err = change_dir(path);
			ft_strdel(&path);
		}
		else
			err = change_dir(argv[1]);
	}
	if (same)
		g_shell->env_tmp = g_shell->env;
	return (cd_err(err, argv[1]));
}
