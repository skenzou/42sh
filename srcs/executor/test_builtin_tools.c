/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghamelek <ghamelek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 01:38:54 by ghamelek          #+#    #+#             */
/*   Updated: 2019/06/23 15:51:55 by Mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_integer(char *str, char *str2)
{
	int i;

	i = -1;
	while (str[++i] && ft_isdigit(str[i]))
		continue ;
	if (str[i])
	{
		ft_putstr_fd("42sh: integer expression expected: ", 2);
		ft_putendl_fd(str, 2);
		return (2);
	}
	i = -1;
	while (str2[++i] && ft_isdigit(str2[i]))
		continue ;
	if (str2[i])
	{
		ft_putstr_fd("42sh: integer expression expected: ", 2);
		ft_putendl_fd(str2, 2);
		return (2);
	}
	return (0);
}

int		arithmetic_test(char **av, char *op)
{
	if (is_integer(av[1], av[3]))
		return (2);
	if (!ft_strcmp(op, "-eq"))
		return (!(ft_atoi(av[1]) == ft_atoi(av[3])));
	else if (!ft_strcmp(av[2], "-ne"))
		return (ft_atoi(av[1]) == ft_atoi(av[3]));
	else if (!ft_strcmp(av[2], "-ge"))
		return (ft_atoi(av[1]) < ft_atoi(av[3]));
	else if (!ft_strcmp(av[2], "-lt"))
		return (ft_atoi(av[1]) >= ft_atoi(av[3]));
	return (ft_atoi(av[1]) > ft_atoi(av[3]));
}
