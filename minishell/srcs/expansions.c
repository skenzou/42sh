/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 21:14:54 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/24 13:21:31 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*tilde_expansion(char *needle, char **env)
{
	char	*path;
	char	*home;
	int		len;

	home = get_homepath(env);
	len = ft_strlen(needle);
	path = NULL;
	if (len == 1)
	{
		if (!(path = ft_strdup(home)))
			exit(1);
	}
	else if (*(needle + 1) == '/')
	{
		if (!(path = ft_strjoin(home, needle + 1)))
			exit(1);
	}
	if (path)
	{
		ft_strdel(&needle);
		needle = path;
	}
	return (needle);
}

static char		*dollar_expansion(char *needle, char **env)
{
	int		len;
	int		i;
	char	*save;

	save = needle;
	needle = ft_strcjoin(needle + 1, "", '=');
	!needle ? exit(1) : 0;
	len = ft_strlen(needle);
	i = -1;
	while (env[++i])
		if (!ft_strncmp(needle, env[i], len))
		{
			ft_strdel(&save);
			ft_strdel(&needle);
			needle = ft_strdup(env[i] + len);
			!needle ? exit(1) : 0;
			return (needle);
		}
	ft_strdel(&needle);
	return (save);
}

void			manage_expansions(char **input, char **env)
{
	char	*home;
	int		len;

	home = get_homepath(env);
	len = ft_strlen(*input);
	if (**input == '~' && home)
		*input = tilde_expansion(*input, env);
	else if (len > 1 && **input == '$')
		*input = dollar_expansion(*input, env);
}
