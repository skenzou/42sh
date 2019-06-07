/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:53:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/07 06:03:19 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Displays special signal caught while listening to a child.
*/

static void		display_signal(int status, char *cmd)
{
	if (status == SIGALRM)
		ft_printf(ANSI_RED"[TIMEOUT] %s\n"ANSI_RESET, cmd);
	else if (status == SIGSEGV)
		ft_printf(ANSI_RED"[SEGV] %s\n"ANSI_RESET, cmd);
	else if (status == SIGBUS)
		ft_printf(ANSI_RED"[BUSE] %d\n"ANSI_RESET, cmd);
	else if (status == SIGABRT)
		ft_printf(ANSI_RED"[ABRT] %d\n"ANSI_RESET, cmd);
	else if (status == SIGFPE)
		ft_printf(ANSI_RED"[FPE] %d\n"ANSI_RESET, cmd);
	else
		ft_printf(ANSI_RED"[ERR] %d ended unexpectedly\n"ANSI_RESET, cmd);
}

/*
** Checks the status of a processus.
** Returns exit value for regular exits,
** Returns -1 for anormal exits and update_pid_table.
*/

int				ft_waitprocess(pid_t pid, char **cmd)
{
	int			status;
	t_child		*node;

	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		return ((WEXITSTATUS(status)));
	else if (WIFSIGNALED(status))
		kill(pid, SIGTERM); // proteccc ? err = -1
	else if (WSTOPSIG(status))
	{
		add_pid(pid, cmd, S_SUSP);
		search_pid(&node, NULL, pid);
		display_pid_status(node, 0);
		kill(pid, SIGINT); // idem ?
	}
	display_signal(status, cmd[0]);
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
	signal(SIGINT, sigfork);
	if (!pid)
		execve(cmd[0], cmd, env);
	if (pid < 0)
		return (FAILFORK); // fork
	if (!waitpid(pid, &pid, WNOHANG))
		return (add_pid(pid, cmd, S_RUN));
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
