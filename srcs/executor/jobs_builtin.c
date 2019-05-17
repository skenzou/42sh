/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 04:51:21 by tlechien          #+#    #+#             */
/*   Updated: 2019/05/17 10:41:34 by tlechien         ###   ########.fr       */
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

int display_pid_status(int index, char prio, int status, char **command)
{
	char current;

	current = (prio < 1) ? ' ' : '-';
	(prio == 2) ? current = '+' : 0;
	(void)command;
	ft_printf("[%d] %c %-10s    ", index, current, g_status[status]);
	//display_array(g_pid_table->exec); -> print_env(g_pid_table->exec);
	return (0);
}

/*
** Check child status and update it.
*/

static  int check_pid_status(t_child **node)
{
	int   status;

  if (!node || !*node || !(*node)->pid)
    return (0);
  if (!waitpid((*node)->pid, &status, WNOHANG))
    ((*node)->status != S_SUSP) ? (*node)->status = 0: 0;
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
  update_priority(0); // ?
	display_pid_status((*node)->index, (*node)->priority, (*node)->status,
											&(*node)->exec);
	ft_putendl((*node)->exec);
  return (0); // return display_pid_status
}

/*
** Recurse on the pid_table and display the bg processus.
*/

static int rec_pid(t_child **node)
{
  if ((*node)->prev)
    rec_pid(&(*node)->prev);
	if ((*node)->priority != -1)
  check_pid_status(node);
  return (0);
}

/*
** Builtin that displays background processus with some infos.
*/

int jobs_builtin(char **command)
{
	(void)command;
	rec_pid(&g_pid_table);
  return (0);
}
