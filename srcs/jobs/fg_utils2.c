/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 03:05:33 by tlechien          #+#    #+#             */
/*   Updated: 2019/09/24 03:05:37 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Searches for a certain priority in the pid_table.
*/

int	search_prio(t_child **node, char *str_index)
{
	t_child	*tmp;
	int		prio;

	tmp = g_pid_table;
	if (!ft_strcmp(str_index, "+"))
		prio = 2;
	else if (!ft_strcmp(str_index, "-"))
		prio = 1;
	else
		return (1);
	while (tmp->prev)
	{
		if ((prio == 2 && tmp->priority == 2) ||
		(prio == 1 && tmp->priority == 1))
		{
			*node = tmp;
			return (0);
		}
		tmp = tmp->prev;
	}
	return (1);
}
