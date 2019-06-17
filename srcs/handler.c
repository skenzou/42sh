/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 17:39:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/16 17:58:32 by ghamelek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**dup_env(const char **env)
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

int	handler(const char *input)
{
	t_list *redir;
	char 	*in;
	if (!ft_strcmp(input, "history\n"))
	{
		debug_history(g_shell->history);
		return (1);
	}
	if (!(in = ft_strdup(input)))
		exit(1); //TODO + free input ??
	in[ft_strlen(in) - 1] = '\0';
 	in = parse_aliases(in, in, in);
	build_lexer(in, &g_shell->lexer);
	ft_strdel(&in);
	if (g_shell->print_flags & PRINT_LEXER)
		print_lexer(g_shell->lexer);
	g_shell->ast = ft_parse(g_shell->lexer);
	redir = g_shell->redir;
	ft_execute_ast(g_shell->ast);
	ft_lstdel(&redir, redir_delone);      // leak possible 
	del_ast(&g_shell->ast);
	g_shell->redir = NULL;
	g_shell->lexer = NULL;
	return (1);
}
