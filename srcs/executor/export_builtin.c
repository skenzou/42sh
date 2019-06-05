/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 13:22:00 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/05 09:07:24 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	env_to_env(char *key)
{
	char *entry;

	entry = get_key_value(key, g_shell->env_tmp);
	ft_setenv(key, entry, &g_shell->env);
}

void	intern_to_env(char *key)
{
	char	*entry;
	char	same;

	same = g_shell->intern_tmp == g_shell->intern;
	entry = get_key_value(key, g_shell->intern_tmp);
	ft_setenv(key, entry, &g_shell->env);
	g_shell->intern_tmp =
						removekey(key, ft_strlen(key), g_shell->intern_tmp);
	if (same)
		g_shell->intern = g_shell->intern_tmp;
	else
		env_to_env(key);
}

static int			check_options(int ac, char **av)
{
	int i;

	if (ac > 1)
	{
		av++;
		if (**av == '-' && *((*av) + 1))
		{
			i = 0;
			while ((*av)[++i])
				if ((*av)[i] != 'p')
				{
					ft_putstr_fd("42sh: export: -", 2);
					ft_putchar_fd((*av)[i], 2);
					ft_putendl_fd(": invalid option", 2);
					return (1);
				}
			if (ac == 2)
				print_split(g_shell->env);
		}
	}
	else
		print_split(g_shell->env);
	return (0);
}

static int			exec_export(char *key, char *ptr)
{
	if (is_key_valid(key))
	{
		if (!ptr)
			intern_to_env(key);
		else
			ft_setenv(key, ptr + 1, &g_shell->env);
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

int		export_builtin(int ac, char **av)
{
	int		i;
	char	*ptr;
	char	*key;
	int		ret;

	if (check_options(ac, av))
		return (1);
	i = ft_strnequ(av[1], "-p", 2);;
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
	g_shell->env_tmp = g_shell->env;
	return (ret);
}
