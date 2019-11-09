/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:17:30 by midrissi          #+#    #+#             */
/*   Updated: 2019/10/23 12:56:28 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			add_to_right_tab(char *needle, char ***env, char ***intern)
{
	int		i;
	char	*key;
	int		entry;
	char	*value;

	i = 0;
	while (needle[i] && needle[i] != '=')
		i++;
	if (!(key = ft_strsub(needle, 0, i)))
		shell_exit(MALLOC_ERR);
	if (!(value = ft_strdup(needle + i + 1)))
		shell_exit(MALLOC_ERR);
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

void				compare_paths(char *path)
{
	char *newpath;

	newpath = get_all_key_value("PATH", g_shell->env);
	if ((!path && newpath) || (path && !newpath))
		empty_table();
	else if (path && newpath)
	{
		if (ft_strcmp(path, newpath))
			empty_table();
	}
}

static void			add_to_env_tmp(char *needle)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (needle[i] && needle[i] != '=')
		i++;
	if (!(key = ft_strsub(needle, 0, i)))
		shell_exit(MALLOC_ERR);
	if (!(value = ft_strdup(needle + i + 1)))
		shell_exit(MALLOC_ERR);
	ft_expand_one(&value);
	ft_setenv(key, value, &g_shell->env_tmp);
	ft_strdel(&key);
	ft_strdel(&value);
}

void				handle_intern_var(char **args)
{
	int		i;
	int		j;
	char	*path;

	if (!is_var(args[0]))
		return ;
	i = 0;
	while (args[i] && is_var(args[i]))
		i++;
	j = -1;
	if (args[i])
	{
		if (!(g_shell->env_tmp = ft_splitdup(g_shell->env)))
			shell_exit(MALLOC_ERR);
		while (++j < i)
			add_to_env_tmp(args[j]);
	}
	else
	{
		path = get_all_key_value("PATH", g_shell->env);
		while (++j < i)
			add_to_right_tab(args[j], &g_shell->env, &g_shell->intern);
		compare_paths(path);
	}
	remove_n_first_entries(args, i);
}
