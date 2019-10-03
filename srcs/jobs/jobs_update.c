/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 06:56:09 by tlechien          #+#    #+#             */
/*   Updated: 2019/09/27 11:38:09 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** List of all the statuses a process can experience.
*/

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

/*
** Updates statuses in pid_table.
** tmp_f && tmp_s are initalised at NULL.
*/

int			update_priority(int first, t_child *tmp_f, t_child *tmp_s)
{
	t_child *save;

	save = g_pid_table;
	while (ID_PREV && ID_INDEX)
	{
		if (first)
		{
			(ID_PRIORITY == 1) ? ID_PRIORITY = 0 : 0;
			(ID_PRIORITY == 2) ? ID_PRIORITY = 1 : 0;
			(ID_INDEX == first) ? ID_PRIORITY = 2 : 0;
		}
		if (!first && (!tmp_s || tmp_f == tmp_s) && (ID_PRIORITY == 1 ||
			!ID_PRIORITY))
			tmp_s = g_pid_table;
		if (!first && (!tmp_f || tmp_f->priority < ID_PRIORITY))
		{
			(tmp_f && tmp_f->priority != -1) ? tmp_s = tmp_f : 0;
			tmp_f = g_pid_table;
		}
		g_pid_table = ID_PREV;
	}
	g_pid_table = save;
	(tmp_s && tmp_s->priority != -1) ? tmp_s->priority = 1 : 0;
	(tmp_f && tmp_f->priority != -1) ? tmp_f->priority = 2 : 0;
	return (0);
}

/*
** Updates a child depending on the result of the wait..().
*/

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
** Checks child's status and updates it.
*/

int			update_pid_table(void)
{
	int		status;

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
