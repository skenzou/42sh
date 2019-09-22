/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 05:04:02 by tlechien          #+#    #+#             */
/*   Updated: 2019/09/22 01:40:10 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Puts a background process in foreground and listens to it.
*/

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
		ID_STATUS = ID_DONE;
		return (0);
	}
	else if (WIFSIGNALED(status))
		s_child_handler(WTERMSIG(status), node);
	else if (WIFSTOPPED(status))
		s_child_handler(WSTOPSIG(status), node);
	tcsetpgrp(0, getpgrp());
	init_signal();
	return (1);
}

/*
** Queues all the processes in a pipe for wait_fg.
*/

static	int	setup_wait(t_child *node)
{
	int	action;
	t_child *tmp;

	if (!node->is_pipe)
		return (waitfg(node));
	while (node)
	{
		tmp = node->right;
		if (s_get_values(node->status, &action, NULL, NULL) ||
			action == S_CONT || action == S_STOP)
			waitfg(node);
		node = tmp;
	}
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
			return (setup_wait(node));
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
		if ((ret = setup_wait(node)))
			return (ret);
	}
	return (0 && ac);
}
