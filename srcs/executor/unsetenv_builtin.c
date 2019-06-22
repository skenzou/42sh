/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:26:58 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/22 19:43:21 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			**removekey(char *key, int keylen, const char **env)
{
	char	**fresh_env;
	int		count;
	int		i;
	int		j;

	count = ft_split_count(env);
	fresh_env = (char **)ft_memalloc(sizeof(char *) * (count + 1));
	fresh_env == NULL ? exit(1) : 0;
	j = 0;
	i = -1;
	while (++i < count)
		if (ft_strncmp(env[i], key, keylen))
		{
			fresh_env[j] = ft_strdup(env[i]);
			fresh_env[j++] == NULL ? exit(1) : 0;
		}
	fresh_env[j] = NULL;
	ft_splitdel((char**)env);
	return (fresh_env);
}

int				unsetenv_builtin(int ac, char **av)
{
	char	*key;
	int		same;

	same = g_shell->env == g_shell->env_tmp;
	if (ac != 2)
	{
		ft_putendl_fd("usage: unsetenv <Key>", 2);
		return (1);
	}
	key = ft_strjoin(av[1], "=");
	key == NULL ? exit(1) : 0;
	if ((get_indexof_key(key, g_shell->env)) >= 0)
		g_shell->env = removekey(key, ft_strlen(key),
													(const char**)g_shell->env);
	ft_strdel(&key);
	if (same)
		g_shell->env_tmp = g_shell->env;
	return (0);
}
