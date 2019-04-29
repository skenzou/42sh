/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:44:19 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/29 18:02:29 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
