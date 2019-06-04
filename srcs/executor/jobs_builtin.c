/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 04:51:21 by tlechien          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/06/04 19:57:27 by tlechien         ###   ########.fr       */
=======
/*   Updated: 2019/06/04 22:22:09 by tlechien         ###   ########.fr       */
>>>>>>> tlechien
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
** Displays child status.
*/

int			display_pid_status(t_child *node, char option)
{
	char current;

	current = (node->priority < 1) ? ' ' : '-';
	(node->priority == 2) ? current = '+' : 0;
	if (option & OPT_L)
		ft_printf("[%d] %d %c %-10s    \n", node->index, node->pid,
		current, node->exec);
	else if (option & OPT_P)
		ft_printf("%d\n", node->pid);
	else
		ft_printf("[%d] %c %-10s    \n", node->index, current,
		node->exec);
	//display_array(g_pid_table->exec); -> print_env(g_pid_table->exec);
	return (0);
}

/*
** Checks child status and update it.
*/
int	update_pid_table(void)
{
	int	status;
	int prio;

	while(ID_PREV && ID_PREV->index)
		g_pid_table = ID_PREV;
	while (g_pid_table && g_pid_table->index)
	{
		 prio = ID_PRIORITY;
		if (!waitpid(ID_PID, &status, WNOHANG))
			(ID_STATUS != S_SUSP) ? ID_STATUS = 0 : 0;
		else if (WIFEXITED(status))
		{
			(prio != -1 && ID_PID) ? display_pid_status(g_pid_table, 0) : 0;
			ID_PRIORITY = -1;
			ID_STATUS = S_DONE;
		}
		else if (WIFSIGNALED(status))
		{
			(prio != -1 && ID_PID) ? display_pid_status(g_pid_table, 0) : 0;
			ID_PRIORITY = -1;
			ID_STATUS = S_TERM;
		}
		else if (WSTOPSIG(status))
			ID_STATUS = S_CONT;
		if (!ID_NEXT)
			break;
		g_pid_table = ID_NEXT;
	}
	update_priority(0); // ?s
	return (0);
}

/*
static	int	check_pid_status(t_child **node, char option)
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
	//display_pid_status(*node, option);
	//ft_putendl((*node)->exec);
	return (0); // return display_pid_status
}*/

/*
** Recurses on the pid_table and displays the bg processus.
*/

static int	all_pid(t_child *node, char option)
{
	while (node->prev)
		node = node->prev;
	while (node)
	{
		if (node->priority != -1 && node->pid)
			display_pid_status(node, option);
		node = node->next;
	}
	return (0);
}

static int usage_jobs(void)
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
<<<<<<< HEAD
	t_child	**node;
=======
	t_child	*node;
>>>>>>> tlechien

	(void)ac;
	cmd++;
	i = 0;
	options = 0;
	pod[0] = &options;
	pod[1] = "lp";
	if ((i = params(pod, ft_arraylen(cmd), cmd, usage_jobs)) == -1)
		return (1);
	if (!cmd || !cmd[i])
		return (all_pid(g_pid_table, options));
	while (cmd[i] && !(node = NULL))
	{
<<<<<<< HEAD
		if ((*cmd[i] == '%' && (search_pid(node, cmd[i] + 1, 0) ||
		search_process(node, cmd[i] + 1) || search_index(node, cmd[i] + 1))))
			return (ft_printf("jobs : job not found: %s\n", cmd[i] + 1));
		else if (search_process(node, cmd[i]))
			return (ft_printf("jobs : job not found: %s\n", cmd[i]));
		display_pid_status(*node, options);
=======
		//search_pid(&node,cmd[i] + 1, 0);
		//ft_printf("pid:[%d] %d %d %-10s    \n", node->index, node->pid,node->priority, node->exec);
		if ((*cmd[i] == '%' && !(!search_pid(&node, cmd[i] + 1, 0) ||
		!search_process(&node, cmd[i] + 1) || !search_index(&node, cmd[i] + 1))))
			return (err_display("jobs : job not found: ", cmd[i] + 1, "\n"));
		else if (*cmd[i] != '%' && search_process(&node, cmd[i]))
			return (err_display("jobs : job not found: ", cmd[i], "\n"));
		display_pid_status(node, options);
>>>>>>> tlechien
		i++;
	}
	return (0);
}
