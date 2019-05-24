/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:58:59 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/24 17:26:49 by midrissi         ###   ########.fr       */
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

static void 		first_pipe(char **cmd1, t_pipe **pipes, int redir)
{
	pid_t pid;

	pid = fork();
	signal(SIGINT, sigfork);
	if (pid == 0)
	{
		close(pipes[g_shell->curr_pipe]->pipe[0]);
		dup2(pipes[g_shell->curr_pipe]->pipe[1], STDOUT_FILENO);
		if (!(ft_pre_execution(&cmd1, redir)))
			execve(cmd1[0], cmd1, g_shell->env);
		exit(1);
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
		if (!(g_shell->lastsignal = ft_pre_execution(&cmd, redir)))
			execve(cmd[0], cmd, g_shell->env);
		exit(1);
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
		first_pipe(root->left->token->content, pipes, root->left->token->redir);
	pipe_cmd(root->right->token->content, pipes, nbpipes, root->right->token->redir);
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
