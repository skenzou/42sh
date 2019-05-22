/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 17:39:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/21 15:18:38 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**dup_env(char **env)
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

int	handler(char *input)
{
	if (!ft_strcmp(input, "exit\n"))
		exit(0);
	else if (!ft_strcmp(input, "history\n"))
	{
		debug_history(g_shell->history);
		return (1);
	}
	build_lexer(input, &g_shell->lexer);
	if (g_shell->print_flags & PRINT_LEXER)
		print_lexer(g_shell->lexer);
	g_shell->ast = ft_parse(g_shell->lexer);
	ft_execute_ast(g_shell->ast, g_shell->env);
	del_ast(&g_shell->ast);
	g_shell->lexer = NULL;
	return (1);
}
