/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 09:15:55 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/26 13:35:30 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		input_handler(char *input, char ***env)
{
	int		i;
	char	**cmds;

	if (!(cmds = ft_strsplit(input, ';')))
		exit(1);
	ft_strdel(&input);
	i = -1;
	while (cmds[++i])
		cmd_handler(cmds[i], env);
	ft_splitdel(cmds);
}

static char		**dup_env(char **env)
{
	char	**p;
	int		i;

	i = ft_split_count(env);
	if (!(p = (char **)ft_memalloc(sizeof(char *) * (i + 1))))
		exit(0);
	i = -1;
	while (env[++i])
		if (!(p[i] = ft_strdup(env[i])))
			exit(0);
	p[i] = NULL;
	return (p);
}

int				main(int argc, char **argv, char **env)
{
	char	*input;
	int		ret;

	ret = 1;
	env = dup_env(env);
	while (ret == 1)
	{
		print_prompt();
		signal(SIGINT, sighandler);
		if ((ret = get_next_line(0, &input)) > 0)
			input_handler(input, &env);
	}
	(void)argc;
	(void)argv;
	ft_strdel(&input);
	ft_splitdel(env);
	return (0);
}
