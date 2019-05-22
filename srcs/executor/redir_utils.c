/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:33:19 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/21 17:01:23 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		print_redir(t_list *redir)
{
	t_redir *red;
	int i;

	ft_printf("===========================REDIR============================\n");
	while (redir)
	{
		red = ((t_redir *)redir->content);
		i = -1;
		print_optype(red->op_type);
		ft_printf(" dest: |");
		while (red->dest[++i])
		{
			ft_printf("%s", red->dest[i]);
			if (red->dest[i + 1])
				ft_putchar(' ');
		}
		ft_printf("|\n");
		redir = redir->next;
	}
	ft_printf("============================================================\n");
}

char	**get_curr_cmd(t_list *redir)
{
	while (redir)
	{
		if (((t_redir *)redir->content)->end_of_leaf)
			return (((t_redir *)redir->content)->dest);
		redir = redir->next;
	}
	return (NULL);
}

void 	redir_delone(void *data, size_t size)
{
	t_redir *redir;

	(void)size;
	if (data)
	{
		redir = ((t_redir *)(data));
		ft_splitdel(redir->dest);
		free(data);
	}
}

int		open_file(t_redir *redir)
{
	int		fd;
	int		err;

	fd = 0;
	if (redir->op_type == GREAT)
		fd = open(redir->dest[0], O_RDWR | O_CREAT | O_TRUNC, 0666);
	else if (redir->op_type == DBL_GREAT)
		fd = open(redir->dest[0], O_RDWR | O_APPEND | O_CREAT, 0666);
	else if (redir->op_type == LESS)
		fd = open(redir->dest[0], O_RDONLY);
	if (fd == -1)
	{
		err = check_file(redir->dest[0]);
		if (err == NO_RIGHT)
			ft_putstr_fd("42sh: Permission denied: ", 2);
		else if (err == NON_EXISTENT)
			ft_putstr_fd("42sh: No such file or directory: ", 2);
		else if (err == IS_DIRECTORY)
			ft_putstr_fd("42sh: Is a directory: ", 2);
		else
			ft_putstr_fd("42sh: Error while opening: ", 2);
		ft_putendl_fd(redir->dest[0], 2);
	}
	return (fd);
}
