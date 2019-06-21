/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 06:12:37 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/21 05:26:50 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		ft_pipe_exec(char **cmd, int redir)
{
	t_builtin *builtin;

	g_shell->lastsignal = ft_pre_execution(&cmd, redir, &builtin);
	if (!g_shell->lastsignal && !builtin)
		execve(cmd[0], cmd, g_shell->env_tmp);
	if (!g_shell->lastsignal && builtin)
		g_shell->lastsignal = builtin->function(ft_split_count((const char**)cmd), cmd);
	return (g_shell->lastsignal);
}

static void		first_pipe(char **cmd, t_pipe **pipes, int redir)
{
	pid_t pid;

	pid = fork();
	(!pipes[g_shell->curr_pipe]->job) ? signal(SIGINT, sigfork): 0;
	if (pid == 0)
	{
		if (pipes[g_shell->curr_pipe]->job)
		{
			setpgid(getpid(), getpgrp());
			waitabit(0,8000000);
			resetsign();
		}
		close(pipes[g_shell->curr_pipe]->pipe[0]);
		dup2(pipes[g_shell->curr_pipe]->pipe[1], STDOUT_FILENO);
		exit(ft_pipe_exec(cmd, redir));
	}
	if (pid > 0)
		pipes[g_shell->curr_pipe]->pid = pid;
	if (pipes[g_shell->curr_pipe]->job)
	{
		if (!waitpid(pid, &pid, WNOHANG))
			add_pid(3, pid, cmd, ID_RUN);
	}
}

static void		pipe_cmd(char **cmd, t_pipe **pipes, size_t nbpipes, int redir)
{
	pid_t pid;

	pid = fork();
	(!pipes[g_shell->curr_pipe]->job) ? signal(SIGINT, sigfork): 0;
	if (pid == 0)
	{
		if (pipes[g_shell->curr_pipe]->job)
		{
			setpgid(getpid(), getpgrp());
			waitabit(0,8000000);
			resetsign();
		}
		dup2(pipes[g_shell->curr_pipe]->pipe[0], STDIN_FILENO);
		close(pipes[g_shell->curr_pipe]->pipe[0]);
		close(pipes[g_shell->curr_pipe]->pipe[1]);
		if (g_shell->curr_pipe < nbpipes - 1)
			dup2(pipes[g_shell->curr_pipe + 1]->pipe[1], STDOUT_FILENO);
		exit(ft_pipe_exec(cmd, redir));
	}
	// pipes[g_shell->curr_pipe]->pid = pid;
	close(pipes[g_shell->curr_pipe]->pipe[0]);
	close(pipes[g_shell->curr_pipe]->pipe[1]);
	if (pipes[g_shell->curr_pipe]->job)
	{
		if (!waitpid(pid, &pid, WNOHANG))
			add_amperpipe(pipes[0]->pid, pid, full_cmd(cmd), ID_RUN);
	}
	else if (g_shell->curr_pipe == nbpipes - 1)
		g_shell->lastsignal = ft_waitprocess(pid, cmd);
}

void			parse_pipes(t_ast *root, t_pipe **pipes, size_t nbpipes)
{
	if (root->left && root->left->left)
		parse_pipes(root->left, pipes, nbpipes);
	if (root->left->token->op_type != PIPE)
	{
		first_pipe(root->left->token->content, pipes, root->left->token->redir);
		ft_post_exec(root->left);
	}
	pipe_cmd(root->right->token->content,
									pipes, nbpipes, root->right->token->redir);
	ft_post_exec(root->right);
	g_shell->curr_pipe++;
}
