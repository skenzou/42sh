/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 11:44:34 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/06 06:20:01 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

static void		clean_dot_dot(char *path, int *j, char *new_path, int *i)
{
	if (*j > 0 && path[*j - 1] == '/' && (path[*j + 2] == '\0' ||
														path[*j + 2] == '/'))
	{
		(*j) += 2;
		(*i)--;
		if (*j == 3)
			return ;
		new_path[(*i)--] = '\0';
		while (*i >= 0 && new_path[*i] != '/')
			new_path[(*i)--] = '\0';
		if (*i < 0)
			*i = 0;
	}
	else
	{
		new_path[(*i)++] = path[(*j)++];
		new_path[(*i)++] = path[(*j)++];
	}
}

static void		clean_dot(char *path, int *j, char *new_path, int *i)
{
	if (*j > 0 && path[*j - 1] == '/' &&
								(path[*j + 1] == '\0' || path[*j + 1] == '/'))
	{
		if (path[*j + 1] == '\0')
			(*j)++;
		else if (path[*j + 1] == '/')
			(*j) += 2;
	}
	else
		new_path[(*i)++] = path[(*j)++];
}

char		*clean_path(char *path, char *new_path)
{
	int			i;
	int			j;

	ft_bzero((void *)new_path, MAX_PATH_LEN);
	j = 0;
	i = 0;
	while (path[j])
	{
		if (path[j] == '/')
		{
			while (path[j] == '/')
				j++;
			new_path[i++] = '/';
		}
		else if (ft_strnequ(path + j, "..", 2))
			clean_dot_dot(path, &j, new_path, &i);
		else if (path[j] == '.')
			clean_dot(path, &j, new_path, &i);
		else
			new_path[i++] = path[j++];
	}
	if (i > 0  && new_path[i] == '/')
		new_path[i] = '\0';
	return (new_path);
}

static char				*reorder_pwd(char *path, char *buff)
{
	char	*oldpwd;
	char	full_path[MAX_PATH_LEN];

	if (path && path[0] == '/')
		return (clean_path(path, buff));
	oldpwd = get_key_value("OLDPWD", g_shell->env);
	ft_bzero((void *)full_path, MAX_PATH_LEN);
	ft_strcpy(full_path, oldpwd);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, path);
	return (clean_path(full_path, buff));
}

static int				cd_err(int err_id, char *dest)
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

static int		change_dir(char *path, char flag)
{
	char			cwd[MAX_PATH_LEN];

	if (cd_err(check_dir(path), path))
		return (1);
	ft_setenv("OLDPWD", getcwd(cwd, sizeof(cwd)), &g_shell->env);
	if (chdir(path) == -1)
	{
		ft_putendl_fd("42sh: cd: chdir error", 2);
		return (1);
	}
	if (flag == 'P')
		ft_setenv("PWD", getcwd(cwd, sizeof(cwd)), &g_shell->env);
	else
		ft_setenv("PWD", reorder_pwd(path, cwd), &g_shell->env);
	return (0);
}

static int			check_options(int ac, char **av, char *flag)
{
	int i;

	*flag = 0;
	if (ac > 1)
	{
		av++;
		if (ft_strequ(*av, "--"))
		{
			*flag = '-';
			return (0);
		}
		if (**av == '-' && *((*av) + 1))
		{
			i = 0;
			while ((*av)[++i])
				if ((*av)[i] != 'L' && (*av)[i] != 'P')
				{
					ft_putstr_fd("42sh: cd: -", 2);
					ft_putchar_fd((*av)[i], 2);
					ft_putendl_fd(": invalid option", 2);
					return (1);
				}
				*flag = (*av)[i - 1];
		}
	}
	return (0);
}

static	int		cd_home(char flag)
{
	char *value;

	value = get_key_value("HOME", g_shell->env);
	if (value)
		return (change_dir(value, flag));
	else
	{
		ft_putendl_fd("42sh: cd: HOME not set", 2);
		return (1);
	}
}

static int		cd_oldpwd(char flag)
{
	char *path;
	int ret;

	ret = 0;
	path = get_oldpwd(g_shell->env);
	if (!path)
	{
		ft_putendl_fd("42sh: cd: OLDPWD not set", 2);
		return (1);
	}
	ft_printf("%s\n", path);
	ret = change_dir(path, flag);
	ft_strdel(&path);
	return (ret);
}

static int		regular_cd(char *dir, char flag)
{
	int ret;
	char *path;

	path = get_path(dir);
	ret = change_dir(path, flag);
	ft_strdel(&path);
	return (ret);
}

int				cd_builtin(int ac, char **av)
{
	int		same;
	char	flag;
	int		ret;

	same = g_shell->env == g_shell->env_tmp;
	if (check_options(ac, av, &flag))
		return (1);
	if (flag)
		av++ && ac--;
	if (ac == 1)
		ret = cd_home(flag);
	else if (ac > 1 && ft_strequ(av[1], "-"))
		ret = cd_oldpwd(flag);
	else
		ret = regular_cd(av[1], flag);
	if (same)
		g_shell->env_tmp = g_shell->env;
	return (ret);
}
