/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 13:22:00 by midrissi          #+#    #+#             */
/*   Updated: 2019/07/01 05:39:42 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			intern_to_env(char *key)
{
	char	*value;

	value = get_key_value(key, g_shell->intern);
	update_env(key, value); // faire encore plus de test pour ce cas ci
	g_shell->intern = removekey2(key, 0, (const char**)g_shell->intern);
}

static void			env_to_env(char *key)
{
	char	*value;

	value = get_key_value(key, g_shell->env_tmp);
	if (value)
	{
		if (!(value = ft_strdup(value)))
			ft_exit("Malloc failed in intern_to_env");
		if ((get_indexof_key2(key, g_shell->intern)) >= 0)
			g_shell->intern = removekey2(key, 0, (const char**)g_shell->intern);
		update_env(key, value);
		ft_strdel(&value);
	}
	else if ((get_indexof_key2(key, g_shell->intern)) >= 0)
		intern_to_env(key);
	else
	{
		if (get_indexof_key2(key, g_shell->env) < 0)
			ft_setenv(key, NULL, &g_shell->env);
	}
}

static void			simple_export(char *key, char *value, char *ptr)
{
	if (!(value = ft_strdup(ptr + 1)))
		ft_exit("Malloc failed in exec_export");
	update_env(key, value);
	ft_strdel(&value);
	if ((get_indexof_key2(key, g_shell->intern)) >= 0)
		g_shell->intern = removekey2(key, 0, (const char**)g_shell->intern);
}

static int			exec_export(char *key, char *ptr)
{
	char	*value;

	value = NULL;
	if (is_key_valid(key))
	{
		if (!ptr)
			env_to_env(key);
		else
			simple_export(key, value, ptr);
		return (0);
	}
	else
	{
		ft_putstr_fd("42sh: export: `", 2);
		ft_putstr_fd(key, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
}

int					export_builtin(int ac, char **av)
{
	int		i;
	char	*ptr;
	char	*key;
	int		ret;

	if (export_options(ac, av))
		return (1);
	i = ft_strnequ(av[1], "-p", 2);
	ret = 0;
	while (++i < ac)
	{
		ptr = ft_strchr(av[i], '=');
		if (ptr)
			key = ft_strsub(av[i], 0, ptr - av[i]);
		else
			key = ft_strdup(av[i]);
		!key ? ft_exit("Malloc failed in export_builtin") : 0;
		ret += exec_export(key, ptr);
		ft_strdel(&key);
	}
	return (ret);
}
