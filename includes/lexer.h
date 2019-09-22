/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:57:23 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/22 21:31:53 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "shell.h"

/*
** les 5 premiers sont des TOKEN_CTL_OPERATOR
** cad des token de d'operateur de controle
** les 10 suivant sont des TOKEN_REDIR cad des token d'operateur de redirection
** OTHER_OP c'est tout ce qui n'est pas un TOKEN_REDIR ou un TOKEN_CTL_OPERATOR
*/

typedef enum	e_op_type
{
	SEMI,
	DBL_SEMI,
	PIPE,
	DBL_PIPE,
	AND,
	DBL_AND,
	LESS,
	DBL_LESS,
	GREAT,
	DBL_GREAT,
	LESS_AND,
	GREAT_AND,
	LESS_GREAT,
	DBL_LESS_DASH,
	DBL_GREAT_DASH,
	CLOBBER,
	OTHER_OP,
}				t_op_type;

typedef enum	e_token_type
{
	TOKEN_EAT,
	TOKEN_DQ,
	TOKEN_SQ,
	TOKEN_CTL_OPERATOR,
	TOKEN_NEG,
	TOKEN_OP_ARITHM,
	TOKEN_OP_BRA,
	TOKEN_CL_BRA,
	TOKEN_OP_PAR,
	TOKEN_CL_PAR,
	TOKEN_REDIR,
	TOKEN_ASS_WORD,
	TOKEN_OP_CMD,
	TOKEN_OP_CURLY,
	TOKEN_CL_CURLY,
	TOKEN_EQUAL,
	TOKEN_WORD,
	TOKEN_FOR,
	TOKEN_WHILE,
	TOKEN_BSLASH,
	TOKEN_NULL
}				t_token_type;

typedef struct		s_token
{
	char			**content;
	size_t			size;
	char			is_op;
	t_op_type		op_type;
	t_token_type	type;
	char			redir;
}					t_token;

typedef struct		s_oplist
{
	char			*op;
	size_t			len;
	t_token_type	type;
	t_op_type		op_type;
}					t_oplist;

typedef struct		s_ast
{
	char			job;
	t_token			*token;
	t_list			*list_pointer;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;
/*
** LEXER.C
*/
int					build_lexer(char *input, t_list **lexer);
t_oplist			check_ops(char *str);
/*
** PRINT_LEXER.C
*/
void				print_lexer(t_list *lexer);
void				print_optype(t_op_type op_type);
/*
**  UTILS.C
*/
void				lex_delone(void *data, size_t size);
void				lex_del_list(t_list **lexer);
int					is_in_lexer(t_list *lexer, t_op_type optype);

#endif
