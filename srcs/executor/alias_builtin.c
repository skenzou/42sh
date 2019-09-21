/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 14:48:57 by tlechien          #+#    #+#             */
/*   Updated: 2019/09/22 00:42:19 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** List of all the reserved keywords that can't be aliased.
*/

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

static int		expand_alias(void)
{
	char	**new_aliases;
	int		i;

	if (!(new_aliases = (char**)ft_memalloc(sizeof(char*) *
		(ft_arraylen(g_aliases) + 2))))
		shell_exit(MALLOC_ERR);
	i = -1;
	while (g_aliases[++i])
		new_aliases[i] = g_aliases[i];
	new_aliases[i + 1] = NULL;
	free(g_aliases);
	g_aliases = new_aliases;
	return (0);
}

/*
** Adds an alias line to the g_aliases array.
*/

static int		add_alias(char *key, char *value)
{
	int		i;
	char	*line;

	i = 0;
	if (!(line = ft_strcjoin(key, value, '=')))
		shell_exit(MALLOC_ERR);
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

/*
** Removes an alias from the g_aliases array.
*/

int				unalias_builtin(int ac, char **cmd)
{
	int	i;
	int	index;

	(void)ac;
	cmd++;
	if (!cmd || !cmd[0])
		return (err_display("unalias: not enough arguments\n", NULL, NULL));
	i = -1;
	while ((index = -1) && cmd[++i])
	{
		index = is_alias(cmd[i]);
		if (index == -1)
			err_display("unalias: no such alias: ", cmd[i], "\n");
		else
		{
			free(g_aliases[index]);
			if (!(g_aliases[index] = ft_strdup("")))
				exit(1);
		}
	}
	return (0);
}

/*
**	Builtin that either displays the aliases or modifies them.
*/

int				alias_builtin(int ac, char **cmd)
{
	int		i;

	(void)ac;
	cmd++;
	if (!cmd || !cmd[0])
		return (display_alias());
	if (!cmd[0] || !cmd[1] || cmd[2])
		return (err_display("usage: alias [key] [value]\n", NULL, NULL));
	if (!is_reserved(cmd[0]))
		return (err_display("alias: ", cmd[0], ": reserved word\n"));
	i = is_alias(cmd[0]);
	if (i == -1)
		add_alias(cmd[0], cmd[1]);
	else
	{
		ft_strdel(&g_aliases[i]);
		if (!(g_aliases[i] = ft_strcjoin(cmd[0], cmd[1], '=')))
			shell_exit(MALLOC_ERR);
	}
	return (0);
}
