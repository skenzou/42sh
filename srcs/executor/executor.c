/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:15:41 by midrissi          #+#    #+#             */
/*   Updated: 2019/09/18 05:15:36 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			ft_post_exec(t_ast *root)
{
	char *str;

	if (g_shell->env != g_shell->env_tmp)
		ft_splitdel(g_shell->env_tmp);
	if (!(str = ft_itoa(g_shell->lastsignal)))
		ft_exit("Maloc failed in ft_post_exec");
	ft_setenv("?", str, &g_shell->intern);
	ft_strdel(&str);
	g_shell->env_tmp = g_shell->env;
	if (root && root->token->redir)
		go_to_next_cmd(g_shell->redir);
}

static void		handle_builtin(t_builtin *builtin, char **args)
{
	char	*path;

	(path = get_key_value("PATH", g_shell->env)) ||
	(path = get_key_value("PATH", g_shell->intern));
	g_shell->lastsignal = builtin->function(ft_split_count((const char**)args),
																		args);
	compare_paths(path);
}

static void		ft_execute(char **args, int redir, int background)
{
	t_builtin	*builtin;

	g_shell->lastsignal = ft_pre_execution(&args, redir, &builtin);
	if (!g_shell->lastsignal && !builtin && args && args[0])
	{
		if (!background)
			g_shell->lastsignal = ft_fork(args, g_shell->env_tmp);
		else
			g_shell->lastsignal = ft_fork_amper(args, g_shell->env_tmp);
	}
	if (!g_shell->lastsignal && builtin && !background)
		handle_builtin(builtin, args);
	else if (!g_shell->lastsignal && builtin)
		g_shell->lastsignal = ft_fork_builtin(builtin,
									ft_split_count((const char**)args), args);
	if (redir)
		close_fd();
	ft_post_exec(NULL);
}

void			ft_execute_ast(t_ast *root)
{
	t_pipe	*pipe;

	if (!root)
		return ;
	if (root->token->op_type == PIPE)
	{
		pipe = NULL;
		parse_pipe(root, root->right, &pipe);
		launch_pipe(&pipe, pipe, root->job);
		return ;
	}
	if (root->token->op_type == AND && root->left &&
		(root->left->token->op_type == TOKEN_WORD ||
										root->left->token->op_type == PIPE))
		root->left->job = 1;
	if (root->token->op_type == AND && root->left && root->left->right
		&& (root->left->right->token->op_type == TOKEN_WORD
	|| root->left->right->token->op_type == PIPE))
		root->left->right->job = 1;
	if (root->left)
		ft_execute_ast(root->left);
	if (root->left && root->token->op_type == DBL_AND && g_shell->lastsignal)
		return ;
	if (root->left && root->token->op_type == DBL_PIPE && !g_shell->lastsignal)
		return ;
	if (root->right)
		ft_execute_ast(root->right);
	if (root->token->type == TOKEN_WORD)
		ft_execute(root->token->content, root->token->redir, root->job);
}
