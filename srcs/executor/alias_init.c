/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 16:01:10 by tlechien          #+#    #+#             */
/*   Updated: 2019/05/20 14:41:38 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Initializes the global g_aliases from void or file.
*/

int	init_alias(int file)
{
	int		fd;
	int		i;
	char	*line;
	int		ret;

	fd = (file) ? open(ALIAS_FILE, O_RDONLY | O_CREAT | O_TRUNC, S_IRUSR |
		S_IWUSR) : 0;
	i = 1;
	ret = 0;
	//if (fd == -1)
	//	error(1); TODO
	if (fd)
	{
		while ((ret = get_next_line(fd, &line, '\n')) == 1)
		{
			free(line);
			i++;
		}
	}
	if (ret == -1 || (file && close(fd) == -1) || (file && (fd = open(
		ALIAS_FILE, O_RDONLY | O_TRUNC, S_IRUSR | S_IWUSR)) == -1))
		return (1);
	g_aliases =(char **)ft_memalloc(sizeof(char *) * i);
	i = -1;
	while (file && (ret = get_next_line(fd, &line, '\n')) == 1)
		g_aliases[++i] = line;
	return (((file && close(fd) == -1) || ret == -1)? 1 : 0);
}

/*
**	Frees the global g_aliases and saves in file if save=1 .
*/

int save_alias(int save)
{
	int		fd;
	int		i;
	int		err;

	if ((i = -1) && save && (fd = open(ALIAS_FILE, O_WRONLY | O_CREAT |
		S_IRUSR | S_IWUSR)) == -1)
		return (1);
	err = 0;
	while (g_aliases[++i])
	{
		if (save && *g_aliases[i] && write(fd, g_aliases[i],
			ft_strlen(g_aliases[i])) == -1)
			err = 1;
		free(g_aliases[i]);
	}
	free(g_aliases);
	return (err);
}
