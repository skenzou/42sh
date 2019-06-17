/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:58:59 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/17 19:52:24 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static size_t	ft_count_pipes(t_ast *root)
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

void			handle_pipe(t_ast *root, char job)
{
	t_pipe		**pipes;
	size_t		nbpipes;
	size_t		i;

	g_shell->curr_pipe = 0;
	nbpipes = ft_count_pipes(root);
	if (!(pipes = (t_pipe **)ft_memalloc(sizeof(t_pipe *) * nbpipes)))
		ft_exit("Malloc failed");
	i = 0;
	while (i < nbpipes)
	{
		if (!(pipes[i] = (t_pipe *)ft_memalloc(sizeof(t_pipe))))
			ft_exit("Malloc failed");
		pipes[i]->job = job;
		pipe(pipes[i++]->pipe);
	}
	parse_pipes(root, pipes, nbpipes);
	i = 0;
	while (i < nbpipes)
		free(pipes[i++]);
	free(pipes);
}
