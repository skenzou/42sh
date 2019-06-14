/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 23:37:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/14 05:55:11 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_ast  *ft_parse(t_list *lexer)
{
	char *error;
	t_ast *root;

	if (!lexer)
		return (NULL);
	root = NULL;
	error = check_syntax_errors(lexer);
	if (error)
	{
		ft_putstr_fd(ANSI_RED"21sh: parse error near '", 2);
		ft_putstr_fd(error, 2);
		ft_putendl_fd("'", 2);
		ft_lstdel(&lexer, lex_delone);
		return (NULL);
	}
	handle_inhibitors(lexer);
	create_redir_list(lexer);
	if (g_shell->print_flags & PRINT_REDIR)
		print_redir(g_shell->redir);
	join_all_redir(lexer);
	if (is_in_lexer(lexer, SEMI) || is_in_lexer(lexer, AND))
		build_ast(lexer, &root, SEMI, AND);
	else if (is_in_lexer(lexer, DBL_AND))
		build_ast(lexer, &root, DBL_AND, OTHER_OP);
	else if (is_in_lexer(lexer, DBL_PIPE))
		build_ast(lexer, &root, DBL_PIPE, OTHER_OP);
	else
		build_ast(lexer, &root, PIPE, OTHER_OP);
	if (g_shell->print_flags & PRINT_AST)
		print_ast(root, ft_strdup("root"));
	return root;
}
