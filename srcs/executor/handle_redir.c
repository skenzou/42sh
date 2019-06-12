/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:28:47 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/07 06:31:52 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_list	*next_cmd(t_list *redir)
{
	while (redir && ((t_redir *)redir->content)->end_of_leaf == 0)
		redir = redir->next;
	if (redir)
		redir = redir->next;
	return (redir);
}

static int		handle_redir_and(t_redir *redir)
{
	int fd;

	fd = -1;
	if (ft_strequ(redir->dest[0], "-"))
	{
		close(redir->fd);
		return (-42);
	}
	else if (ft_isonly_digit(redir->dest[0]))
	{
		fd = ft_atoi(redir->dest[0]);
		if (fd < 0 || fd > 2)
		{
			redir_errors(BAD_FD, NULL, fd);
			fd = -1;
		}
	}
	else if (redir->op_type == LESS_AND)
		redir_errors(AMBIGOUS_REDIRECT, redir->dest[0], 0);
	else if (redir->op_type == GREAT_AND)
		fd = open_file(redir);
	return (fd);
}

static int		restore_stdout_and_exec_hdoc(t_redir *redir)
{
	int		tempfd;
	int		fd;

	tempfd = dup(STDOUT_FILENO);
	dup2(g_shell->fd_table[1], STDOUT_FILENO);
	fd = handle_hdoc(redir);
	dup2(tempfd, STDOUT_FILENO);
	return (fd);
}

static int		exec_redir(t_redir *redir)
{
	int		fd;

	ft_expand(redir->dest);
	if (redir->op_type == DBL_LESS)
		fd = restore_stdout_and_exec_hdoc(redir);
	else if (redir->op_type == GREAT_AND || redir->op_type == LESS_AND)
	{
		if ((fd = handle_redir_and(redir)) == -42)
			return (0);
	}
	else
		fd = open_file(redir);
	if (fd != -1)
		dup2(fd, redir->fd);
	else
		return (1);
	if (redir->op_type == GREAT_AND)
		dup2(fd, STDERR_FILENO);
	return (0);
}

char			**handle_redir(void)
{
	t_list *redir;

	redir = g_shell->redir;
	while (redir && ((t_redir *)redir->content)->end_of_leaf == 0)
	{
		if (exec_redir(((t_redir *)redir->content)))
		{
			g_shell->redir = next_cmd(redir);
			return (NULL);
		}
		redir = redir->next;
	}
	g_shell->temp_redir = g_shell->redir;
	if (redir)
	{
		g_shell->redir = redir->next;
		ft_expand(((t_redir *)redir->content)->dest);
		return (((t_redir *)redir->content)->dest);
	}
	g_shell->redir = NULL;
	return (NULL);
}
