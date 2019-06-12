/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 21:14:00 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/06 20:51:56 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		env_builtin(int ac, char **av)
{
	(void)ac;
	(void)av;
	print_split(g_shell->env_tmp);
	return (0);
}
