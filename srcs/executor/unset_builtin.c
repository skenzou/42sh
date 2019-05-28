/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:41:44 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/28 17:09:11 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		unset_builtin(int ac, char **av)
{
	int i;
	int key_index;
	char same_env;
	char same_intern;

	i = -1;
	same_env = g_shell->env == g_shell->env_tmp;
	same_intern = g_shell->intern == g_shell->intern_tmp;
	while (++i < ac)
	{
		key_index = get_indexof_key(av[i], g_shell->env_tmp);
		if (key_index >= 0)
			g_shell->env_tmp = removekey(av[i], ft_strlen(av[i]), g_shell->env_tmp);
		key_index = get_indexof_key(av[i], g_shell->intern_tmp);
		if (key_index >= 0)
			g_shell->intern_tmp = removekey(av[i], ft_strlen(av[i]), g_shell->intern_tmp);
	}
	if (same_env)
		g_shell->env = g_shell->env_tmp;
	if (same_intern)
		g_shell->intern = g_shell->intern_tmp;
	return (0);
}
