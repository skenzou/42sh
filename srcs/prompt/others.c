/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:35:56 by aben-azz          #+#    #+#             */
/*   Updated: 2019/11/12 20:07:53 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_put_termcaps(int c)
{
	write(1, &c, 1);
	return (1);
}

int		multi_putstr_fd(char *s1, char *s2, char *s3)
{
	if (s1)
		ft_putstr_fd(s1, 0);
	if (s2)
		ft_putstr_fd(s2, 0);
	if (s3)
		ft_putstr_fd(s3, 0);
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
			if ((status = ft_strdup(str + ft_lastindexof(str, '/') + 1)))
			{
				ft_strdel(&str);
				return (status);
			}
			else
			{
				ft_strdel(&str);
				return (NULL);
			}
			i++;
		}
		close(fd);
	}
	return (NULL);
}

int		ft_clean_eol(t_cap *tcap)
{
	int		len;
	int		j;
	char	*str;
	int		i;

	len = 0;
	i = -1;
	while (tcap->command[++i])
		if (tcap->command[i] != '\n')
			len++;
	if (!(str = ft_strnew(len)))
		return (tcap->char_len);
	i = -1;
	j = 0;
	while (tcap->command[++i])
	{
		if (tcap->command[i] != '\n')
			str[j++] = tcap->command[i];
	}
	ft_bzero(tcap->command, BUFFSIZE);
	ft_strcpy(tcap->command, str);
	ft_strdel(&str);
	return (len);
}
