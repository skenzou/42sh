/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 07:12:26 by midrissi          #+#    #+#             */
/*   Updated: 2019/07/01 08:09:44 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_exec_pipe(t_ast *root)
{
	int			fd[2];
	pid_t		pid;
	int			stdin;

	pipe(fd);
	if ((pid = fork()) == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_execute_ast(root->left);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	close(fd[1]);
	stdin = dup(STDIN_FILENO);
	dup2(fd[0], STDIN_FILENO);
	ft_execute_ast(root->right);
	close(fd[0]);
	dup2(stdin, STDIN_FILENO);
	close(stdin);
	wait(NULL);
	// ft_waitprocess(pid, (char **)root->token->content, NULL, NULL);
}
