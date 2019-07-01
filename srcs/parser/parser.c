/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 23:37:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/07/01 05:42:02 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		init_ast(t_list *lexer)
{
	if (is_in_lexer(lexer, SEMI) || is_in_lexer(lexer, AND))
		build_ast(lexer, &g_shell->ast, SEMI, AND);
	else if (is_in_lexer(lexer, DBL_AND) || is_in_lexer(lexer, DBL_PIPE))
		build_ast(lexer, &g_shell->ast, DBL_AND, DBL_PIPE);
	else
		build_ast(lexer, &g_shell->ast, PIPE, OTHER_OP);
	if (g_shell->print_flags & PRINT_AST)
		print_ast(g_shell->ast, ft_strdup("root"));
}

void			ft_parse(t_list *lexer)
{
	char *error;

	g_shell->ast = NULL;
	if (!lexer)
		return ;
	error = check_syntax_errors(lexer);
	if (error)
	{
		ft_putstr_fd(ANSI_RED"21sh: parse error near '", 2);
		ft_putstr_fd(error, 2);
		ft_putendl_fd("'", 2);
		ft_lstdel(&lexer, lex_delone);
		return ;
	}
	handle_inhibitors(lexer);
	if (g_shell->inhib_mod == 2)
		return ;
	create_redir_list(lexer);
	ft_lstrev(&g_shell->redir);
	if (g_shell->print_flags & PRINT_REDIR)
		print_redir(g_shell->redir);
	join_all_redir(lexer);
	init_ast(lexer);
}
