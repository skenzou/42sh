/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:53:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/14 03:25:30 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Checks the status of a processus.
** Returns exit value for regular exits,
** Returns -1 for anormal exits and update_pid_table.
*/

int				ft_waitprocess(pid_t pid, char **cmd)
{
	int       	status;
	t_child   	*node;
	char		*handler;
	char		*stat;

	signal(SIGTSTP, sigtstp_handler);
	waitpid(pid, &status, WUNTRACED);
	tcsetpgrp(0, getpid());
	if (WIFEXITED(status))
		return ((WEXITSTATUS(status)));
	else if (WIFSIGNALED(status))
	{
 		s_get_values(status, NULL, &handler, &stat);
 		if (status != SIGINT)
 		{
 			err_display(ANSI_RED"42sh : ", cmd[0], ": ");
 			err_display(handler, ": ", stat);
 			ft_putendl_fd(ANSI_RESET, 2);
 		}
 	}
	else if (WSTOPSIG(status))
	{
		add_pid(pid, cmd, ID_SUSP);
		search_pid(&node, NULL, pid);
		display_pid_status(node, 0);
	}
	signal(SIGTSTP, sigtstp_dflhandler);
	return (-1);
}

/*
** Forks without waiting for a return signal from the process and add him to
** the g_pid_table.
*/

int				ft_fork_amper(char **cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (FAILFORK); // fork
	if (!pid)
	{
		resetsign();
		setpgid(0, 0);
		execve(cmd[0], cmd, env);
		exit(1);
	}
	if (!waitpid(pid, &pid, WNOHANG))
		return (add_pid(pid, cmd, ID_RUN));
	return (0);
}

int				ft_fork(char **cmd, char **env)
{
	pid_t pid;

	pid = fork();
	signal(SIGINT, sigfork);
	setpgid(getpid(), getpid());
	if (pid == 0)
	{
		setpgid(0, 0);
		tcsetpgrp(0, getpgrp());
		execve(cmd[0], cmd, env);
		exit(1);
	}
	else if (pid < 0)
		return (FAILFORK);
	return (ft_waitprocess(pid, cmd));
}
