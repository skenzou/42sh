/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:28:47 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/15 03:37:25 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int handle_hdoc(t_redir *redir)
{
	char *input;
	int fd;
	char *eof;

	fd = open(HERE_DOC_TMP, O_RDWR | O_CREAT | O_TRUNC, 0666);
	input = NULL;
	if (!(eof = ft_strjoin(redir->dest[0], "\n")))
		ft_exit("Malloc failed in handle_hdoc");
	g_shell->tcap->prompt = "heredoc>";
	while (42)
	{
		input = read_line(g_shell->tcap);
		if (!ft_strcmp(input, eof))
			break ;
		write(fd, input, ft_strlen(input));
	}
	g_shell->tcap->prompt = NULL;
	free(eof);
	close(fd);
	fd = open(HERE_DOC_TMP, O_RDONLY);
	return (fd);
}

static t_list *next_cmd(t_list *redir)
{
	t_list *temp;

	while (redir && ((t_redir *)redir->content)->end_of_leaf == 0)
	{
		temp = redir;
		redir = redir->next;
		ft_lstdelone(&temp, redir_delone);
	}
	if (redir)
	{
		temp = redir;
		redir = redir->next;
		ft_lstdelone(&temp, redir_delone);
	}
	return (redir);
}

void		handle_redir()
{
	t_list *temp;
	t_list *redir;
	int		fd;
	int stdout;
	int stdin;
	char **cmd;
	int tempfd;
	int i;
	t_redir *red;

	stdout = dup(STDOUT_FILENO);
	stdin = dup(STDIN_FILENO);
	redir = g_shell->redir;
	while (redir && ((t_redir *)redir->content)->end_of_leaf == 0)
	{
		red = ((t_redir *)redir->content);
		cmd = get_curr_cmd(redir);
		i = -1;
		while (red->dest[++i])
			remove_quote(&(red->dest[i]));
		if (red->op_type == DBL_LESS)
		{
			tempfd = dup(STDOUT_FILENO);
			dup2(stdout, STDOUT_FILENO);
			fd = handle_hdoc(redir->content);
			dup2(tempfd, STDOUT_FILENO);
		}
		else
		{
			fd = open_file(redir->content);
			red->fd = fd;
		}
		if (fd != -1)
		{
			if (red->op_type == LESS
				|| red->op_type == DBL_LESS)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
		}
		else
		{
			g_shell->redir = next_cmd(redir);
			dup2(stdout, STDOUT_FILENO);
			dup2(stdin, STDIN_FILENO);
			return ;
		}
		temp = redir;
		redir = redir->next;
		ft_lstdelone(&temp, redir_delone);
	}
	ft_execute(cmd);
	dup2(stdout, STDOUT_FILENO);
	dup2(stdin, STDIN_FILENO);
	if (redir)
	{
		g_shell->redir = redir->next;
		ft_lstdelone(&redir, redir_delone);
	}
	else
		g_shell->redir = redir;
}
