/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:15:41 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/08 01:01:15 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void 		redirect(char **cmd, char *path, char **env, char simple)
{
	pid_t pid;
	int fd;

	if (simple) // redirection simple '>'
		fd = open(path, O_RDWR | O_APPEND | O_CREAT | O_TRUNC, 0666); // ecraser un le contenu de fichier
	else		// double redirection '>>'
		fd = open(path, O_RDWR | O_APPEND | O_CREAT, 0666); // ecrire fin de fichier
	pid = fork();
	signal(SIGINT, sighandler);
	if (pid == 0)
	{
		dup2(fd, 1); // recupere stdout
		dup2(fd, 2); // recupere stderr
		execve(cmd[0], cmd, env);
	}
	wait(&pid);
}

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
		dup2(fildes[1], STDOUT_FILENO); /* recupere stdout de ma 1ere commande */
		dup2(fildes[1], STDERR_FILENO); /* recupere stderr de ma 2eme commande */
		execve(cmd1[0], cmd1, env);
		exit(1);
	}
	pid = fork();
	signal(SIGINT, sigfork);
	if (pid == 0)
	{
		close(fildes[1]);
		dup2(fildes[0], STDIN_FILENO); /* recupere la sortie de pipe dans stdin de ma 2 eme commande */
		execve(cmd2[0], cmd2, env);
		exit(1);
	}
	close(fildes[0]);
	close(fildes[1]);
	wait(&pid);
	wait(&pid);
}

void search_pipe(t_ast *root,char *str, char **env)
{
	if (root != NULL)
	{
		search_pipe(root->left,ft_strjoin(str , " - > left"),env);
		if (root->token->op_type == PIPE)
			pipe_cmds(ft_strsplit(root->left->token->content,' '),
					ft_strsplit(root->right->token->content,' '),env);
		search_pipe(root->right,ft_strjoin(str ,"- > right"), env);
	}
}

void ft_compiler(t_ast *root, char **env)
{
	search_pipe(root,"root",env);
}

// void 	executor(char **argv, char **env)
// {
//
// }
