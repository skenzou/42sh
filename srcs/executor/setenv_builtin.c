/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 18:46:30 by midrissi          #+#    #+#             */
/*   Updated: 2019/10/22 02:14:41 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int						get_indexof_key(char *key, char **env)
{
	int i;
	int len;

	i = -1;
	len = ft_strlen2(key);
	while (env && env[++i])
	{
		if (!ft_strncmp(key, env[i], len))
			return (i);
	}
	return (-1);
}

static char				**addkey(char *key, char *value, char **env)
{
	int		i;
	char	**fresh_env;
	int		count;

	count = ft_split_count((const char**)env);
	fresh_env = (char **)ft_memalloc(sizeof(char *) * (count + 2));
	fresh_env == NULL ? shell_exit(MALLOC_ERR) : 0;
	i = -1;
	while (++i < count)
		if (!(fresh_env[i] = ft_strdup(env[i])))
			shell_exit(MALLOC_ERR);
	fresh_env[i] = !value ? key : ft_strjoin(key, value);
	fresh_env[i] == NULL ? shell_exit(MALLOC_ERR) : 0;
	fresh_env[i + 1] = NULL;
	ft_splitdel(env);
	return (fresh_env);
}

void					ft_setenv(char *key, char *value, char ***env)
{
	int		i;
	char	*temp;

	key = ft_strjoin(key, "=");
	key == NULL ? shell_exit(MALLOC_ERR) : 0;
	i = get_indexof_key(key, *env);
	if (i >= 0)
	{
		temp = (*env)[i];
		(*env)[i] = !value ? key : ft_strjoin(key, value);
		(*env)[i] == NULL ? shell_exit(MALLOC_ERR) : 0;
		ft_strdel(&temp);
	}
	else
		*env = !value ? addkey(key, NULL, *env) : addkey(key, value, *env);
	value ? ft_strdel(&key) : 0;
}

static int				setenv_err(int err_id)
{
	if (err_id == SETENV_USG)
		ft_putendl_fd("usage: setenv [<Key> <Value> | <Key>]", 2);
	if (err_id == SETENV_INVALID_KEY)
		ft_putendl_fd(
			"setenv: Variable name must contain alphanumeric characters.", 2);
	return (1);
}

int						setenv_builtin(int ac, char **av)
{
	int same;

	same = g_shell->env == g_shell->env_tmp;
	if (ac > 3)
		return (setenv_err(SETENV_USG));
	if (ac > 1 && !is_key_valid(av[1]))
		return (setenv_err(SETENV_INVALID_KEY));
	if (ac == 1)
		print_split(g_shell->env);
	if (ac == 2)
		ft_setenv(av[1], NULL, &g_shell->env);
	if (ac == 3)
		ft_setenv(av[1], av[2], &g_shell->env);
	if (same)
		g_shell->env_tmp = g_shell->env;
	return (0);
}
