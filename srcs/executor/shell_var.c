/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:17:30 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/23 18:43:23 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			check_intern_var(char *needle, char ***env, char ***intern)
{
	int		i;
	char	*key;
	int		entry;
	char	*value;

	i = 0;
	while (needle[i] && needle[i] != '=')
		i++;
	if (!(key = ft_strsub(needle, 0, i)))
		ft_exit("Malloc failed in check_intern_var failed");
	if (!(value = ft_strdup(needle + i + 1)))
		ft_exit("Malloc failed in check_intern_var failed");
	entry = get_indexof_key2(key, g_shell->env);
	ft_expand_one(&value);
	if (entry >= 0)
		ft_setenv(key, value, env);
	else
		ft_setenv(key, value, intern);
	ft_strdel(&key);
	ft_strdel(&value);
}

static int			is_var(char *needle)
{
	if (!needle || ft_isdigit(*needle))
		return (0);
	while (*needle && *needle != '=')
	{
		if (!ft_isalnum(*needle) && *needle != '_')
			return (0);
		needle++;
	}
	return (*needle);
}

void		compare_paths(char *path)
{
	char *newpath;

	newpath = get_key_value("PATH", g_shell->env);
	if (!newpath)
		newpath = get_key_value("PATH", g_shell->intern);
	if ((!path && newpath) || (path && !newpath))
		empty_table();
	else if (path && newpath)
	{
		if (ft_strcmp(path, newpath))
			empty_table();
	}
}

static void			reorder_tabs(char *str, char **env, char **intern)
{
	char *path;

	path = get_key_value("PATH", g_shell->env);
	if (!path)
		path = get_key_value("PATH", g_shell->intern);
	if (str)
	{
		g_shell->env_tmp = env;
		g_shell->intern_tmp = intern;
	}
	else
	{
		ft_splitdel(g_shell->env);
		ft_splitdel(g_shell->intern);
		g_shell->env = env;
		g_shell->intern = intern;
		g_shell->env_tmp = g_shell->env;
		g_shell->intern_tmp = g_shell->intern;
		compare_paths(path);
	}
}

void				handle_intern_var(char **args)
{
	int		i;
	char	**env;
	char	**intern;

	i = 0;
	env = ft_splitdup(g_shell->env);
	intern = ft_splitdup(g_shell->intern);
	while (args[i] && is_var(args[i]))
		check_intern_var(args[i++], &env, &intern);
	if (!i)
	{
		ft_splitdel(env);
		ft_splitdel(intern);
		return ;
	}
	remove_n_first_entries(args, i);
	reorder_tabs(args[0], env, intern);
}
