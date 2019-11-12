/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 06:30:44 by midrissi          #+#    #+#             */
/*   Updated: 2019/11/06 19:45:26 by tlechien         ###   ########.fr       */
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
		shell_exit(MALLOC_ERR);
	g_shell->tcap->prompt = "heredoc>";
	while (42 && g_shell->inhib_mod == 1)
	{
		input = read_line(g_shell->tcap);
		if (g_shell->inhib_mod == 2 || !ft_strcmp(input, eof))
			break ;
		write(fd, input, ft_strlen2(input));
	}
	g_shell->tcap->prompt = NULL;
	(eof) ? ft_strdel(&eof) : 0;
	close(fd);
	if (g_shell->inhib_mod == 2)
		return ;
	fd = open(tmp_file, O_RDONLY);
	redir->hdoc_fd = fd;
}

void			handle_hdoc(t_list *redir)
{
	char	*str;
	int		i;

	g_shell->inhib_mod = 1;
	if (!(str = ft_strdup("/tmp/.hdoc1")))
		shell_exit(MALLOC_ERR);
	i = 0;
	while (redir)
	{
		str[10] = i + 48;
		if (((t_redir *)redir->content)->op_type == DBL_LESS)
			exec_hdoc(redir->content, str);
		if (g_shell->inhib_mod != 1)
			break ;
		i++;
		redir = redir->next;
	}
	ft_strdel(&str);
}
