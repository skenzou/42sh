/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 15:02:25 by tlechien          #+#    #+#             */
/*   Updated: 2019/06/04 19:12:09 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Calculates the size of an array of strings.
*/

int		ft_arraylen(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}

/*
**	Display the aliases.
*/

int		display_alias(void)
{
	int i;

	i = -1;
	while (g_aliases[++i])
		(*g_aliases[i]) ? ft_putendl(g_aliases[i]) : 0;
	return (0);
}

/*
** Checks if the key is in the reserved list.
*/

int	is_reserved(char *key)
{
	int i;

	i = -1;
	while (g_reserved[++i])
	{
		if (!ft_strcmp(key, g_reserved[i]))
			return (0);
	}
	return (1);
}

/*
** Checks if the key is an alias.
*/

int	is_alias(char *key)
{
	int 	i;
	int 	len;

	len = (key) ? ft_strlen(key) : 0;
	if (!is_reserved(key))
		return (-1);
	i = -1;
	while (g_aliases[++i])
	{
		if (*g_aliases[i] && !ft_strncmp(key, g_aliases[i], len) &&
			g_aliases[i][len]== '=')
			return (i);
	}
	return (-1);
}

/*
** Look for an alias in g_aliases and returns its value.
*/

char *get_alias(char *key)
{
	int		i;
	int		len;
	char	*value;

	len = (key) ? ft_strlen(key) : 0;
	if (!is_reserved(key))
		return (NULL);
	if ((i = is_alias(key)) >= 0)
	{
		value = g_aliases[i]+ len + 1;
		len = 0;
		while (value[len] != '\0' && value[len] != '\n')
			len++;
		value = ft_strsub(value, 0, len);
		return (value);
	}
	return (NULL);
}
