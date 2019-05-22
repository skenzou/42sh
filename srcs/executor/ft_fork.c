/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:53:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/21 16:06:36 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_fork_amper(char *path, char **command, char **env)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, sighandler);
	if (!pid)
		execve(path, command, env);
	if (pid < 0)
		return (FAILFORK); // fork
	else
		if (!waitpid(pid, &pid, WNOHANG))
			return(update_pid_table(pid, command));
	return (0);
}

int		ft_fork(char **cmd, char **env)
{
	pid_t pid;

	if (!ft_strcmp(cmd[ft_split_count(cmd) - 1], "&"))
		return(ft_fork_amper(cmd[0], cmd, env));
	pid = fork();
	signal(SIGINT, sighandler);
	if (pid == 0)
	{
		execve(cmd[0], cmd, env);
		exit(1);
	}
	else if (pid < 0)
		return (FAILFORK);
	wait(&pid);
	return (0);
}
