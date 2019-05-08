/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:57:45 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/08 02:43:43 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		find_built(char **argv)
{
	if (!ft_strcmp(argv[0], "echo"))
		return (ft_echo(argv));
	else if (!ft_strcmp(argv[0], "cd"))
		return (ft_cd(argv));
	else if (!ft_strcmp(argv[0], "setenv"))
		return (ft_setenv(argv));
	else if (!ft_strcmp(argv[0], "unsetenv"))
		return (ft_unsetenv(argv));
	else if (!ft_strcmp(argv[0], "env"))
		return (ft_env(argv));
	else if (!ft_strcmp(argv[0], "exit"))
		return (ft_exit(argv));
	return (-1);
}

int		ft_echo(char **argv)
{
	int i;

	i = 0;
	while (argv[++i])
	{
		while (*argv[i])
		{
			if (!~ft_indexof("\"'", *argv[i]))
				ft_printf("%c", *argv[i]);
			(void)argv[i]++;
		}
		ft_printf(" ");
	}
	ft_printf(" \n");
	return (0);
}

int		ft_env(char **argv)
{
	(void)argv;
	ft_printf("%r\n", g_env, env_len(g_env), "\n");
	return (0);
}

static void		print_pth(char *path)
{
	if (!path)
		return ;
	ft_putstr(path);
}

int				change_dir(char *path, int print_path)
{
	char	*cwd;
	char	buff[4097];

	cwd = getcwd(buff, 4096);
	if (!chdir(path))
	{
		if (print_path)
		{
			print_pth(path);
			ft_putchar('\n');
		}
		set_env("OLDPWD", cwd);
		set_env("PWD", getcwd(buff, 4096));
	}
	else
	{
		if (access(path, F_OK) == -1)
			ft_putstr("cd: no such file or directory: ");
		else if (access(path, R_OK) == -1)
			ft_putstr("cd: permission denied: ");
		else
			ft_putstr("cd: not a directory: ");
		ft_putendl(path);
	}
	return (1);
}

static int		has_two_args(char **args)
{
	char	*cwd;
	char	buff[4096 + 1];
	char	*tmp;

	tmp = NULL;
	if (args[2])
	{
		if (args[3])
		{
			ft_putendl("cd: too many arguments\n");
			return (1);
		}
		cwd = getcwd(buff, 4096);
		if (!(tmp = ft_strreplace(cwd, args[1], args[2])))
		{
			ft_putstr("cd: string not in pwd: ");
			ft_putendl(args[1]);
			free(tmp);
			return (1);
		}
		change_dir(tmp, 1);
		free(tmp);
		return (1);
	}
	return (0);
}

int				ft_cd(char **argv)
{
	char	*home_path;

	home_path = get_env("HOME");
	if (!argv[1])
	{
		change_dir(home_path, 0);
		return (1);
	}
	if (has_two_args(argv))
		return (1);
	else
	{
		if (ft_strequ(argv[1], "--") || ft_strequ(argv[1], "~"))
		{
			change_dir(home_path, 0);
			return (1);
		}
		else if (argv[1][0] == '-' && !argv[1][2])
		{
			change_dir(get_env("OLDPWD"), 1);
			return (1);
		}
		change_dir(argv[1], 0);
	}
	return (1);
}

void			signal_handler_command(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, signal_handler_command);
		ft_printf("\n");
	}
}

int		quick_cd(char **cmd)
{
	char	*s;
	t_stat	f;
	char	*buff;

	buff = NULL;
	buff = getcwd(buff, 4096);
	s = (cmd[0] + ft_lastindexof(cmd[0], '/') + 1);
	if (!ft_strcmp(s, ".."))
		return (change_dir(ft_strsub(buff, 0, ft_lastindexof(buff, '/')), 0));
	else if (!ft_strcmp(s, "~"))
		return (change_dir(get_env("HOME"), 0));
	else if (lstat(cmd[0], &f) != -1)
	{
		if (f.st_mode & S_IFDIR)
			return (change_dir(cmd[0], 0));
		else
			return (-1);
	}
	else if (lstat(s, &f) != -1 && (f.st_mode & S_IFDIR))
	{
		return (change_dir(s, 0));
	}
	return (-1);
}

int		set_env(char *key, char *value)
{
	int		index;
	char	*tmp;

	tmp = ft_strjoin("=", value);
	if (~(index = get_env_index(key)))
		free(g_env[index]);
	else if ((index = env_len(g_env)))
		g_env = realloc_env(index + 1, -1);
	g_env[index] = ft_strjoin(key, value ? tmp : "=");
	return (0);
}

int		ft_setenv(char **argv)
{
	if (!argv[1])
		return (ft_env(argv));
	else if (argv[2] && argv[3])
		return (ft_printf("setenv: Too many arguments.\n") > 0);
	return (set_env(argv[1], argv[2]));
}

