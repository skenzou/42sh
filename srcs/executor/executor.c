/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:15:41 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/24 16:11:04 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		ft_execute(char **args, int redir)
{
	if (!ft_pre_execution(&args, redir))
		ft_fork(args, g_shell->env);
	if (redir)
		restore_fd();
}

void	ft_execute_ast(t_ast *root, char **env)
{
	if (!root)
		return ;
	if (root->token->op_type == PIPE)
	{
		handle_pipe(root);
		return ;
	}
	if (root->left)
		ft_execute_ast(root->left, env);
	if (root->right)
		ft_execute_ast(root->right, env);
	if (root->token->redir)
		ft_execute(root->token->content, 1);
	else if (root->token->type == TOKEN_WORD)
		ft_execute(root->token->content, 0);
}
