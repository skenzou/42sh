/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 04:40:55 by tlechien          #+#    #+#             */
/*   Updated: 2019/05/15 06:01:11 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	init_pid()
{
	if (!(g_pid_table = (t_child*)malloc(sizeof(t_child))))
		return (1);
	g_pid_table->index = 0;
	g_pid_table->prev = NULL;
	g_pid_table->pid = 0;
	g_pid_table->status = 0;
	g_pid_table->exec = NULL;
	g_pid_table->next = NULL;
	return (0);
}

int kill_pids()
{
	while (g_pid_table->prev)
	{
		ft_printf("bg PID :%d is being killed.\n", g_pid_table->pid);
		kill(g_pid_table->pid, SIGTERM);
		ft_printf("command: %s ",g_pid_table->exec);
		ft_printf("address: %p ", g_pid_table);
		ft_printf("pids: %d\n", g_pid_table->pid);
		g_pid_table = g_pid_table->prev;
	}
	return (0);
}

/*
** Update statuses in pid_table.
*/

static int 	update_status()
{
	t_child *tmp;

	tmp = g_pid_table;

	while (g_pid_table->prev)
	{
		(g_pid_table->status == 1) ? g_pid_table->status = 0 : 0;
		(g_pid_table->status == 2) ? g_pid_table->status = 1 : 0;
		g_pid_table = g_pid_table->prev;
	}
  g_pid_table = tmp;
	return (0);
}

/*
** Add a new node to the pid_table.
*/

int		update_pid_table(int pid, char **command)
{
		t_child *new;

		if (!(new = (t_child*)malloc(sizeof(t_child))))
			return (FAILFORK); //TODO malloc erroc
		new->index = g_pid_table->index + 1;
		new->pid = pid;
		new->status = 2;
		new->exec = ft_strdup(command[0]);  //TODO dup_env() + proteccc
		new->next = NULL;
		new->prev = g_pid_table;
		update_status();
		g_pid_table->next = new;
		g_pid_table = new;
		ft_printf("\n[%d] %d\n", new->index, new->pid);
		return (0);
}
