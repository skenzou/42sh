/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 07:12:26 by midrissi          #+#    #+#             */
/*   Updated: 2019/07/11 07:18:37 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*static int		ft_pipe_exec(char **cmd, int redir)
{
	t_builtin *builtin;

	g_shell->lastsignal = ft_pre_execution(&cmd, redir, &builtin);
	if (!g_shell->lastsignal && !builtin)
		execve(cmd[0], cmd, g_shell->env_tmp);
	if (!g_shell->lastsignal && builtin)
		g_shell->lastsignal = builtin->function(
										ft_split_count((const char**)cmd), cmd);
	return (g_shell->lastsignal);
}*/

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
    dup2 (ext[0], STDIN_FILENO);
    close (ext[0]);
    dup2 (ext[1], STDOUT_FILENO);
    close (ext[1]);
	execvp(pipe->cmd[0], pipe->cmd);
	exit(1);
}

int launch_pipe (t_pipe **begin, t_pipe *elem)
{
	int		pid;
	int		ext[2];
	dprintf(debug(), "shell_fds: %d %d \n", g_shell->fd_table[0], g_shell->fd_table[1]);
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
		}
		elem = elem->next;
	}
	elem = *begin;
	while (elem)
	{
		wait(NULL);
		elem = elem->next;
		close(STDIN_FILENO);
	}
	dprintf(debug(), "here\n");
	//tcsetpgrp(0, 0);
	dup2(g_shell->fd_table[0], STDIN_FILENO);
	dup2(g_shell->fd_table[1], STDOUT_FILENO);
	return (0);
}
