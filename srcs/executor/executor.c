/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:15:41 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/21 15:33:10 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		get_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (ECHO_BUILTIN);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (CD_BUILTIN);
	else if (ft_strcmp(cmd, "setenv") == 0)
		return (SETENV_BUILTIN);
	else if (ft_strcmp(cmd, "unsetenv") == 0)
		return (UNSETENV_BUILTIN);
	else if (ft_strcmp(cmd, "env") == 0)
		return (ENV_BUILTIN);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (EXIT_BUILTIN);
	return (0);
}

static void		exec_builtin(char **builtin, int id, char ***env)
{
	int	ac;
	int	err_id;

	ac = ft_split_count(builtin);
	err_id = 0;
	if (id == ECHO_BUILTIN)
		err_id = echo_builtin(ac, builtin);
	if (id == CD_BUILTIN)
		err_id = cd_builtin(ac, builtin, env);
	if (id == ENV_BUILTIN && ac == 1)
		print_env(*env);
	if (id == SETENV_BUILTIN)
		err_id = setenv_builtin(ac, builtin, env);
	if (id == UNSETENV_BUILTIN)
		err_id = unsetenv_builtin(ac, builtin, env);
	if (id == EXIT_BUILTIN)
		exit_builtin();
	if (err_id != 0)
		err_handler(err_id, builtin[0]);
}

static int		exec_binpath(char **bin, char **env)
{
	struct stat	buff;

	if (stat(bin[0], &buff) == -1)
		return (NON_EXISTENT);
	if (S_ISREG(buff.st_mode) == 1 && !access(bin[0], X_OK))
		return (ft_fork(bin, env));
	else if (access(bin[0], X_OK) != 0)
		return (NO_RIGHT);
	else if (S_ISDIR(buff.st_mode) == 1)
		return (IS_DIRECTORY);
	return (0);
}

void	ft_execute(char **args)
{
	char *cmd;
	int id;
	int err;

	cmd = NULL;
	err = 0;
	ft_expand(args);
	id = get_builtin(args[0]);
	if (id)
		exec_builtin(args, id, &g_shell->env);
	else
	{
		if (is_path(args[0]))
			err = exec_binpath(args, g_shell->env);
		else
		{
			if ((err = hash_table(&args[0], g_shell->env)) == 0)
				err = ft_fork(args, g_shell->env);
		}
	}
	if (err)
		err_handler(err, args[0]);
}


void	ft_execute_ast(t_ast *root, char **env)
{
	if (!root)
		return ;
	if (root->left)
		ft_execute_ast(root->left, env);
	if (root->right)
		ft_execute_ast(root->right, env);
	if (root->token->redir)
		handle_redir();
	else if (root->token->type == TOKEN_WORD)
		ft_execute	(root->token->content);
}
