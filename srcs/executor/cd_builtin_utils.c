/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 02:31:10 by midrissi          #+#    #+#             */
/*   Updated: 2019/07/01 05:38:37 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			*get_oldpwd(char **env)
{
	int		i;
	char	*str;

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

int				cd_err(int err_id, char *dest)
{
	if (err_id == NON_EXISTENT)
		ft_putstr_fd("42sh: cd: no such file or directory: ", 2);
	if (err_id == NOT_DIR)
		ft_putstr_fd("42sh: cd: not a directory: ", 2);
	if (err_id == NO_RIGHT)
		ft_putstr_fd("42sh: cd: permission denied: ", 2);
	if (err_id)
		ft_putendl_fd(dest, 2);
	return (err_id > 0);
}

char			*join_path(char *path, char *dir)
{
	char *full_path;

	if (!path || !dir)
		return (NULL);
	if (path[ft_strlen(path) - 1] == '/')
		full_path = ft_strjoin(path, dir);
	else
		full_path = ft_strcjoin(path, dir, '/');
	if (!full_path)
		ft_exit("Malloc failed in test_full_paths");
	return (full_path);
}

char			*test_full_paths(char *entry, char *dir)
{
	char	**paths;
	char	*fpath;
	int		i;

	if (!(paths = ft_strsplit(entry, ':')))
		ft_exit("Malloc failed in test_full_paths");
	i = -1;
	fpath = NULL;
	while (paths[++i])
	{
		fpath = join_path(paths[i], dir);
		if (check_dir(fpath) == 0)
			break ;
		ft_strdel(&fpath);
	}
	ft_splitdel(paths);
	return (fpath);
}

char			*get_path(char *dir)
{
	char *path;
	char *entry;

	if (!dir)
		return (NULL);
	if (*dir == '/' || *dir == '.' || ft_strnequ(dir, "..", 2))
	{
		if (!(path = ft_strdup(dir)))
			ft_exit("Malloc failed in get_path");
		return (path);
	}
	entry = get_key_value("CDPATH", g_shell->env_tmp);
	if (!entry)
		entry = get_key_value("CDPATH", g_shell->intern);
	path = NULL;
	if (entry)
		path = test_full_paths(entry, dir);
	if (path)
		ft_printf("%s\n", path);
	if (!path)
		if (!(path = ft_strdup(dir)))
			ft_exit("Malloc failed in get_path");
	return (path);
}
