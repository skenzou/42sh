/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghamelek <ghamelek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 00:34:44 by ghamelek          #+#    #+#             */
/*   Updated: 2019/06/23 01:39:55 by ghamelek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static	int		binary_test(char **av)
{
	if (!ft_strcmp(av[2], "="))
		return ((ft_strcmp(av[1], av[3]) != 0));
	else if (!ft_strcmp(av[2], "!="))
		return ((ft_strcmp(av[1], av[3]) == 0));
	else if (!ft_strcmp(av[2], "-eq"))
		return (arithmetic_test(av, "-eq"));
	else if (!ft_strcmp(av[2], "-ne"))
		return (arithmetic_test(av, "-ne"));
	else if (!ft_strcmp(av[2], "-ge"))
		return (arithmetic_test(av, "-ge"));
	else if (!ft_strcmp(av[2], "-lt"))
		return (arithmetic_test(av, "-lt"));
	else if (!ft_strcmp(av[2], "-le"))
		return (arithmetic_test(av, "-le"));
	else if (av[2][0] == '-')
	{
		ft_putstr_fd(av[0], 2);
		ft_putstr_fd(": unknown condition: ", 2);
		ft_putendl_fd(av[1], 2);
		return (2);
	}
	ft_putstr_fd("42sh: parse error: condition expected: ", 2);
	ft_putendl_fd(av[2], 2);
	return (1);
}

static	int		suit_unary_test(char **av, struct stat *buf)
{
	if (!ft_strcmp(av[1], "-u"))
		return ((buf->st_mode & S_ISUID) == 0);
	else if (!ft_strcmp(av[1], "-s"))
		return (!(buf->st_size > 0));
	else if (!ft_strcmp(av[1], "-r"))
		return (access(av[2], R_OK) != 0);
	else if (!ft_strcmp(av[1], "-w"))
		return ((access(av[2], W_OK) != 0));
	else if (!ft_strcmp(av[1], "-x"))
		return ((access(av[2], X_OK) != 0));
	else if (!ft_strcmp(av[1], "-z"))
		return ((ft_strlen2(av[2]) != 0));
	else if (av[1][0] == '-')
	{
		ft_putstr_fd(av[0], 2);
		ft_putstr_fd(": unknown condition: ", 2);
		ft_putendl_fd(av[1], 2);
		return (2);
	}
	ft_putstr_fd("42sh: parse error: condition expected: ", 2);
	ft_putendl_fd(av[1], 2);
	return (1);
}

static	int		unary_test(char **av)
{
	struct stat		*buf;
	int				ret;

	buf = malloc(sizeof(struct stat));
	ret = lstat(av[2], buf);
	if (!ft_strcmp(av[1], "-b"))
		return (!((buf->st_mode & S_IFMT) == S_IFBLK));
	else if (!ft_strcmp(av[1], "-c"))
		return (!((buf->st_mode & S_IFMT) == S_IFCHR));
	else if (!ft_strcmp(av[1], "-d"))
		return (!((buf->st_mode & S_IFMT) == S_IFDIR));
	else if (!ft_strcmp(av[1], "-e"))
		return (!(ret == 0));
	else if (!ft_strcmp(av[1], "-f"))
		return (!(S_ISREG(buf->st_mode)));
	else if (!ft_strcmp(av[1], "-g"))
		return (!(S_ISGID & buf->st_mode));
	else if (!ft_strcmp(av[1], "-L"))
		return (!(S_ISLNK(buf->st_mode)));
	else if (!ft_strcmp(av[1], "-p"))
		return (!((buf->st_mode & S_IFMT) == S_IFIFO));
	else if (!ft_strcmp(av[1], "-S"))
		return (!(S_ISSOCK(buf->st_mode)));
	return (suit_unary_test(av, buf));
}

int				builtin_tools(int *ac, char **av)
{
	if (ft_strequ(av[0], "["))
	{
		if (ft_strequ(av[*ac - 1], "]"))
			ft_strdel(&av[--*ac]);
		else
		{
			ft_putendl_fd("[: ']' expected", 2);
			return (1);
		}
	}
	return (0);
}

int				test_builtin(int ac, char **av)
{
	int i;
	int j;
	int not;

	if (builtin_tools(&ac, av))
		return (1);
	i = 0;
	while ((j = 1) && av[++i] && !ft_strcmp(av[i], "!"))
		ft_strdel(&av[i]);
	not = ((i - 1) && !(i % 2));
	ac = ac - i;
	while (i && av[i])
		av[j++] = av[i++];
	while (av[j])
		av[j++] = NULL;
	if (ac == 0)
		return (!not);
	else if ((ac == 1) || (ac == 2 && not))
		return (not & (int)av[ac]);
	else if (ac == 2)
		return (not ^ unary_test(av));
	else if (ac == 3)
		return (not ^ binary_test(av));
	ft_putendl_fd("test: too many arguments", 2);
	return (1);
}
