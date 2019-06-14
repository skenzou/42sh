/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 20:05:06 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/04 19:45:09 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		exit_builtin(int ac, char **av)
{
	(void)ac;
	(void)av;
	save_alias(1);
	kill_pids();
	ft_printf("exit\n");
	exit(0);
	return (0);
}
