/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin_chdir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 05:34:19 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/07 05:47:29 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			clean_dot_dot(char *path, int *j, char *new_path, int *i)
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

static void			clean_dot(char *path, int *j, char *new_path, int *i)
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

char				*clean_path(char *path, char *new_path)
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
	if (i > 0 && new_path[i] == '/')
		new_path[i] = '\0';
	return (new_path);
}

static char			*reorder_pwd(char *path, char *buff)
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

int					change_dir(char *path, char flag)
{
	char			cwd[MAX_PATH_LEN];
	char			*pwd;

	if (cd_err(check_dir(path), path))
		return (1);
	pwd = get_key_value("PWD", g_shell->env_tmp);
	if (pwd)
		ft_setenv("OLDPWD", pwd, &g_shell->env);
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
