/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 11:44:34 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/07 05:44:29 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int			check_options(int ac, char **av, char *flag)
{
	int i;

	*flag = 0;
	if (ac > 1)
	{
		av++;
		if (ft_strequ(*av, "--"))
		{
			*flag = '-';
			return (0);
		}
		if (**av == '-' && *((*av) + 1) && !(i = 0))
		{
			while ((*av)[++i])
				if ((*av)[i] != 'L' && (*av)[i] != 'P')
				{
					ft_putstr_fd("42sh: cd: -", 2);
					ft_putchar_fd((*av)[i], 2);
					ft_putendl_fd(": invalid option", 2);
					return (1);
				}
			*flag = (*av)[i - 1];
		}
	}
	return (0);
}

static	int			cd_home(char flag)
{
	char *value;

	value = get_key_value("HOME", g_shell->env_tmp);
	if (!value)
		value = get_key_value("HOME", g_shell->intern_tmp);
	if (value)
		return (change_dir(value, flag));
	else
	{
		ft_putendl_fd("42sh: cd: HOME not set", 2);
		return (1);
	}
}

static int			cd_oldpwd(char flag)
{
	char	*path;
	int		ret;

	ret = 0;
	path = get_oldpwd(g_shell->env_tmp);
	if (!path)
		path = get_oldpwd(g_shell->intern_tmp);
	if (!path)
	{
		ft_putendl_fd("42sh: cd: OLDPWD not set", 2);
		return (1);
	}
	ft_printf("%s\n", path);
	ret = change_dir(path, flag);
	ft_strdel(&path);
	return (ret);
}

static int			regular_cd(char *dir, char flag)
{
	int		ret;
	char	*path;

	path = get_path(dir);
	ret = change_dir(path, flag);
	ft_strdel(&path);
	return (ret);
}

int					cd_builtin(int ac, char **av)
{
	int		same;
	char	flag;
	int		ret;

	same = g_shell->env == g_shell->env_tmp;
	if (check_options(ac, av, &flag))
		return (1);
	if (flag)
		av++ && ac--;
	if (ac == 1)
		ret = cd_home(flag);
	else if (ac > 1 && ft_strequ(av[1], "-"))
		ret = cd_oldpwd(flag);
	else
		ret = regular_cd(av[1], flag);
	if (same)
		g_shell->env_tmp = g_shell->env;
	return (ret);
}
