/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 06:30:44 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/07 06:32:07 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		handle_hdoc(t_redir *redir)
{
	char	*input;
	int		fd;
	char	*eof;

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
