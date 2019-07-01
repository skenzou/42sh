/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 17:39:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/07/01 07:49:28 by midrissi         ###   ########.fr       */
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
	check_inhib(&in);
	if (g_shell->inhib_mod == 2)
	{
		ft_strdel(&in);
		return (1);
	}
	build_lexer(in, &g_shell->lexer);
	ft_strdel(&in);
	if (g_shell->print_flags & PRINT_LEXER)
		print_lexer(g_shell->lexer);
	ft_parse(g_shell->lexer);
	redir = g_shell->redir;
	handle_hdoc(redir);
	if (g_shell->inhib_mod == 2)
		return (1);
	ft_execute_ast(g_shell->ast);
	ft_lstdel(&redir, redir_delone);      // leak possible
	del_ast(&g_shell->ast);
	g_shell->redir = NULL;
	g_shell->lexer = NULL;
	return (1);
}
