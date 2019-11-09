/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:41:44 by midrissi          #+#    #+#             */
/*   Updated: 2019/10/23 13:03:11 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		unset_key(char *str)
{
	char	*key;
	int		key_index;

	if (!(key = ft_strjoin(str, "=")))
		shell_exit(MALLOC_ERR);
	key_index = get_indexof_key(key, g_shell->env_tmp);
	if (key_index >= 0)
		g_shell->env_tmp = removekey(key, ft_strlen(key),
											(const char **)g_shell->env_tmp);
	else if ((get_indexof_key(key, g_shell->intern)) >= 0)
		g_shell->intern = removekey(key, ft_strlen(key),
										(const char **)g_shell->intern);
	ft_strdel(&key);
}

int				unset_builtin(int ac, char **av)
{
	int		i;
	char	same_env;

	i = -1;
	same_env = g_shell->env == g_shell->env_tmp;
	while (++i < ac)
		unset_key(av[i]);
	if (same_env)
		g_shell->env = g_shell->env_tmp;
	if (ac < 2)
		ft_putendl_fd("unset: not enough arguments", 2);
	return (ac < 2);
}
