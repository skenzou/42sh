/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:58:59 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/28 00:49:21 by Mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static size_t			ft_count_pipes(t_ast *root)
{
	size_t nbpipes;

	nbpipes = 0;
	while (root && root->left)
	{
		root = root->left;
		nbpipes++;
	}
	return (nbpipes);
}

static int		ft_pipe_exec(char **cmd, int redir)
{
	int builtin;

	g_shell->lastsignal = ft_pre_execution(&cmd, redir, &builtin);
	if (!g_shell->lastsignal && !builtin)
		execve(cmd[0], cmd, g_shell->env_tmp);
	if (!g_shell->lastsignal && builtin)
		g_shell->lastsignal = exec_builtin(cmd, builtin, &g_shell->env_tmp);
	return (g_shell->lastsignal);
}

static void 		first_pipe(char **cmd, t_pipe **pipes, int redir)
{
	pid_t pid;

	pid = fork();
	signal(SIGINT, sigfork);
	if (pid == 0)
	{
		close(pipes[g_shell->curr_pipe]->pipe[0]);
		dup2(pipes[g_shell->curr_pipe]->pipe[1], STDOUT_FILENO);
		exit(ft_pipe_exec(cmd, redir));
	}
}

static void		pipe_cmd(char **cmd, t_pipe **pipes, size_t nbpipes, int redir)
{
	pid_t pid;

	pid = fork();
	signal(SIGINT, sigfork);
	if (pid == 0)
	{
		dup2(pipes[g_shell->curr_pipe]->pipe[0], STDIN_FILENO);
		close(pipes[g_shell->curr_pipe]->pipe[0]);
		close(pipes[g_shell->curr_pipe]->pipe[1]);
		if (g_shell->curr_pipe < nbpipes - 1)
			dup2(pipes[g_shell->curr_pipe + 1]->pipe[1], STDOUT_FILENO);
		exit(ft_pipe_exec(cmd, redir));
	}
	close(pipes[g_shell->curr_pipe]->pipe[0]);
	close(pipes[g_shell->curr_pipe]->pipe[1]);
	if (g_shell->curr_pipe == nbpipes -1)
		g_shell->lastsignal = ft_waitprocess(pid, cmd);
}

static void		parse_pipes(t_ast *root, t_pipe **pipes, size_t nbpipes)
{
	if (root->left && root->left->left)
		parse_pipes(root->left, pipes, nbpipes);
	if (root->left->token->op_type != PIPE)
	{
		first_pipe(root->left->token->content, pipes, root->left->token->redir);
		ft_post_exec();
	}
	pipe_cmd(root->right->token->content, pipes, nbpipes, root->right->token->redir);
	ft_post_exec();
	g_shell->curr_pipe++;
}

void		handle_pipe(t_ast *root)
{
	t_pipe		**pipes;
	size_t	nbpipes;
	size_t	i;

	g_shell->curr_pipe = 0;
	nbpipes = ft_count_pipes(root);
	if (!(pipes = (t_pipe **)ft_memalloc(sizeof(t_pipe *) * nbpipes)))
		ft_exit("Malloc failed");
	i = 0;
	while (i < nbpipes)
	{
		if (!(pipes[i] = (t_pipe *)ft_memalloc(sizeof(t_pipe))))
			ft_exit("Malloc failed");
		pipe(pipes[i++]->pipe);
	}
	parse_pipes(root, pipes, nbpipes);
	i = 0;
	while (i < nbpipes)
		free(pipes[i++]);
	free(pipes);
}
