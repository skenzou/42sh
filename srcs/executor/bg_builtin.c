/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 10:57:28 by tlechien          #+#    #+#             */
/*   Updated: 2019/06/14 01:43:21 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Builtin that resumes interruped processus.
**  Needs protection on already finished process ??
*/

static	int	bg_all(t_child *node)
{
	int		job_done;

	job_done = 0;
	while (node->prev)
		node = node->prev;
	while (node)
	{
		if (node->pid && (node->status == ID_SUSP || node->status == SIGSTOP
		|| node->status == SIGTTIN || node->status == SIGTTOU) && ++job_done)
			bg_resume(&node);
		node = node->next;
	}
	return ((job_done) ? 0 : err_display("bg: no current job\n", NULL, NULL));
}

int			bg_builtin(int ac, char **cmd)
{
	t_child	*node;
	int		i;
	int		ret;

	(void)ac;
	ret = 0;
	node = NULL;
	if ((i = 1) && !cmd[i])
		return (bg_all(g_pid_table));
	while (cmd[i] && *cmd[i] == '%')
	{
		if ((*cmd[i] == '%' && !(!search_pid(&node, cmd[i] + 1, 0) ||
		!search_process(&node, cmd[i] + 1) || !search_index(&node, cmd[i] + 1))))
			return (err_display("bg : job not found: ", cmd[i] + 1, "\n"));
		else if (*cmd[i] != '%' && search_process(&node, cmd[i]))
			return (err_display("bg : job not found: ", cmd[i], "\n"));;
		if ((ret = bg_resume(&node)))
			break ;
		i++;
	}
	if (!node && (ret = 1))
		err_display("bg: ", cmd[i],": no such job\n");
	else if (ret)
		err_display("bg: job already in background\n", NULL, NULL);
	return (ret);
}

int			bg_resume(t_child **node)
{
	if (!node || ((*node)->status != ID_SUSP && (*node)->status != SIGSTOP  &&
	(*node)->status != SIGTTIN && (*node)->status != SIGTTOU) ||
	kill((*node)->pid, SIGCONT))
		return (1);
	(*node)->priority = 0;
	(*node)->status = ID_RUN;
	display_pid_long(*node, 1);
	return (0);
}
