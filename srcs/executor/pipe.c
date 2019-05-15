/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:58:59 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/14 23:59:07 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void 		pipe_cmds(char **cmd1, char **cmd2, char **env)
{
	int fildes[2];
	pid_t pid;

	pipe(fildes);
	pid = fork();
	signal(SIGINT, sigfork);
	if (pid == 0)
	{
		close(fildes[0]);
		dup2(fildes[1], STDOUT_FILENO);
		dup2(fildes[1], STDERR_FILENO);
		execve(cmd1[0], cmd1, env);
		exit(1);
	}
	pid = fork();
	signal(SIGINT, sigfork);
	if (pid == 0)
	{
		close(fildes[1]);
		dup2(fildes[0], STDIN_FILENO);
		execve(cmd2[0], cmd2, env);
		exit(1);
	}
	close(fildes[0]);
	close(fildes[1]);
	wait(&pid);
	wait(&pid);
	ft_splitdel(cmd1);
	ft_splitdel(cmd2);
}
