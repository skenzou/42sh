/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 20:05:06 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/03 21:19:10 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		exit_builtin(int ac, char **av)
{
	(void)ac;
	(void)av;
	ft_printf("exit\n");
	exit(0);
	return (0);
}