char	**realloc_env(int new_size, int exception)
{
	char	**new;
	int		i;
	int		j;

	if (!(new = (char **)ft_memalloc(sizeof(char *) * (new_size + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (g_env[++i] && i < new_size)
	{
		(~exception && j == exception) && j++;
		new[i] = ft_strdup(g_env[j++]);
		free(g_env[i]);
	}
	free(g_env);
	return (new);
}

int		ft_unsetenv(char **argv)
{
	int		index;

	if (!argv[1])
		return (ft_env(argv));
	else if (argv[2])
		return (ft_printf("setenv: Too many arguments.\n") > 0);
	if (~(index = get_env_index(argv[1])))
	{
		if (!(g_env = realloc_env(index + 1, index)))
			return (0);
		return (0);
	}
	return (0);
}

int		ft_exit(char **argv)
{
	(void)argv;
	exit(0);
	return (0);
}



int		env_len(char **env)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (env[++i])
		count++;
	return (count);
}

void	init_env(char **env)
{
	int		i;

	if (!(g_env = (char **)ft_memalloc(sizeof(char *) * (env_len(env) + 1))))
		exit(0);
	i = -1;
	while (env[++i])
		if (!(g_env[i] = ft_strdup(env[i])))
			exit(0);
}

char	*get_env(char *name)
{
	int i;

	if (!name)
		return (NULL);
	if (~(i = get_env_index(name)))
		return (ft_strsub(g_env[i], ft_indexof(g_env[i], '=') + 1,
			ft_strlen(g_env[i])));
	else
		return (NULL);
}

int		get_env_index(char *name)
{
	int i;

	i = -1;
	if (!name)
		return (-1);
	while (g_env[++i])
		if (!ft_strcmp(ft_strsub(g_env[i], 0, ft_indexof(g_env[i], '=')), name))
			return (i);
	return (-1);
}

int		execute(char **cmd, int dir)
{
	t_stat	f;

	(void)dir;
	if (lstat(cmd[0], &f) != -1)
	{
		if (f.st_mode & S_IXUSR)
			return (execve(cmd[0], cmd, g_env));
	}
	return (-1);
}

int		exec_valid_command(char **argv, int m)
{
	pid_t	pid;
	char	**av;
	char	**path;
	int		i;

	path = ft_strsplit(get_env("PATH"), ':');
	av = malloc(sizeof(char*) * 2048);
	signal(SIGINT, signal_handler_command);
	if (!(pid = fork()))
	{
		(!m && *argv[0] == '\\' && *(argv[0] + 1) == '/') && ++argv[0];
		if (!m && ~execute(argv, 0))
			return (1);
		while (*path && (i = -1))
		{
			while (argv[++i])
				av[i] = i ? argv[i] : ft_strjoin(ft_strjoin(*path++, "/"),
					argv[0]);
			if (~execute(av, 1))
				return (1);
		}
		ft_printf("minishell: command not found: %s\n",
			(av[0] + ft_lastindexof(av[0], '/') + 1));
		exit(0);
	}
	else if (pid < 0)
		return (ft_printf("Fork failed to create a new process.\n") ? -1 : -1);
	wait(&pid);
	return (1);
}

int		is_expansion_printable(char *s, int dollar_index, int i)
{
	return (!((s[dollar_index - 1] && s[dollar_index - 1] == '\'') &&
			(s[i] && s[i] == '\'')));
}

char	*get_expansion(char *string, char *act_env, int length)
{
	char	*replaced;

	if (get_env(act_env + 1 + length))
	{
		if (!length)
			replaced = ft_strreplace(string, act_env, get_env(act_env + 1));
		else
			replaced = ft_strreplace(string, act_env,
					ft_itoa((int)ft_strlen(get_env(act_env + 2))));
	}
	else if (length)
		replaced = ft_strreplace(string, act_env, "0");
	else
		replaced = ft_strreplace(string, act_env, "");
	return (replaced);
}

char	*expansion_dollar(char *string)
{
	int		i;
	int		length;
	int		dollar_index;
	char	*replaced;
	char	*act_env;

	if (!string || (string && !(replaced = ft_strdup(string))))
		return (NULL);
	dollar_index = ft_indexof(string, '$');
	if (!~dollar_index)
		return (string);
	i = dollar_index + 1;
	length = 0;
	(string[i] == '#') && ((length = 1) && (i++));
	while (i < (int)ft_strlen(string) && string[i] && (string[i] == '_' ||
		ft_isalpha(string[i])))
		i++;
	if (is_expansion_printable(string, dollar_index, i))
	{
		act_env = ft_substr(string, dollar_index, i);
		replaced = get_expansion(string, act_env, length);
	}
	return (replaced);
}

int		handler(char *string)
{
	char	**commands;
	char	**argv;
	char	*test;

	if ((test = expansion_dollar(string)))
		string = test;
	commands = ft_strsplit(string, ';');
	while (*commands)
	{
		argv = ft_strsplitwhitespace(*commands++);
		if (!~find_built(argv))
		{
			while (ft_is_space(*argv[0]))
				(void)*argv[0]++;
			if (!~quick_cd(argv))
				exec_valid_command(argv, !(*argv[0] == '/' ||
					(*argv[0] == '\\' && *(argv[0] + 1) == '/')));
		}
	}
	return (1);
}
