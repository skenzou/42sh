/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 19:52:37 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/22 20:29:11 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			export_options(int ac, char **av)
{
	int i;

	if (ac > 1)
	{
		av++;
		if (**av == '-' && *((*av) + 1))
		{
			i = 0;
			while ((*av)[++i])
				if ((*av)[i] != 'p')
				{
					ft_putstr_fd("42sh: export: -", 2);
					ft_putchar_fd((*av)[i], 2);
					ft_putendl_fd(": invalid option", 2);
					return (1);
				}
			if (ac == 2)
				print_split(g_shell->env);
		}
	}
	else
		print_split(g_shell->env);
	return (0);
}
