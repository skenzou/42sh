/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:26:58 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/29 18:05:58 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**removekey(char *key, int keylen, char **env)
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
	ft_splitdel(env);
	return (fresh_env);
}

int				unsetenv_builtin(int ac, char **av, char ***env)
{
	char	*key;

	if (ac != 2)
		return (UNSETENV_USG);
	key = ft_strjoin(av[1], "=");
	key == NULL ? exit(1) : 0;
	if ((is_set(key, *env)) >= 0)
		*env = removekey(key, ft_strlen(key), *env);
	ft_strdel(&key);
	return (0);
}
