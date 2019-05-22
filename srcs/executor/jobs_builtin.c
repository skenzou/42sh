/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 04:51:21 by tlechien          #+#    #+#             */
/*   Updated: 2019/05/15 05:56:01 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
/*
static int display_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		ft_putstr(array[i]);
    ft_putchar(' ');
		i++;
	}
	return (0);
}
*/
/*
** Check and display the status of a pid_table node.
*/

static int check_pid_status(t_child *node)
{
  int   status;
  char  pstat;

  if (!node || !node->pid)
    return (0);
  if (!waitpid(node->pid, &status, WNOHANG))
  {
    pstat = (node->status == 2) ? '+': ' ';
    (node->status == 1) ? pstat = '-': 0;
    ft_printf("[%d] %c running    ", node->index, pstat);
    //display_array(g_pid_table->exec); -> print_env(g_pid_table->exec);
    ft_putstr(node->exec);
    ft_putchar('\n');
  }
  return (0);
}

/*
** Recurse on the pid_table and display the bg processus.
*/

static int rec_pid(t_child *node)
{
  if (node->prev)
    rec_pid(node->prev);
  check_pid_status(node);
  return (0);
}

/*
** Builtin that displays background processus with some infos.
*/

int jobs_builtin(char **command)
{
	(void)command;
	rec_pid(g_pid_table);
  return (0);
}
