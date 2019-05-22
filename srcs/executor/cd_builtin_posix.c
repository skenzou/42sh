/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin_posix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:46:44 by tlechien          #+#    #+#             */
/*   Updated: 2019/05/22 17:29:23 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"
static void		error_dir(char *path)
{
	ft_putstr("cd: ");
	if (access(path, F_OK) == -1)
		ft_putstr("no such file or directory: ");
	else if (access(path, R_OK) == -1)
		ft_putstr("permission denied: ");
	else
		ft_putstr("not a directory: ");
	ft_putendl(path);
}

int				change_dir(char *path)
{
	char *cwd;
	char buf[4097];

	cwd = getcwd(buf, 4096);
	if (!chdir(path))
	{
		ft_setenv("OLDPWD", cwd); //add_key
		ft_setenv("PWD", path); // add_key
		return (0);
	}
	error_dir(path);
	return (1);
}

static	char	*new_cwd(char **command)
{
	char	*cwd;
	char	*begin;
	char	*end;
	char	buf[4097];
	char	*tmp;

	cwd = getcwd(buf, 4096);
	begin = NULL;
	if ((end = ft_strstr(cwd, command[1])))
	{
		begin = ft_strsub(cwd, 0, end - cwd);
		end = ft_strdup(cwd + (end - cwd + ft_strlen2(command[1])));
		tmp = ft_strjoin(begin, command[2]);
		(begin) ? free(begin): 0;
		begin = ft_strjoin (tmp, end);
		(end)? free(end): 0;
		(tmp)? free(tmp): 0;
		if (!begin)
			error_data(MALLOC);
	}
	return (begin);
}

static	int		cd_many_args(char **cmd)
{
	char	*tmp;

	if (!cmd[3])
	{
		if ((tmp = new_cwd(cmd)))
		{
			change_dir(tmp);
			ft_putendl(tmp);
			//display_path(tmp);
			//ft_putendl("");
			free(tmp);
			return (0);
		}
		ft_putstr("cd: string not in pwd: ");
		ft_putstr(cmd[1]);
		return (0);
	}
	ft_putendl("cd: too many arguments");
	return (1);
}

int				cd_builtin(char **cmd)
{
	char *home_path;
	char *curpath;

	home_path = get_env("HOME");
	if (!cmd[0])
		return (change_dir(home_path));
	//if (command[1])
	//	return (cd_many_args(command));
	else
	{
		if (*cmd[0] == '/')
			curpath = cmd[0];
		else if (!ft_strcmp(cmd[0], ".") || !ft_strcmp(cmd[0], ".."))
			curpath = cmd[0];
		if (!ft_strcmp(cmd[0], "--"))
			return (change_dir(home_path));
		else if (!ft_strcmp(cmd[0], "-"))
		{
			ft_putendl(get_env("OLDPWD"));
			return (change_dir(get_env("OLDPWD")));
		}
		change_dir (cmd[1]);
	}
	return (1);
}
