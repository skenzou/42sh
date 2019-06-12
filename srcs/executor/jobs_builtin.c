/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 04:51:21 by tlechien          #+#    #+#             */
/*   Updated: 2019/06/12 13:47:50 by tlechien         ###   ########.fr       */
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

int display_pid_long(t_child *node, int fd)
{
	char current;
	char *stat;

	(s_get_values(node->status, NULL, NULL, &stat)) ? stat = "running": 0;
	current = (node->priority < 1) ? ' ' : '-';
	(node->priority == 2) ? current = '+' : 0;
	ft_putchar_fd('[', fd);
	ft_putnbr_fd(node->index, fd);
	ft_putstr_fd("] ", fd);
	ft_putchar_fd(current, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(node->pid, fd);
	ft_putchar_fd(' ', fd);
	ft_putstr_fd(stat, fd);
	write (fd,"                       ", 23 - ft_strlen2(stat));
	ft_putstr_fd(node->exec, fd);
	ft_putchar_fd('\n', fd);
	//print_prompt_prefix();
	return (0);
}

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
		ft_printf("[%d] %c %d %-22s %s\n", node->index, current, node->pid,
		stat, node->exec);
	else if (option & OPT_P)
		ft_printf("%d\n", node->pid);
	else
		ft_printf("[%d] %c %-22s %s\n", node->index, current,
		stat, node->exec);
	if (node->status == SIGHUP)
		print_prompt_prefix();
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
		if (!waitpid(ID_PID, &status, WNOHANG | WUNTRACED | WCONTINUED))
			;
		else if (WIFCONTINUED(status))
			ID_STATUS = 0;
		else if (WIFEXITED(status))
		{
			ID_PRIORITY = -1;
			ID_STATUS = ID_DONE;
			display_pid_status(g_pid_table, 0);
			remove_pid();
		}
		else if (WIFSIGNALED(status))
			s_child_handler(status, g_pid_table);
		else if (WIFSTOPPED(status))
			s_child_handler(status, g_pid_table);
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
		//search_pid(&node,cmd[i] + 1, 0);
		//ft_printf("pid:[%d] %d %d %-10s    \n", node->index, node->pid,node->priority, node->exec);
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
