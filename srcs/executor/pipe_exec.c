/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 17:31:04 by tlechien          #+#    #+#             */
/*   Updated: 2019/11/08 11:43:46 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Execve() or calls builtin depending on cmd.
*/

static int		pipe_exec(char **cmd, int redir)
{
	t_builtin *builtin;

	g_shell->lastsignal = ft_pre_execution(&cmd, redir, &builtin);
	if (!g_shell->lastsignal && !builtin)
		execve(cmd[0], cmd, g_shell->env_tmp);
	if (!g_shell->lastsignal && builtin)
		g_shell->lastsignal = builtin->function(
										ft_split_count((const char**)cmd), cmd);
	return (g_shell->lastsignal);
}

/*
** Launches an unitary elem of the pipe and set its fds.
*/

static	void	launch_process(t_pipe *beg, t_pipe *prev, t_pipe *pipe, int bg)
{
	if (bg)
	{
		resetsign();
		setpgid(pipe->pid, beg->pid);
	}
	else
		setpgid(getpid(), getpgrp());
	if (pipe->next)
	{
		dup2(pipe->fd[1], STDOUT_FILENO);
		close(pipe->fd[0]);
	}
	if (prev)
	{
		dup2(prev->fd[0], STDIN_FILENO);
		close(prev->fd[1]);
	}
	pipe_exec(pipe->cmd, pipe->redir);
	exit(1);
}

/*
** Closes parent side of the pipe and
** Adds child to g_pid_table if it's a bg job.
*/

static	void	parent_end(t_pipe **begin, t_pipe *elem, int is_bg)
{
	elem = *begin;
	while (elem)
	{
		close(elem->fd[0]);
		if (is_bg)
		{
			(elem == *begin) ? add_pid(3, elem->pid, elem->cmd, ID_RUN) :
			add_amperpipe((*begin)->pid, elem->pid,
						full_cmd(elem->cmd), ID_RUN);
			g_shell->dprompt = 0;
			g_shell->chld_check = 1;
		}
		elem = elem->next;
	}
}

/*
** Checks return statuses of each elem and
** adds them to g_pid_table if interrupted and
** frees the pipe list.
*/

static	void	end_pipe(t_pipe **begin, t_pipe *elem, int is_bg)
{
	t_pipe *prev;

	prev = NULL;
	while (!is_bg && elem)
	{
		//dprintf(debug(), "waiting %d\n", elem->pid);
		g_shell->lastsignal = waitpipe(begin, elem);
		prev = elem;
		elem = elem->next;
	}
	elem = *begin;
	while (elem)
	{
		prev = elem;
		elem = elem->next;
		free(prev);
	}
	setpgid(0, 0);
	tcsetpgrp(0, 0);
}

/*
** Launches each elem of a pipe and links them together.
*/

int				launch_pipe(t_pipe **begin, t_pipe *elem, int is_bg)
{
	t_pipe	*prev;

	prev = NULL;
	elem = *begin;
	while (elem)
	{
		pipe(elem->fd);
		if (!(elem->pid = fork()))
			launch_process(*begin, prev, elem, is_bg);
		else if (elem->pid < 0)
			shell_exit(FORK_ERR);
		close(elem->fd[1]);
		prev = elem;
		elem = elem->next;
	}
	parent_end(begin, *begin, is_bg);
	end_pipe(begin, *begin, is_bg);
	return (0);
}
