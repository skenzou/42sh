/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:35:56 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/22 20:30:59 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_put_termcaps(int c)
{
	write(1, &c, 1);
	return (1);
}

char	*get_git_status(void)
{
	char		*str;
	int			i;
	int			fd;
	char		*status;

	i = 0;
	if ((fd = open(".git/HEAD", O_RDONLY)) > 0)
	{
		while (get_next_line(fd, &str, '\n') > 0)
		{
			if ((status = str + ft_lastindexof(str, '/') + 1))
				return (status);
			else
				return (NULL);
			i++;
		}
	}
	close(fd);
	return (NULL);
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
