/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:53:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/10/08 17:48:49 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Checks the status of a processus.
** Returns exit value for regular exits,
** Returns -1 for anormal exits and update_pid_table.
*/

int				ft_waitprocess(pid_t pid, char **cmd, char *handler, char *stat)
{
	int			status;
	t_child		*node;

	signal(SIGTSTP, sigtstp_handler);
	waitpid(pid, &status, WUNTRACED);
	tcsetpgrp(0, getpid());
	if (WIFEXITED(status))
		return ((WEXITSTATUS(status)));
	else if (WIFSIGNALED(status))
	{
		s_get_values(WTERMSIG(status), NULL, &handler, &stat);
		if (!handler)
			ft_printf(ANSI_RED"42sh : %s: %d: unknown error code\n"ANSI_RESET,
			cmd[0], WTERMSIG(status));
		else if (status != SIGINT && status != SIGQUIT)
			ft_printf(ANSI_RED"42sh : %s: %s: %s\n"ANSI_RESET,
			cmd[0], handler, stat);
	}
	else if (WSTOPSIG(status))
	{
		add_pid(0, pid, cmd, ID_SUSP);
		!search_pid(&node, NULL, pid) && display_pid_status(node, 0);
	}
	signal(SIGTSTP, sigtstp_dflhandler);
	return (-1);
}

/*
** Checks the status of a processus.
** Returns exit value for regular exits,
** Returns -1 for anormal exits and
** if pipe process is stopped, adds it to pid_table.
*/

int		waitpipe(t_pipe **begin, t_pipe *elem)
{
	int			status;
	char*		handler;
	char*		stat;
	t_child		*node;

	signal(SIGTSTP, sigtstp_handler);
	waitpid(elem->pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		return ((WEXITSTATUS(status)));
	else if (WIFSIGNALED(status))
	{
		s_get_values(WTERMSIG(status), NULL, &handler, &stat);
		if (!handler)
			ft_printf(ANSI_RED"42sh : %s: %d: unknown error code\n"ANSI_RESET,
			elem->cmd[0], WTERMSIG(status));
		else if (status != SIGINT && status != SIGQUIT && status != SIGPIPE)
			ft_printf(ANSI_RED"42sh : %s: %s: %s\n"ANSI_RESET,
			elem->cmd[0], handler, stat);
	}
	else if (WSTOPSIG(status) && search_pid(&node, NULL, (*begin)->pid))
	{
		elem = *begin;
		while (elem)
		{
			if (elem == *begin)
				add_pid(3, elem->pid, elem->cmd, ID_SUSP);
			else
				add_amperpipe((*begin)->pid, elem->pid, full_cmd(elem->cmd), ID_SUSP);
			elem = elem->next;
		}
	}
	signal(SIGTSTP, sigtstp_dflhandler);
	return (-1);
}

/*
** Forks without waiting for a return signal from the process and adds it to
** the g_pid_table.
*/

int				ft_fork_amper(char **cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		shell_exit(FORK_ERR);
	if (!pid)
	{
		resetsign();
		setpgid(getpid(), getpid());
		execve(cmd[0], cmd, env);
		exit(1);
	}
	if (!waitpid(pid, &pid, WNOHANG))
		return (add_pid(0, pid, cmd, ID_RUN));
	return (0);
}

/*
** Forks builtin without waiting for a return signal from the process and
** adds it to the g_pid_table.
*/

int				ft_fork_builtin(t_builtin *builtin, int ac, char **cmd)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
		shell_exit(FORK_ERR);
	if (!pid)
	{
		resetsign();
		setpgid(getpid(), getpgrp());
		exit(builtin->function(ac, cmd));
	}
	if (!waitpid(pid, &pid, WNOHANG))
		return (add_pid(0, pid, cmd, ID_RUN));
	return (0);
}

/*
** Regular bin fork-exec with foreground waiting.
*/

int				ft_fork(char **cmd, char **env)
{
	pid_t pid;

	pid = fork();
	signal(SIGINT, sigfork);
	if (pid == 0)
	{
		setpgid(getpid(), getpgrp());
		tcsetpgrp(0, getpgrp());
		execve(cmd[0], cmd, env);
		exit(1);
	}
	else if (pid < 0)
		shell_exit(FORK_ERR);
	return (ft_waitprocess(pid, cmd, NULL, NULL));
}
