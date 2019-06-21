/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 04:51:21 by tlechien          #+#    #+#             */
/*   Updated: 2019/06/21 06:42:01 by tlechien         ###   ########.fr       */
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
	char *stat;

	(s_get_values(node->status, NULL, NULL, &stat)) ? stat = "running": 0;
	(node->status == SIGHUP) ? stat = "done": 0;
	current = (node->priority < 1) ? ' ' : '-';
	(node->priority == 2) ? current = '+' : 0;
	if (option & OPT_L)
		ft_printf("[%d] %c %d %-28s %s\n", node->index, current, node->pid,
		stat, node->exec);
	else if (option & OPT_P)
		ft_printf("%d\n", node->pid);
	else
		ft_printf("[%d] %c %-28s %s\n", node->index, current,
		stat, node->exec);
	return (0);
}

static int change_status(int status)
{
	if (WIFCONTINUED(status))
		ID_STATUS = 0;
	else if (WIFEXITED(status))
	{
		ID_STATUS = ID_DONE;
		display_pid_status(g_pid_table, 1);
		return (1);
	}
	else if (WIFSIGNALED(status))
		s_child_handler(WTERMSIG(status), g_pid_table);
	else if (WIFSTOPPED(status))
		s_child_handler(WSTOPSIG(status), g_pid_table);
	return(0);
}

/*
** Checks child status and update it.
*/

int	update_pid_table(void)
{
	int	status;
	int out;

	out = 0;
	while(ID_PREV && ID_PREV->index)
		g_pid_table = ID_PREV;
	while (g_pid_table && g_pid_table->index)
	{
		if (ID_PIPE)
			update_amperpipe(g_pid_table);
		else if (waitpid(ID_PID, &status, WNOHANG | WUNTRACED | WCONTINUED))
			out += change_status(status);
		if (!ID_LEFT)
			break;
		g_pid_table = ID_LEFT;
	}
	check_remove_pids();
	if (out)
		print_prompt_prefix();
	update_priority(0);
	return (0);
}

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
			display_amperpipe(node, option);
		else if (node->pid)
			display_pid_status(node, option);
		node = node->left;
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
	t_child	*node;

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
		if ((*cmd[i] == '%' && !(!search_pid(&node, cmd[i] + 1, 0) ||
		!search_process(&node, cmd[i] + 1) || !search_index(&node, cmd[i] + 1))))
			return (err_display("jobs : job not found: ", cmd[i] + 1, "\n"));
		else if (*cmd[i] != '%' && search_process(&node, cmd[i]))
			return (err_display("jobs : job not found: ", cmd[i], "\n"));
		display_pid_status(node, options);
		i++;
	}
	return (0);
}
