/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 08:06:33 by aben-azz          #+#    #+#             */
/*   Updated: 2018/11/22 11:35:03 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				get_next_line(int const fd, char **line, char separator)
{
	static t_gnl	g;

	if (fd < 0 || fd > MAX || !line || (!g.s[fd] && !(g.s[fd] = ft_strnew(0))))
		return (-1);
	g.i = 0;
	while (g.s[fd] && (g.i_read = read(fd, g.buff, BUFF_SIZE)) > 0)
	{
		g.buff[g.i_read] = '\0';
		g.ptr_leak = g.s[fd];
		g.s[fd] = ft_strjoin(g.s[fd], g.buff);
		free(g.ptr_leak);
		if (ft_strchr(g.buff, separator))
			break ;
	}
	if (g.s[fd] && g.i_read >= 0 && g.s[fd][g.i])
	{
		while (g.s[fd][g.i] && g.s[fd][g.i] != separator)
			g.i++;
		*line = !g.i ? ft_strdup("") : ft_strsub(g.s[fd], 0, g.i);
		g.ptr_leak = g.s[fd];
		g.s[fd] = ft_strdup(&g.s[fd][g.i + (g.s[fd][g.i] == separator)]);
		free(g.ptr_leak);
		return ((!line || !g.s[fd]) ? -1 : 1);
	}
	return ((g.i_read || !g.s[fd]) ? -1 : 0);
}
