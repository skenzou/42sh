/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:44:19 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/15 00:11:32 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			echo_builtin(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc == 1)
		ft_putchar('\n');
	if (argc > 1)
		while (++i < argc)
		{
			if (i < argc - 1)
				ft_printf("%s ", argv[i]);
			else
				ft_printf("%s\n", argv[i]);
		}
	return (0);
}
