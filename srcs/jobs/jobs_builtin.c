/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 04:51:21 by tlechien          #+#    #+#             */
/*   Updated: 2019/09/24 03:14:20 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Recurses on the pid_table and displays the bg processus.
*/

static int	all_pid(t_child *node, char option)
{
	while (node->prev)
		node = node->prev;
	while (node)
	{
		if (node->is_pipe)
			display_amperpipe(node, option, NULL, 0);
		else if (node->pid)
			display_pid_status(node, option);
		node = node->left;
	}
	return (0);
}

static int	usage_jobs(void)
{
	ft_putstr_fd("usage: jobs [-l|-p] [job_id...]\n", 2);
	return (-1);
}

/*
** Builtin that displays background processus with some infos.
*/

int			jobs_builtin(int ac, char **cmd)
{
	char	options;
	char	*pod[2];
	int		i;
	t_child	*node;

	(void)ac;
	cmd++;
	options = 0;
	pod[0] = &options;
	pod[1] = "lp";
	if ((i = params(pod, ft_arraylen(cmd), cmd, usage_jobs)) == -1)
		return (1);
	if (!cmd || !cmd[i])
		return (all_pid(g_pid_table, options));
	while (cmd[i] && !(node = NULL))
	{
		if ((*cmd[i] == '%' && !(!search_pid(&node, cmd[i] + 1, 0) || !
		search_process(&node, cmd[i] + 1) | !search_index(&node, cmd[i] + 1))))
			return (err_display("jobs : job not found: ", cmd[i] + 1, "\n"));
		else if (*cmd[i] != '%' && search_process(&node, cmd[i]))
			return (err_display("jobs : job not found: ", cmd[i], "\n"));
		display_pid_status(node, options);
		i++;
	}
	return (0);
}
