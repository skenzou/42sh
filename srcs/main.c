/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 17:39:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/07 23:15:32 by ghamelek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	t_list	*lexer;
	t_ast *trees;

	trees  = NULL;
	ret = 1;
	env = dup_env(env);
	lexer = NULL;
	while (ret == 1)
	{
		signal(SIGINT, sighandler);
		print_prompt();
		if ((ret = get_next_line(0, &input)) > 0)
			build_lexer(input, &lexer);
		ft_lstrev(&lexer);
		print_lexer(lexer);
	trees = ft_parse(lexer);
	ft_compiler(trees,env);
		lex_del_list(&lexer);
		ft_strdel(&input);
	}
	(void)argc;
	(void)argv;
	ft_splitdel(env);
	return (0);
}
