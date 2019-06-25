/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 06:02:13 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/26 00:45:27 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_separator(char *s, int position)
{
	return ((s[position] && s[position] == ';') ||
			(s[position] && s[position] == '|') ||
			(s[position] && s[position] == '&'));
}

int		is_space_before(t_cap *tcap, int position)
{
	int i;

	i = -1;
	while (++i <= position && i < tcap->char_len)
		if (tcap->command[i] != ' ')
			return (0);
	return (1);
}

char	*env_path(char **env)
{
	int i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PATH=", 5))
			return ((char*)env[i] + 5);
	return (NULL);
}

int		is_first_argi(t_cap *tc, int position)
{
	int i;

	if (!get_argi(tc, position))
		return (1);
	i = position - 1;
	while (i)
	{
		if (tc->command[i] == ' '
				&& (tc->command[i - 1] && !is_separator(tc->command, i - 1)))
			return (0);
		else if (is_separator(tc->command, i))
			return (1);
		i--;
	}
	return (0);
}

int		is_env_var(t_ab *autocomp, char *path)
{
	int		i;
	char	copy[MAX_PATH];

	ft_strcpy(copy, path);
	i = 0;
	if (path[0] == '$' && (path[1] && path[1] == '{'))
	{
		i = 2;
		autocomp->after[0] = '}';
		autocomp->after[1] = '\0';
	}
	else if (path[0] == '$')
	{
		i = 1;
		autocomp->after[0] = path[0] == '$';
		autocomp->after[1] = '\0';
	}
	ft_bzero(path, MAX_PATH);
	ft_strcpy(path, copy + i);
	return (i > 0);
}
