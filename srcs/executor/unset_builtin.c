/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:41:44 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/07 06:27:32 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		unset_key(char *str)
{
	char	*key;
	int		key_index;

	if (!(key = ft_strjoin(str, "=")))
		ft_exit("Malloc failed in unset_builtin");
	key_index = get_indexof_key(key, g_shell->env_tmp);
	if (key_index >= 0)
		g_shell->env_tmp = removekey(key, ft_strlen(key), g_shell->env_tmp);
	key_index = get_indexof_key(key, g_shell->intern_tmp);
	if (key_index >= 0)
		g_shell->intern_tmp =
							removekey(key, ft_strlen(key), g_shell->intern_tmp);
	ft_strdel(&key);
}

int				unset_builtin(int ac, char **av)
{
	int		i;
	char	same_env;
	char	same_intern;

	i = -1;
	same_env = g_shell->env == g_shell->env_tmp;
	same_intern = g_shell->intern == g_shell->intern_tmp;
	while (++i < ac)
		unset_key(av[i]);
	if (same_env)
		g_shell->env = g_shell->env_tmp;
	if (same_intern)
		g_shell->intern = g_shell->intern_tmp;
	if (ac < 2)
		ft_putendl_fd("unset: not enough arguments", 2);
	return (ac < 2);
}
