/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_words.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 23:58:47 by aben-azz          #+#    #+#             */
/*   Updated: 2019/11/03 05:24:47 by aben-azz         ###   ########.fr       */
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
	i = -1;
	ft_strcpy(autocomp->match, key);
	while (intern && intern[++i])
	{
		if (intern[i] && !ft_strncmp(key, intern[i], len))
		{
			index = ft_indexof(intern[i], '=');
			autocomp->data[autocomp->len] = ft_strnew(index);
			autocomp->ext[autocomp->len] = 'i';
			ft_strncpy(autocomp->data[autocomp->len], intern[i], index);
			autocomp->max_offset =
		ft_max(autocomp->max_offset, ft_strlen(autocomp->data[autocomp->len]));
			autocomp->len++;
		}
	}
	return (1);
}

int		env_completion(t_ab *comp, char *k)
{
	int		i;
	int		len;
	char	**nv;
	int		o;

	nv = g_shell->env_tmp;
	i = -1;
	len = ft_strlen(k);
	comp->max_offset = 0;
	comp->len = 0;
	ft_strcpy(comp->match, k);
	while (nv && nv[++i])
	{
		if (nv[i] && !ft_strncmp(k, nv[i], len) && (o = ft_indexof(nv[i], '=')))
		{
			comp->data[comp->len] = ft_strnew(o);
			comp->ext[comp->len] = 'e';
			ft_strncpy(comp->data[comp->len], nv[i], o);
			comp->max_offset = ft_max(comp->max_offset,
											ft_strlen(comp->data[comp->len]));
			comp->len++;
		}
	}
	intern_completion(comp, k);
	return (1);
}

int		command_completion(t_ab *autocomp, char *key)
{
	int		i;
	char	**path_split;
	char	*path;

	path_split = NULL;
	path = NULL;
	if (!(path = ft_strdup(get_all_key_value("PATH", g_shell->env))))
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
	int index;

	if ((index = is_env_var(autocomp, str)))
		return (env_completion(autocomp, str));
	else if (tc->command[position - 1] && tc->command[position - 1] == '/')
	{
		return (add_to_completion(autocomp, str, 'r'));
	}
	path_completion(autocomp, str);
	return (autocomp->len > 0);
}
