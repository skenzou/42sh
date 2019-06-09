/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 17:39:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/30 14:42:35 by midrissi         ###   ########.fr       */
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
	t_list *redir;

	dprintf(debug(), "str: |%s|\n", input);
	if (!ft_strcmp(input, "history\n"))
	{
		debug_history(g_shell->history);
		return (1);
	}
	if (!(input = ft_strdup(input)))
		exit(1); //TODO + free input ??
	input[ft_strlen(input) - 1] = '\0';
 	input = parse_aliases(input, input, input);
	build_lexer(input, &g_shell->lexer);
	if (g_shell->print_flags & PRINT_LEXER)
		print_lexer(g_shell->lexer);
	g_shell->ast = ft_parse(g_shell->lexer);
	redir = g_shell->redir;
	ft_execute_ast(g_shell->ast);
	ft_lstdel(&redir, redir_delone);
	del_ast(&g_shell->ast);
	g_shell->redir = NULL;
	g_shell->lexer = NULL;
	return (1);
}
