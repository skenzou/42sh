/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 06:56:09 by tlechien          #+#    #+#             */
/*   Updated: 2019/09/20 23:11:04 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

	(s_get_values(node->status, NULL, NULL, &stat)) ? stat = "running" : 0;
	(node->status == SIGHUP) ? stat = "done" : 0;
	current = (node->priority < 1) ? ' ' : '-';
	(node->priority == 2) ? current = '+' : 0;
	if (option & OPT_L)
		printf("\r[%d] %c %d %-28s %s\n", node->index, current, node->pid,
		stat, node->exec);
	else if (option & OPT_P)
		printf("%d\n", node->pid);
	else
		printf("[%d] %c %-28s %s\n", node->index, current,
		stat, node->exec);
	return (0);
}

static int	change_status(int status)
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
	return (0);
}

/*
** Checks child status and update it.
*/

int			update_pid_table(void)
{
	int		status;

	g_shell->dprompt = 0;
	g_shell->chld_check = 1;
	while (ID_PREV && ID_PREV->index)
		g_pid_table = ID_PREV;
	while (g_pid_table && g_pid_table->index)
	{
		if (ID_PIPE)
			update_amperpipe(g_pid_table);
		else if (waitpid(ID_PID, &status, WNOHANG | WUNTRACED | WCONTINUED))
			change_status(status);
		if (!ID_LEFT)
			break ;
		g_pid_table = ID_LEFT;
	}
	while (g_shell->chld_check == 1 && !(g_shell->chld_check = 0))
	{
		waitabit(0, 1000000);
		check_remove_pids();
	}
	check_remove_pids();
	update_priority(0, NULL, NULL);
	return (0);
}
