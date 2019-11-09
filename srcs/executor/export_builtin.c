/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 13:22:00 by midrissi          #+#    #+#             */
/*   Updated: 2019/11/09 16:12:08 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**faire des test pour update_env();
*/

static void			intern_to_env(char *key)
{
	char	*value;

	value = get_all_key_value(key, g_shell->intern);
	update_env(key, value);
	g_shell->intern = removekey2(key, 0, (const char**)g_shell->intern);
}

static void			env_to_env(char *key)
{
	char	*value;

	value = get_all_key_value(key, g_shell->env_tmp);
	if (value)
	{
		if (!(value = ft_strdup(value)))
			shell_exit(MALLOC_ERR);
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
		shell_exit(MALLOC_ERR);
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
		!key ? shell_exit(MALLOC_ERR): 0;
		ret += exec_export(key, ptr);
		ft_strdel(&key);
	}
	return (ret);
}
