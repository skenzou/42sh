/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 20:05:06 by midrissi          #+#    #+#             */
/*   Updated: 2019/11/09 16:51:48 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		shell_exit(int err_code)
{
	if (err_code)
		ft_printf(ANSI_RED"42sh encountered error %d.\n"ANSI_RESET, err_code);
	save_alias(1);
	empty_table();
	kill_pids();
	exit(1);
	return (1);
}

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
	empty_table();
	kill_pids();
	exit(value);
	return (0);
}
