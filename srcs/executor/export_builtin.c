/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 13:22:00 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/02 03:34:44 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	env_to_env(char *key)
{
	char *entry;

	entry = get_key_value(key, g_shell->env_tmp);
	if (entry)
	{
		if (entry[ft_strlen(key) + 1])
			ft_setenv(key, entry + ft_strlen(key) + 1, &g_shell->env);
		else
			ft_setenv(key, NULL, &g_shell->env);
	}
}

void	intern_to_env(char *key)
{
	char	*entry;
	char	same;

	same = g_shell->intern_tmp == g_shell->intern;
	entry = get_key_value(key, g_shell->intern_tmp);
	if (entry)
	{
		if (entry[ft_strlen(key) + 1])
			ft_setenv(key, entry + ft_strlen(key) + 1, &g_shell->env);
		else
			ft_setenv(key, NULL, &g_shell->env);
		g_shell->intern_tmp = removekey(key, ft_strlen(key), g_shell->intern_tmp);
		if (same)
			g_shell->intern = g_shell->intern_tmp;
	}
	else
		env_to_env(key);
}

int		export_builtin(int ac, char **av)
{
	int		i;
	char	*ptr;
	char	*key;


	if (ac == 1 || (ac == 2 && ft_strequ(av[1], "-p")))
	{
		print_split(g_shell->env);
		return (0);
	}
	i = 0;
	key = NULL;
	while (++i < ac)
	{
		ptr = ft_strchr(av[i], '=');
		if (ptr)
			key = ft_strsub(av[i], 0, ptr - av[i]);
		else
			key = ft_strdup(av[i]);
		!key ? ft_exit("Malloc failed in export_builtin") : 0;
		if (!ptr)
			intern_to_env(key);
		else
			ft_setenv(key, ptr + 1, &g_shell->env);
		ft_strdel(&key);
	}
	g_shell->env_tmp = g_shell->env;
	return (0);
}
