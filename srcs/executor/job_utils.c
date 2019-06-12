/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 04:40:55 by tlechien          #+#    #+#             */
/*   Updated: 2019/06/12 16:04:03 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	init_pid(void)
{
	if (!(g_pid_table = (t_child*)ft_memalloc(sizeof(t_child))))
		return (1);
	return (0);
}

int	kill_pids(void)
{
	while (ID_PID != 0)
	{
		//ft_printf("bg PID :%d is being killed.\n", ID_PID);
		if (!kill(ID_PID, SIGHUP))
			ID_STATUS = SIGHUP;
		else if (!kill(ID_PID, SIGTERM))
			ID_STATUS = SIGTERM;
		else
		{
			err_display(ANSI_RED"42sh: can't kill process: ", ID_EXEC,
			": pid >");
			ft_putnbr_fd(ID_PID, 2);
			ft_putendl_fd(ANSI_RESET, 2);
		}
		display_pid_long(g_pid_table, 2);
		remove_pid();
	}
	return (0);
}

/*
** Updates statuses in pid_table.
*/

int	update_priority(int first)
{
	t_child *tmp_f;
	t_child *tmp_s;
	t_child *save;

	save = g_pid_table;
	tmp_f = NULL;
	tmp_s = NULL;
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
		/*ft_printf("debug  :[%d] %d %d %-10s    \n", ID_INDEX, ID_PID, ID_PRIORITY, ID_EXEC);
		(tmp_f)?ft_printf("debug_f:[%d] %d %d %-10s    \n", tmp_f->index, tmp_f->pid,tmp_f->priority, tmp_f->exec):0;
		(tmp_s)?ft_printf("debug_s:[%d] %d %d %-10s    \n", tmp_s->index, tmp_s->pid,tmp_s->priority, tmp_s->exec):0;*/
		g_pid_table = ID_PREV;

	}
	g_pid_table = save;
	(tmp_s && tmp_s->priority != -1) ? tmp_s->priority = 1 : 0;
	(tmp_f && tmp_f->priority != -1) ? tmp_f->priority = 2 : 0;
	return (0);
}

int	remove_pid(void)
{
	t_child *curr;

	curr = (ID_NEXT)? ID_NEXT : ID_PREV;
	(ID_PREV) ? ID_PREV->next = ID_NEXT : 0;
	(ID_NEXT) ? ID_NEXT->prev = ID_PREV : 0;
	ft_strdel(&ID_EXEC);
	free (g_pid_table);
	g_pid_table = curr;
	return (0);
}

/*
** Adds a new node to the pid_table.
*/

int	add_pid(int pid, char **command, int status)
{
	t_child *new;

	if (!(new = (t_child*)malloc(sizeof(t_child))))
		exit(FAILFORK); //TODO malloc erroc
	new->index = g_pid_table->index + 1;
	new->pid = pid;
	new->status = status;
	new->priority = 0;
	new->exec = ft_strdup(command[0]);  //TODO dup_env() + proteccc
	new->next = NULL;
	new->prev = g_pid_table;
	ID_NEXT = new;
	g_pid_table = new;
	update_priority(new->index);
	ft_printf("[%d] %d\n", new->index, new->pid);
	return (0);
}
