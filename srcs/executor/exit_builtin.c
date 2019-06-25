/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 20:05:06 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/25 18:18:55 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		exit_builtin(int ac, char **av)
{
	unsigned char value;

	value = 0;
	if (ac > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	if (ac == 2)
		value = ft_atoi(av[1]);
	save_alias(1);
	kill_pids();
	ft_printf("exit\n");
	exit(value);
	return (0);
}
