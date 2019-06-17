/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 06:30:44 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/17 17:36:07 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		exec_hdoc(t_redir *redir, char *tmp_file)
{
	char	*input;
	int		fd;
	char	*eof;

	ft_expand(redir->dest);
	fd = open(tmp_file, O_RDWR | O_CREAT | O_TRUNC, 0666);
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
	fd = open(tmp_file, O_RDONLY);
	redir->hdoc_fd = fd;
}

void	handle_hdoc(t_list *redir)
{
	char *str;
	int i;

	if (!(str = ft_strdup("/tmp/.hdoc1")))
		ft_exit("malloc failed in handle_hdoc");
	i = 0;
	while (redir)
	{
		str[10] = i + 48;
		if (((t_redir *)redir->content)->op_type == DBL_LESS)
			exec_hdoc(redir->content, str);
		i++;
		redir = redir->next;
	}
	ft_strdel(&str);
}
