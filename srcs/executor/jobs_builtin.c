/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 04:51:21 by tlechien          #+#    #+#             */
/*   Updated: 2019/05/19 14:46:35 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

const char	*g_status[] = {
	"running",
	"done",
	"suspended",
	"continued",
	"terminated"
};

/*
** Display child status.
*/

int			display_pid_status(t_child *node, int option)
{
	char current;

	current = (node->priority < 1) ? ' ' : '-';
	(node->priority == 2) ? current = '+' : 0;
	if (option)
		ft_printf("[%d] %d %c %-10s    ", node->index, node->pid,
		node->priority, node->status);
	else
		ft_printf("[%d] %c %-10s    ", node->index, node->priority,
		node->status);
	//display_array(g_pid_table->exec); -> print_env(g_pid_table->exec);
	return (0);
}

/*
** Check child status and update it.
*/

static	int	check_pid_status(t_child **node, int option)
{
	int	status;

	if (!node || !*node || !(*node)->pid)
		return (0);
	if (!waitpid((*node)->pid, &status, WNOHANG))
		((*node)->status != S_SUSP) ? (*node)->status = 0 : 0;
	else if (WIFEXITED(status))
	{
		(*node)->priority = -1;
		(*node)->status = S_DONE;
	}
	else if (WIFSIGNALED(status))
	{
		(*node)->priority = -1;
		(*node)->status = S_TERM;
	}
	else if (WSTOPSIG(status))
		(*node)->status = S_CONT;
	else
		return (0);
	update_priority(0); // ?s
	display_pid_status(*node, option);
	ft_putendl((*node)->exec);
	return (0); // return display_pid_status
}

/*
** Recurse on the pid_table and display the bg processus.
*/

static	int	rec_pid(t_child **node, int option)
{
	if ((*node)->prev)
		rec_pid(&(*node)->prev, option);
	if ((*node)->priority != -1)
		check_pid_status(node, option);
	return (0);
}

/*
** Builtin that displays background processus with some infos.
*/

int			jobs_builtin(char **cmd)
{
	int		option;
	int		i;
	t_child	**node;

	(void)cmd; //verify that command is str + 1;
	if ((i = 0) || cmd || !cmd[0])
		return (rec_pid(&g_pid_table, 0));
	if (!(option = 0) && cmd && *cmd[0] && *cmd[0] == '-')
	{
		if (!ft_strcmp(cmd[1], "-p") && cmd++)
			option = 1;
		else if (!ft_strcmp(cmd[1], "-l") && cmd++)
			option = 2;
		else
			return (ft_printf("usage: jobs [-l|-p] [job_id...]\n") || 1);
	}
	while (cmd[i] && *cmd[i] == '%' && !(node = NULL))
	{
		if (search_pid(node, ++cmd[i], 0) && search_process(node, cmd[i])
			&& search_index(node, cmd[i]))
			break ;
		check_pid_status(node, option);
		i++;
	}
	return ((!node) ? ft_printf("jobs : job not found: %s", cmd[i]) || 1 : 0);
}
