/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 23:58:47 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/26 22:40:27 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		intern_completion(t_ab *autocomp, char *key)
{
	int		i;
	int		len;
	char	**intern;
	int		index;

	intern = g_shell->intern;
	len = ft_strlen(key);
	autocomp->max_offset = 0;
	i = 0;
	while (intern && intern[++i])
	{
		if (intern[i] && !ft_strncmp(key, intern[i], len))
		{
			index = ft_indexof(intern[i], '=');
			autocomp->data[autocomp->len] = ft_strnew(index);
			autocomp->ext[autocomp->len] = 'i';
			ft_strncpy(autocomp->data[autocomp->len], intern[i], index);
			autocomp->max_offset =
							ft_max(autocomp->max_offset, ft_strlen(intern[i]));
			autocomp->len++;
		}
	}
	return (1);
}

int		env_completion(t_ab *autocomp, char *key)
{
	int		i;
	int		len;
	char	**env;
	int		index;

	env = g_shell->env;
	i = -1;
	len = ft_strlen(key);
	autocomp->max_offset = 0;
	autocomp->len = 0;
	while (env && env[++i])
	{
		if (env[i] && !ft_strncmp(key, env[i], len))
		{
			index = ft_indexof(env[i], '=');
			autocomp->data[autocomp->len] = ft_strnew(index);
			autocomp->ext[autocomp->len] = 'e';
			ft_strncpy(autocomp->data[autocomp->len], env[i], index);
			autocomp->max_offset =
					ft_max(autocomp->max_offset, ft_strlen(env[i] + index + 1));
			autocomp->len++;
		}
	}
	intern_completion(autocomp, key);
	return (1);
}

int		command_completion(t_ab *autocomp, char *key)
{
	int		i;
	char	**path_split;
	char	*path;

	path_split = NULL;
	path = NULL;
	if (!(path = ft_strdup(get_key_value("PATH", g_shell->env))))
		return (0);
	if (!(path_split = ft_strsplit(path, ':')))
	{
		ft_strdel(&path);
		return (0);
	}
	if (path)
		ft_strdel(&path);
	i = -1;
	ft_strcpy(autocomp->match, key);
	while (path_split && path_split[++i])
		add_to_completion(autocomp, path_split[i], 'c');
	ft_splitdel(path_split);
	return (1);
}

int		path_completion(t_ab *autocomp, char *key)
{
	char	path[BUFFSIZE];
	int		i;

	ft_bzero(path, BUFFSIZE);
	dprintf(debug(), "path completion, key: |%s|\n", key);
	if (~ft_indexof(key, '/'))
	{
		i = ft_strlen(key) - 1;
		while (key[i] && key[i] != '/')
			i--;
		ft_strcpy(autocomp->match, key + i + 1);
		ft_strncpy(path, key, i == 0 ? 1 : i);
	}
	else
	{
		ft_strcpy(autocomp->match, key);
		ft_strcpy(path, ".");
	}
	return (add_to_completion(autocomp, path, 'r'));
}

int		arg_completion(t_ab *autocomp, t_cap *tc, char *str, int position)
{
	if (is_env_var(autocomp, str))
		return (env_completion(autocomp, str));
	else if (tc->command[position - 1] && tc->command[position - 1] == '/')
	{
		dprintf(debug(), "str: |%s|\n", str);
		return (add_to_completion(autocomp, str, 'r'));
	}
	path_completion(autocomp, str);
	return (autocomp->len > 0);
}
