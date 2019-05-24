/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 16:01:10 by tlechien          #+#    #+#             */
/*   Updated: 2019/05/24 18:35:20 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Initializes the global g_aliases from void or file.
*/

int		init_alias(int file)
{
	int		fd;
	int		i;
	char	*line;
	int		ret;

	fd = (file) ? open(ALIAS_FILE, O_RDONLY | O_CREAT, S_IRUSR |
		S_IWUSR) : 0;
	i = 1;
	ret = 0;
	if (fd == -1)
		exit(1); //TODO
	while (fd && (ret = get_next_line(fd, &line, '\n')) == 1)
	{
		free(line);
		i++;
	}
	if (ret == -1 || (file && close(fd) == -1) || (file && (fd = open(
		ALIAS_FILE, O_RDONLY, S_IRUSR | S_IWUSR)) == -1))
		return (1);
	g_aliases = (char **)ft_memalloc(sizeof(char *) * i);
	i = -1;
	while (file && (ret = get_next_line(fd, &line, '\n')) == 1)
		g_aliases[++i] = line;
	return (((file && close(fd) == -1) || ret == -1) ? 1 : 0);
}

/*
**	Substitute aliases in the command line.
*/

char	*substitute_alias(char **origin, char *line, int size)
{
	char	*p1;
	char	*p2;
	char	*tmp;
	int		len;
	int		off;

	tmp = ft_strsub(line, 0, size);
	p2 = get_alias(tmp);
	ft_strdel(&tmp);
	if (!p2)
		return (line);
	len = ft_strlen2(p2);
	off = line - *origin;
	if (!(p1 = (off) ? ft_strsub(*origin, 0, line - *origin) : ft_strdup("")))
		exit(1); //TODO
	if (!(tmp = ft_strjoin(p1, p2)))
		exit(1); //TODO
	ft_strdel(&p1);
	ft_strdel(&p2);
	if (!(p1 = ft_strjoin(tmp, line + size)))
		exit(1); //TODO
	(tmp) ? ft_strdel(&tmp) : 0;
	ft_strdel(origin);
	*origin = p1;
	return (&p1[len + off]);
}

/*
**	Parses the line and substitute the aliases.
*/

char	*parse_aliases(char *line, char *origin, char *prev)
{
	t_oplist	curr;
	int			is_first;

	is_first = 1;
	while (*line && *line)
	{
		curr = check_ops(line);
		if ((curr.op) && prev != line && is_first && !(is_first = 0))
			line = substitute_alias(&origin, prev, line - prev);//TODO check if alias
		if (curr.op)
		{
			(curr.type == TOKEN_CTL_OPERATOR) ? is_first = 1 : 0;
			line += curr.len;
			prev = line;
		}
		else
			line++;
	}
	if (prev != line && is_first)
		line = substitute_alias(&origin, prev, line - prev);//TODO check if alias
	return (origin);
}

/*
**	Frees the global g_aliases and saves in file if save=1 .
*/

int		save_alias(int save)
{
	int		fd;
	int		i;
	int		err;

	i = -1;
	if (save && (fd = open(ALIAS_FILE, O_WRONLY | O_CREAT |
		O_TRUNC | S_IRUSR | S_IWUSR)) == -1)
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
