/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 05:05:04 by tlechien          #+#    #+#             */
/*   Updated: 2019/05/19 13:10:56 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Search for an index in the pid_table.
*/

int	search_index(t_child **node, char *str_index)
{
	t_child	*tmp;
	int		index;

	tmp = g_pid_table;
	index = ft_atoi(str_index);
	while (tmp->prev)
	{
		if (tmp->index == index)
		{
			node = &tmp;
			break ;
		}
		tmp = tmp->prev;
	}
	return ((node) ? 0 : 1);
}

/*
** Search for a child pid in the pid_table.
*/

int	search_pid(t_child **node, char *str_pid, pid_t pid)
{
	t_child	*tmp;

	if (str_pid && !(pid = ft_atoi(str_pid)))
		return (1);
	tmp = g_pid_table;
	while (tmp->prev)
	{
		if (tmp->pid == pid)
		{
			node = &tmp;
			break ;
		}
		tmp = tmp->prev;
	}
	return ((node) ? 0 : 1);
}

/*
** Search for the child with the highest priority in the pid_table.
*/

int	search_priority(t_child **node)
{
	t_child *tmp;

	tmp = g_pid_table;
	while (tmp->prev)
	{
		if (tmp->priority == 2)
		{
			node = &tmp;
			break ;
		}
		(tmp->priority == 1) ? node = &tmp : 0;
		tmp = tmp->prev;
	}
	return ((node) ? 0 : 1);
}

/*
** Search for the first child with the specified status in the pid_table.
*/

int	search_status(t_child **node, int status)
{
	t_child *tmp;

	tmp = g_pid_table;
	while (tmp->prev)
	{
		if (tmp->status == status)
		{
			node = &tmp;
			break ;
		}
		tmp = tmp->prev;
	}
	return ((node) ? 0 : 1);
}

/*
** Search for the first occurence of a processus name in the pid_table.
*/

int	search_process(t_child **node, char *p_name)
{
	t_child *tmp;

	tmp = g_pid_table;
	while (tmp->prev)
	{
		if (!ft_strcmp(tmp->exec, p_name)) //exec[0]
		{
			node = &tmp;
			break ;
		}
		tmp = tmp->prev;
	}
	return ((node) ? 0 : 1);
}
