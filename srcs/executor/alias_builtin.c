/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 14:48:57 by tlechien          #+#    #+#             */
/*   Updated: 2019/05/20 14:47:35 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

const	char	*g_reserved[] = {
	"!",
	"{",
	"}",
	"case",
	"do",
	"done",
	"elif",
	"else",
	"esac",
	"fi",
	"for",
	"if",
	"in",
	"then",
	"until",
	"while",
	NULL,
};

/*
** Expands g_aliases by one.
*/

int		expand_alias(void)
{
	char	**new_aliases;
	int		i;

	if (!(new_aliases =(char**)ft_memalloc(sizeof(char*) *
		(ft_arraylen(g_aliases) + 1))))
		exit(1); //TODO
	i = -1;
	while (g_aliases[++i])
		new_aliases[i] = g_aliases[i];
	free(g_aliases);
	g_aliases = new_aliases;
	return (0);
}

/*
** Adds an alias line to the g_aliases array.
*/

int		add_alias(char *key, char *value)
{
	int	i;
	char *line;

	i = 0;
	if (!(line = ft_strcjoin(key, value, '=')))
		exit(1); // TODOs
	while (g_aliases[i] && *g_aliases[i])
		i++;
	if (!g_aliases[i])
	{
		expand_alias();
		g_aliases[i] = line;
		return (0);
	}
	free(g_aliases[i]);
	g_aliases[i] = line;
	return (0);
}

int		unalias_builtin(char **cmd)
{
	int	i;
	int	index;

	if (!cmd || !cmd[0])
		return (ft_printf("unalias: not enough arguments"));
	i = -1;
	while ((index = -1) && cmd[++i])
	{
		index = is_alias(cmd[i]);
		if (index == -1)
			ft_printf("unalias: no such hash table element: %s", cmd[i]); // fd 2
		else
		{
			free(g_aliases[index]);
			if (!(g_aliases[index] = ft_strdup("")))
				exit(1); //TODO
		}
	}
	if (is_reserved(cmd[0]))
		return (ft_printf("alias: %s: reserved word", cmd[0]) || 1); // fd 2

	return (0);
}

/*
**	Builtin that either displays the aliases or modifies them.
*/

int		alias_builtin(char **cmd)
{
	int 	i;

	if (!cmd || !cmd[0])
		return (display_alias());
	if (!cmd[1] || !cmd[2] || cmd[3])
		return (ft_printf("usage: alias [key] [value]") || 1); //fd 2
	if (is_reserved(cmd[0]))
		return (ft_printf("alias: %s: reserved word", cmd[0]) || 1); // fd 2
	i = is_alias(cmd[0]);
	if (i == -1)
		add_alias(cmd[0], cmd[1]);
	else
	{
		ft_strdel(&g_aliases[i]);
		if (!(g_aliases[i] = ft_strcjoin(cmd[0], cmd[1], '=')))
			exit(1); //TODO
	}
	return (0);
}
