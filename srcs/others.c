/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:35:56 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/09 06:41:15 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char	**dup_env(char **env)
{
	char	**p;
	int		i;

	i = ft_split_count(env);
	if (!(p = (char **)ft_memalloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = -1;
	while (env[++i])
		if (!(p[i] = ft_strdup(env[i])))
			return (NULL);
	p[i] = NULL;
	return (p);
}


int		ft_put_termcaps(int c)
{
	write(1, &c, 1);
	return (1);
}

void	display_prompt_prefix(void)
{
	char *string;
	char *name;

	name = getenv("USER");
	name || (name = "21sh");
	string = NULL;
	string = getcwd(string, 20);
	g_shell->tcap->prompt_len =
		ft_strlen((string + ft_lastindexof(string, '/') + 1)) +
			ft_strlen(name) + 4;
	g_shell->tcap->cursx = g_shell->tcap->prompt_len;
	ft_printf(PREFIX);
	ft_printf(SUFFIX, (string + ft_lastindexof(string, '/') + 1), name);
}

char	*correct(char *string, char **possible, int *difference)
{
	size_t	distance;
	int		i;
	int		smallest;
	size_t	dist;

	i = -1;
	distance = SIZE_MAX;
	while (possible[++i])
	{
		if (distance > (dist = ft_levenshtein(string, possible[i])))
		{
			distance = dist;
			smallest = i;
		}
	}
	*difference = (int)distance;
	return (possible[smallest]);
}
