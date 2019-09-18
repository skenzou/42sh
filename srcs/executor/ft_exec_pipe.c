/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 07:12:26 by midrissi          #+#    #+#             */
/*   Updated: 2019/09/18 05:20:54 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void push_pipe(t_ast *root, t_pipe **begin)
{
	t_pipe *new;
	t_pipe *pipe;

	pipe = *begin;
	if (!(new = (t_pipe *)ft_memalloc(sizeof(t_pipe))))
		shell_exit(MALLOC_ERR);
	new->cmd = root->token->content;
	if (pipe)
	{
		while (pipe->next)
			pipe = pipe->next;
		pipe->next = new;
	}
	else
		*begin = new;
}

void parse_pipe (t_ast *root, t_ast *origin, t_pipe **pipe)
{
	if (root->left)
		parse_pipe(root->left, origin, pipe);
	if (root->right)
		parse_pipe(root->right, origin, pipe);
	if (root == origin)
		push_pipe(root, pipe);
	else if (root->token->type == TOKEN_WORD)
		push_pipe(root, pipe);
}

void	launch_process(t_pipe *pipe, int ext[2])
{
	pid_t pid;

	pid = getpid();
	//setpgid(pid, pid);
	tcsetpgrp(0, pid);
	resetsign();
	if (!pipe->next)
	{
		close (pipe->fd[0]);
		dup2(pipe->fd[1], 1);
	}
    dup2 (ext[0], STDIN_FILENO);
    close (ext[0]);
    dup2 (ext[1], STDOUT_FILENO);
    close (ext[1]);
	execvp(pipe->cmd[0], pipe->cmd);
	exit(1);
}
int	wait_ret(t_pipe *elem)
{
	int		status;
	char	buffer[256]; //any idea of the value here?

	if (elem->next)
	{
		wait_ret(elem->next);
		waitpid(elem->pid, &status, WUNTRACED);
		if (!WIFEXITED(status) && status == 9)
			read(0, &buffer, 255);
	}
	return (0);
}

int	free_pipe(t_pipe *elem)
{
	t_pipe 	*tmp;

	while (elem)
	{
		tmp = elem;
		elem = elem->next;
		free(tmp);
	}
	return (0);
}

int launch_pipe (t_pipe **begin, t_pipe *elem, int is_bg)
{
	int		pid;
	int		ext[2];
	int		status;

	ext[0] = g_shell->fd_table[0]; //shell in.
	while (elem)
	{
		if (elem->next)
		{
			pipe(elem->fd);
			ext[1] = elem->fd[1];
		}
		else
			ext[1] = g_shell->fd_table[1];
		if ((pid = fork()) == 0)
			launch_process(elem, ext);
		else if (pid < 0)
			shell_exit(FORK_ERR);
		else
		{
			elem->pid = pid;
			setpgid(pid, getpgrp());
			(ext[0] != g_shell->fd_table[0]) ? close(ext[0]): 0; // shell in
			(ext[1] != g_shell->fd_table[1]) ? close(ext[1]): 0; // shell out
			ext[0] = elem->fd[0];
			//close(elem->fd[1]); //|necessary ?
			//close(elem->fd[0]); //|
			if (is_bg && elem == *begin && !waitpid(pid, &pid, WNOHANG))
				add_pid(3, pid, elem->cmd, ID_RUN);
			else if (is_bg && elem != *begin && !waitpid(pid, &pid, WNOHANG))
				add_amperpipe((*begin)->pid, pid, full_cmd(elem->cmd), ID_RUN);
		}
		if (elem->next)
			elem = elem->next;
		else
			break;
	}
	waitpid(elem->pid, &status, WUNTRACED);
	elem = *begin;
	while (elem && elem->next && !is_bg)
	{
		kill (elem->pid, SIGKILL);
		elem = elem->next;
	}
	(begin && !is_bg) ? wait_ret(*begin) : 0;
	(begin && !is_bg) ? free_pipe(*begin) : 0;
	tcsetpgrp(0, getpgrp());
	resetsign();
	dup2(g_shell->fd_table[0], STDIN_FILENO);
	dup2(g_shell->fd_table[1], STDOUT_FILENO);
	return (0);
}
