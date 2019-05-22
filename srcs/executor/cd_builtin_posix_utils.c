/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin_posix_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:50:25 by tlechien          #+#    #+#             */
/*   Updated: 2019/05/22 16:53:38 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		begin_with(char *env_key, char *str)
{
	int	i;

	i = 0;
	if (!env_key || !str)
		return (1);
	while (env_key[i] && str[i] && str[i] != '=')
	{
		if (env_key[i] != str[i])
			return (1);
		i++;
	}
	return ((!str[i] && env_key[i] == '=') ? 0 : 1);
}

int		search_env(char *var)
{
	int	i;

	i = -1;
	while (g_env[++i])
	{
		if (!begin_with(g_env[i], var))
			return (i);
	}
	return (-1);
}

char	*get_env(char *var)
{
	int i;
	int j;

	i = search_env(var);
	j = 0;
	if (i == -1)
		return (NULL);
	while (g_env[i][j] != '=' && g_env[i][j])
		j++;
	return ((g_env[i][j]) ? &g_env[i][j + 1] : NULL);
}
