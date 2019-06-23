/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 13:22:00 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/23 17:45:44 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			env_to_env(char *key)
{
	char *value;

	value = get_key_value(key, g_shell->env_tmp);
	if (value)
	{
		if (!(value = ft_strdup(value)))
			ft_exit("Malloc failed in intern_to_env");
		update_env(key, value);
		ft_strdel(&value);
	}
	else
	{
		if (get_indexof_key2(key, g_shell->env) < 0)
			ft_setenv(key, NULL, &g_shell->env);
	}
}

static void			intern_to_env(char *key)
{
	char	*value;
	char	same_intern;

	same_intern = g_shell->intern_tmp == g_shell->intern;
	value = get_key_value(key, g_shell->intern_tmp);
	if (value)
	{
		if (!(value = ft_strdup(value)))
			ft_exit("Malloc failed in intern_to_env");
		update_env(key, value);
		g_shell->intern_tmp =
						removekey2(key, 0, (const char**)g_shell->intern_tmp);
		if (same_intern)
			g_shell->intern = g_shell->intern_tmp;
		else
			g_shell->intern = removekey2(key, 0, (const char**)g_shell->intern);
	}
	else
		env_to_env(key);
	ft_strdel(&value);
}

static void			simple_export(char *key, char *value, char *ptr)
{
	char	same_intern;
	int		entry;

	same_intern = g_shell->intern_tmp == g_shell->intern;
	if (!(value = ft_strdup(ptr + 1)))
		ft_exit("Malloc failed in exec_export");
	update_env(key, value);
	ft_strdel(&value);
	entry = get_indexof_key2(key, g_shell->intern_tmp);
	if (entry >= 0)
	{
		g_shell->intern_tmp =
						removekey2(key, 0, (const char**)g_shell->intern_tmp);
		if (same_intern)
			g_shell->intern = g_shell->intern_tmp;
		else
			g_shell->intern = removekey2(key, 0, (const char**)g_shell->intern);
	}
}

static int			exec_export(char *key, char *ptr)
{
	char	*value;

	value = NULL;
	if (is_key_valid(key))
	{
		if (!ptr)
			intern_to_env(key);
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
