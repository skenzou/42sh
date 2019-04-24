/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 21:26:08 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/29 18:01:44 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		find_bin(char **bin, char **env, char **paths)
{
	char		path[MAX_PATH_LEN];
	struct stat	buff;
	pid_t		pid;
	int			i;

	i = -1;
	while (paths && paths[++i])
	{
		set_path(path, bin[0], paths[i]);
		if (!lstat(path, &buff))
			if (!access(path, X_OK))
			{
				pid = fork();
				signal(SIGINT, sigfork);
				if (!pid)
					execve(path, bin, env);
				else if (pid < 0)
					return (FAILFORK);
				wait(&pid);
				return (0);
			}
	}
	return (NOT_FOUND);
}

static int		exec_envpath(char **bin, char **env)
{
	char	*paths;
	char	**split_paths;
	int		err;

	if ((paths = get_env_path(env)) == NULL || paths[0] == '\0')
		split_paths = NULL;
	else
		split_paths = ft_strsplit(paths, ':');
	err = find_bin(bin, env, split_paths);
	ft_splitdel(split_paths);
	return (err);
}

static int		exec_binpath(char **bin, char **env)
{
	struct stat	buff;
	pid_t		pid;

	if (lstat(bin[0], &buff) == -1)
		return (NON_EXISTENT);
	if (S_ISREG(buff.st_mode) == 1 && !access(bin[0], X_OK))
	{
		pid = fork();
		signal(SIGINT, sigfork);
		if (pid == 0)
			execve(bin[0], bin, env);
		else if (pid < 0)
			return (FAILFORK);
		wait(&pid);
	}
	else if (access(bin[0], X_OK) != 0)
		return (NO_RIGHT);
	else if (S_ISDIR(buff.st_mode) == 1)
		return (IS_DIRECTORY);
	return (0);
}

void			exec_bin(char **bin, char **env)
{
	int err;

	if (is_path(bin[0]))
		err = exec_binpath(bin, env);
	else
		err = exec_envpath(bin, env);
	if (err)
		err_handler(err, bin[0]);
}
