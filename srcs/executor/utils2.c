/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 06:15:18 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/07 06:32:58 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			is_special_char(char c)
{
	return (c == '$' || c == '\\' || c == '"' || c == '`' || c == '\n');
}

int			is_key_valid(char *key)
{
	if (!key || ft_isdigit(*key))
		return (0);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

void		close_fd(void)
{
	int		i;
	t_list	*redir;

	redir = g_shell->temp_redir;
	while (redir && ((t_redir *)redir->content)->end_of_leaf == 0)
	{
		if (((t_redir *)redir->content)->op_type != DBL_LESS)
			close(((t_redir *)redir->content)->fd);
		redir = redir->next;
	}
	g_shell->temp_redir = NULL;
	i = -1;
	while (++i < 10)
		dup2(g_shell->fd_table[i], i);
}
