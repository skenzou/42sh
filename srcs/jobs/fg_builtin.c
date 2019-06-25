/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 05:04:02 by tlechien          #+#    #+#             */
/*   Updated: 2019/06/25 03:10:58 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

static int	waitfg(t_child *node)
{
	int	status;

	signal(SIGCHLD, SIG_DFL);
	signal(SIGINT, sigchld_handler);
	signal(SIGTSTP, sigtstp_handler);
	if (node && node->status != 0 && ((node->status = SIGCONT) || 1))
		kill(node->pid, SIGCONT);
	display_pid_status(node, 1);
	tcsetpgrp(0, (node->pid));
	waitpid(node->pid, &status, WUNTRACED);
	if (WIFEXITED(status))
	{
		ID_PRIORITY = -1;
		ID_STATUS = ID_DONE;
		display_pid_status(g_pid_table, 0);
		remove_pid(node);
	}
	else if (WIFSIGNALED(status))
		s_child_handler(WTERMSIG(status), node);
	else if (WIFSTOPPED(status))
		s_child_handler(WSTOPSIG(status), node);
	tcsetpgrp(0, getpgrp());
	init_signal();
	return (0);
}

/*
** Builtin that gives back focus to background processus.
**  Needs protection on already finished process ??
*/

int			fg_builtin(int ac, char **cmd)
{
	t_child	*node;
	int		i;
	int		ret;

	cmd++;
	node = NULL;
	if (!(i = 0) && !cmd[0])
	{
		search_priority(&node);
		if (node)
			return (waitfg(node));
		return (err_display("fg: no current job\n", NULL, NULL));
	}
	while (cmd[++i] && *cmd[i])
	{
		if ((*cmd[i] == '%' && !(!search_pid(&node, cmd[i] + 1, 0) ||
		!search_process(&node, cmd[i] + 1) ||
		!search_index(&node, cmd[i] + 1))))
			return (err_display("fg : job not found: ", cmd[i] + 1, "\n"));
		else if (*cmd[i] != '%' && search_process(&node, cmd[i]))
			return (err_display("fg : job not found: ", cmd[i], "\n"));
		if ((ret = waitfg(node)))
			return (ret);
	}
	return (0 && ac);
}
