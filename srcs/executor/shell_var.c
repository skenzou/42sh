/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:17:30 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/29 20:32:40 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	check_intern_var(char *needle, char ***env, char ***intern)
{
	int i;
	char *key;

	i = 0;
	while(needle[i] && needle[i] != '=')
		i++;
	if (!(key = ft_strsub(needle, 0, i)))
		ft_exit("Malloc in check_intern_var failed");
	if (get_indexof_key(key, g_shell->env) >= 0)
		ft_setenv(key, needle + i + 1, env);
	else
		ft_setenv(key, needle + i + 1, intern);
	ft_strdel(&key);
}

int		is_var(char *needle)
{
	if (!ft_isalpha(*(needle++)))
		return (0);
	while (*needle && *needle != '=')
	{
		if (!ft_isalnum(*needle))
			return (0);
		needle++;
	}
	return (*needle);
}

void		handle_intern_var(char **args)
{
	int i;
	char **env;
	char **intern;

	i = 0;
	env = ft_splitdup(g_shell->env);
	intern = ft_splitdup(g_shell->intern);
	while (args[i] && is_var(args[i]))
		check_intern_var(args[i++], &env, &intern);
	if (!i)
	{
		ft_splitdel(env);
		ft_splitdel(intern);
		return ;
	}
	remove_n_first_entries(args, i);
	if (args[0])
	{
		g_shell->env_tmp = env;
		g_shell->intern_tmp = intern;
	}
	else
	{
		ft_splitdel(g_shell->env);
		ft_splitdel(g_shell->intern);
		g_shell->env = env;
		g_shell->intern = intern;
		g_shell->env_tmp = g_shell->env;
		g_shell->intern_tmp = g_shell->intern;
	}
}
