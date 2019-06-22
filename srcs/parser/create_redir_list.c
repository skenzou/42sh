/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 16:57:34 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/22 17:45:49 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			**get_cmd(t_token *curr, size_t *cmd_size, char *to_free,
																	char **cmd)
{
	if (!cmd)
	{
		cmd = curr->content;
		*cmd_size = curr->size;
	}
	else
	{
		cmd = join_2tab(cmd, curr->content, *cmd_size, curr->size);
		*cmd_size += curr->size;
		*to_free = 1;
	}
	return (cmd);
}

static int			check_redir(t_token *curr, t_list *lexer)
{
	t_token *next;

	if (curr->type == TOKEN_REDIR)
	{
		next = (t_token *)lexer->next->content;
		create_redir(curr->content[0], next->content, next->size,
																curr->op_type);
		return (0);
	}
	else
		return (1);
}

static t_list		*reset_vars(char ***cmd, t_list **prev, char *to_free,
																t_list *lexer)
{
	*cmd = NULL;
	*prev = NULL;
	*to_free = 0;
	return (get_next_redir(lexer));
}

void				create_redir_list(t_list *lexer)
{
	t_token	*curr;
	char	**cmd;
	t_list	*prev;
	size_t	cmd_size;
	char	to_free;

	lexer = reset_vars(&cmd, &prev, &to_free, lexer);
	while (lexer)
	{
		curr = (t_token *)lexer->content;
		if (curr->type == TOKEN_WORD && (!prev || (prev
			&& ((t_token *)prev->content)->type != TOKEN_REDIR)))
			cmd = get_cmd(curr, &cmd_size, &to_free, cmd);
		if (check_redir(curr, lexer) && (curr->type == TOKEN_CTL_OPERATOR
			|| (curr->type != TOKEN_CTL_OPERATOR && !lexer->next)))
		{
			create_redir(NULL, cmd, cmd_size, OTHER_OP);
			if (to_free)
				ft_splitdel(cmd);
			lexer = reset_vars(&cmd, &prev, &to_free, lexer);
			continue ;
		}
		prev = lexer;
		lexer = lexer->next;
	}
}
