/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 00:53:00 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/22 21:32:14 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "shell.h"

typedef struct		s_redir
{
	char			**dest;
	t_op_type		op_type;
	int				fd;
	int				hdoc_fd;
	char			end_of_leaf;
}					t_redir;
/*
** AST.C
*/
void				del_ast(t_ast **root);
t_ast				*newnode(t_token *token, t_list *pointer);
void				print_ast(t_ast *root, char *str);
/*
** BUILD_AST.C
*/
void				build_ast(t_list *lexer, t_ast **root, t_op_type optype1,
															t_op_type optype2);
/*
** CREATE_REDIR_LIST.C
*/
void				create_redir_list(t_list *lexer);
/*
** INHIBTORS.C
*/
void				handle_inhibitors(t_list *lexer);
/*
** PARSE.C
*/
void				ft_parse(t_list *lexer);
/*
** REDIR_LIST_TOOLS.C
*/
int					get_preceded_fd(char c, t_op_type redir_type);
void				create_redir(char *red, char **dest, size_t size,
														t_op_type redir_type);
t_list				*get_next_redir(t_list *lexer);
void				join_2(t_list *lexer);
void				join_all_redir(t_list *lexer);
/*
** SYNTAX_ERRORS.C
*/
char				*check_syntax_errors(t_list *tokens);

#endif
