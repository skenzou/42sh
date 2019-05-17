/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 04:40:55 by tlechien          #+#    #+#             */
/*   Updated: 2019/05/17 09:50:05 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	init_pid()
{
	if (!(g_pid_table = (t_child*)ft_memalloc(sizeof(t_child))))
		return (1);
	return (0);
}

int kill_pids()
{
	while (ID_PREV)
	{
		ft_printf("bg PID :%d is being killed.\n", ID_PID);
		kill(ID_PID, SIGTERM);
		ft_printf("command: %s ",ID_EXEC);
		ft_printf("address: %p ", g_pid_table);
		ft_printf("pids: %d\n", ID_PID);
		g_pid_table = ID_PREV;
	}
	return (0);
}

/*
** Update statuses in pid_table.
*/

int 	update_priority(int first)
{
	t_child *tmp_f;
  t_child *tmp_s;
  t_child *save;

	save = g_pid_table;
  tmp_f = NULL;
  tmp_s = NULL;
	while (ID_PREV)
	{
    if (first)
    {
      (ID_PRIORITY == 1) ? ID_PRIORITY = 0 : 0;
      (ID_PRIORITY == 2) ? ID_PRIORITY = 1 : 0;
      (ID_INDEX == first) ? ID_PRIORITY = 2 : 0;
    }
    else
      if (!tmp_f || tmp_f->priority < ID_PRIORITY)
        tmp_f = g_pid_table;
    if (((!tmp_s && !ID_PRIORITY) || ID_PRIORITY == 1) && g_pid_table != tmp_f)
        tmp_s = g_pid_table;
    g_pid_table = ID_PREV;
  }
  (tmp_s && (!tmp_s->priority || tmp_s->priority == 1)) ?
    tmp_s->priority = 1 : 0;
  (tmp_f && tmp_f->priority != -1) ? tmp_f->priority = 2 : 0;
  g_pid_table = save;
	return (0);
}

/*
** Add a new node to the pid_table.
*/

int		update_pid_table(int pid, char **command, int status)
{
		t_child *new;

		if (!(new = (t_child*)malloc(sizeof(t_child))))
			return (FAILFORK); //TODO malloc erroc
		new->index = g_pid_table->index + 1;
		new->pid = pid;
		new->status = status;
    new->priority = 0;
		new->exec = ft_strdup(command[0]);  //TODO dup_env() + proteccc
		new->next = NULL;
		new->prev = g_pid_table;
		ID_NEXT = new;
		g_pid_table = new;
    update_priority((status == S_SUSP) ? new->index : 0);
		ft_printf("\n[%d] %d\n", new->index, new->pid);
		return (0);
}
