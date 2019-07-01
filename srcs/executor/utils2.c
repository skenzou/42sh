/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 06:15:18 by midrissi          #+#    #+#             */
/*   Updated: 2019/07/01 05:41:16 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int						is_special_char(char c)
{
	return (c == '$' || c == '\\' || c == '"' || c == '`' || c == '\n');
}

int						is_key_valid(char *key)
{
	if (!key || ft_isdigit(*key))
		return (0);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

void					close_fd(void)
{
	int		i;
	t_list	*redir;

	redir = g_shell->temp_redir;
	while (redir && ((t_redir *)redir->content)->end_of_leaf == 0)
	{
		if (((t_redir *)redir->content)->op_type != DBL_LESS)
			close(((t_redir *)redir->content)->fd);
		redir = redir->next;
	}
	g_shell->temp_redir = NULL;
	i = -1;
	while (++i < 10)
		dup2(g_shell->fd_table[i], i);
}

int						get_indexof_key2(char *key, char **env)
{
	int i;
	int len;

	i = -1;
	if (!(key = ft_strjoin(key, "=")))
		ft_exit("Malloc failed in get_indexof_key2");
	len = ft_strlen(key);
	while (env && env[++i])
	{
		if (!ft_strncmp(key, env[i], len))
		{
			free(key);
			return (i);
		}
	}
	free(key);
	return (-1);
}

void					update_env(char *key, char *value)
{
	char same_env;

	same_env = g_shell->env_tmp == g_shell->env;
	ft_expand_one(&value);
	ft_setenv(key, value, &g_shell->env);
	if (same_env)
		g_shell->env_tmp = g_shell->env;
	else
		g_shell->env_tmp = removekey2(key, 0, (const char**)g_shell->env_tmp);
}
