/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:28:47 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/21 17:54:33 by midrissi         ###   ########.fr       */
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

static int		handle_redir_and(t_redir *redir)
{
	int fd;

	fd = -1;
	if (ft_isonly_digit(redir->dest[0]))
	{
		fd = ft_atoi(redir->dest[0]);
		if (fd < 0 || fd > 2)
		{
			ft_putstr_fd("42sh: ", 2);
			ft_putnbr_fd(fd, 2);
			ft_putendl_fd(": bad file descriptor", 2);
			fd = -1;
		}
	}
	else
	{
		ft_putstr_fd("42sh: ", 2);
		ft_putstr_fd(redir->dest[0], 2);
		ft_putendl_fd(": ambigous redirect", 2);
	}
	return (fd);
}

static void restore_fd()
{
	int i;

	i = -1;
	while(++i < 10)
		dup2(g_shell->fd_table[i], i);
}

void			handle_redir()
{
	t_list *temp;
	t_list *redir;
	int		fd;
	char **cmd;
	int tempfd;
	t_redir *red;

	redir = g_shell->redir;
	while (redir && ((t_redir *)redir->content)->end_of_leaf == 0)
	{
		red = ((t_redir *)redir->content);
		cmd = get_curr_cmd(redir);
		ft_expand(red->dest);
		if (red->op_type == DBL_LESS)
		{
			tempfd = dup(STDOUT_FILENO);
			dup2(g_shell->fd_table[1], STDOUT_FILENO);
			fd = handle_hdoc(redir->content);
			dup2(tempfd, STDOUT_FILENO);
		}
		else if (red->op_type == GREAT_AND || red->op_type == LESS_AND)
			fd = handle_redir_and(red);
		else
			fd = open_file(redir->content);
		if (fd != -1)
			dup2(fd, red->fd);
		else
		{
			g_shell->redir = next_cmd(redir);
			restore_fd();
			return ;
		}
		if (red->op_type == GREAT_AND)
			dup2(fd, STDERR_FILENO);
		temp = redir;
		redir = redir->next;
		ft_lstdelone(&temp, redir_delone);
	}
	ft_execute(cmd);
	restore_fd();
	if (redir)
	{
		g_shell->redir = redir->next;
		ft_lstdelone(&redir, redir_delone);
	}
	else
		g_shell->redir = redir;
}
