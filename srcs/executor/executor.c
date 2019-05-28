/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:15:41 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/28 20:28:39 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		exec_builtin(char **builtin, int id, char ***env)
{
	int	ac;
	int	err_id;

	ac = ft_split_count(builtin);
	err_id = 0;
	if (id == ECHO_BUILTIN)
		err_id = echo_builtin(ac, builtin);
	if (id == CD_BUILTIN)
		err_id = cd_builtin(ac, builtin, *env);
	if (id == ENV_BUILTIN && ac == 1)
		print_split(*env);
	if (id == SETENV_BUILTIN)
		err_id = setenv_builtin(ac, builtin, env);
	if (id == UNSETENV_BUILTIN)
		err_id = unsetenv_builtin(ac, builtin, env);
	if (id == EXIT_BUILTIN)
		exit_builtin();
	if (id == SET_BUILTIN)
		set_builtin();
	if (id == EXPORT_BUILTIN)
		export_builtin(ac, builtin);
	if (id == UNSET_BUILTIN)
		unset_builtin(ac, builtin);
	if (id == JOBS_BUILTIN)
		jobs_builtin(builtin);
	if (err_id)
		err_handler(err_id, builtin[0]);
	return (err_id);
}

void			ft_post_exec()
{
	char *str;

	if (!(str = ft_itoa(g_shell->lastsignal)))
		ft_exit("Maloc failed in ft_post_exec");
	ft_setenv("?", str, &g_shell->intern);
	if (g_shell->env != g_shell->env_tmp)
		ft_splitdel(g_shell->env_tmp);
	if (g_shell->intern != g_shell->intern_tmp)
		ft_splitdel(g_shell->intern_tmp);
	g_shell->env_tmp = g_shell->env;
	g_shell->intern_tmp = g_shell->intern;
}

static void		ft_execute(char **args, int redir, int background)
{
	int builtin;

	g_shell->lastsignal = ft_pre_execution(&args, redir, &builtin);
	if (!g_shell->lastsignal && !builtin)
	{
		if (!background)
			g_shell->lastsignal = ft_fork(args, g_shell->env_tmp);
		else
			g_shell->lastsignal = ft_fork_amper(args, g_shell->env_tmp);
	}
	if (!g_shell->lastsignal && builtin)
		g_shell->lastsignal = exec_builtin(args, builtin, &g_shell->env_tmp);
	if (redir)
		restore_fd();
	ft_post_exec();
}

void	ft_execute_ast(t_ast *root)
{
	if (!root)
		return ;
	if (root->token->op_type == PIPE)
	{
		handle_pipe(root);
		return ;
	}
	if (root->token->op_type == AND && root->left
							&& root->left->token->op_type == TOKEN_WORD)
		root->left->job = 1;
	if (root->token->op_type == AND && root->left && root->left->right
		&& root->left->right->token->op_type == TOKEN_WORD)
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
