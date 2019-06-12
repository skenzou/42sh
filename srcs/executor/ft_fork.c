/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:53:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/12 13:50:15 by tlechien         ###   ########.fr       */
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

	signal(SIGCHLD, SIG_DFL);
	waitpid(pid, &status, WUNTRACED);
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
	signal(SIGCHLD, sigchld_handler);
	return (-1);
}

/*
** Forks without waiting for a return signal from the process and add him to
** the g_pid_table.
*/

int				ft_fork_amper(char **cmd, char **env)
{
	pid_t	pid;
	int		fd[2];

	pid = fork();
	signal(SIGINT, sigfork);
	if (pid < 0)
		return (FAILFORK); // fork
	if (!pid)
	{
		resetsign();
		dup2(0,0);
		execve(cmd[0], cmd, env);
		exit(1);
	}
	dup2(fd[0], 0);
	close(fd[0]);
	setpgid(pid, 0);
	if (!waitpid(pid, &pid, WNOHANG))
	{
		add_pid(pid, cmd, ID_RUN);
		waitabit(20000000);
		return (0);
	}
	ft_putendl("here");
	return (0);
}

int				ft_fork(char **cmd, char **env)
{
	pid_t pid;

	pid = fork();
	signal(SIGINT, sigfork);
	if (pid == 0)
	{
		execve(cmd[0], cmd, env);
		exit(1);
	}
	else if (pid < 0)
		return (FAILFORK);
	return (ft_waitprocess(pid, cmd));
}
