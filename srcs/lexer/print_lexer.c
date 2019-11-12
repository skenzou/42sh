/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 00:34:12 by midrissi          #+#    #+#             */
/*   Updated: 2019/11/12 19:30:22 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				print_optype(t_op_type op_type)
{
	ft_printf(ANSI_BCYAN"==>");
	op_type == 0 ? ft_printf("SEMI" ANSI_RESET) : 0;
	op_type == 1 ? ft_printf("DBL_SEMI"ANSI_RESET) : 0;
	op_type == 2 ? ft_printf("PIPE"ANSI_RESET) : 0;
	op_type == 3 ? ft_printf("DBL_PIPE"ANSI_RESET) : 0;
	op_type == 4 ? ft_printf("AND"ANSI_RESET) : 0;
	op_type == 5 ? ft_printf("DBL_AND"ANSI_RESET) : 0;
	op_type == 6 ? ft_printf("LESS"ANSI_RESET) : 0;
	op_type == 7 ? ft_printf("DBL_LESS"ANSI_RESET) : 0;
	op_type == 8 ? ft_printf("GREAT"ANSI_RESET) : 0;
	op_type == 9 ? ft_printf("DBL_GREAT"ANSI_RESET) : 0;
	op_type == 10 ? ft_printf("LESS_AND"ANSI_RESET) : 0;
	op_type == 11 ? ft_printf("GREAT_AND"ANSI_RESET) : 0;
	op_type == 12 ? ft_printf("LESS_GREAT"ANSI_RESET) : 0;
	op_type == 13 ? ft_printf("DBL_LESS_DASH"ANSI_RESET) : 0;
	op_type == 14 ? ft_printf("DBL_GREAT_DASH"ANSI_RESET) : 0;
	op_type == 15 ? ft_printf("CLOBBER"ANSI_RESET) : 0;
	op_type == 16 ? ft_printf("OTHER_OP"ANSI_RESET) : 0;
}

static void			print_tokentype(t_token_type token_type)
{
	ft_printf(ANSI_BBLUE"==>");
	token_type == 0 ? ft_printf("TOKEN_EAT "ANSI_RESET) : 0;
	token_type == 1 ? ft_printf("TOKEN_DQ "ANSI_RESET) : 0;
	token_type == 2 ? ft_printf("TOKEN_SQ "ANSI_RESET) : 0;
	token_type == 3 ? ft_printf("TOKEN_CTL_OPERATOR "ANSI_RESET) : 0;
	token_type == 4 ? ft_printf("TOKEN_NEG "ANSI_RESET) : 0;
	token_type == 5 ? ft_printf("TOKEN_OP_ARITHM "ANSI_RESET) : 0;
	token_type == 6 ? ft_printf("TOKEN_OP_BRA "ANSI_RESET) : 0;
	token_type == 7 ? ft_printf("TOKEN_CL_BRA "ANSI_RESET) : 0;
	token_type == 8 ? ft_printf("TOKEN_OP_PAR "ANSI_RESET) : 0;
	token_type == 9 ? ft_printf("TOKEN_CL_PAR "ANSI_RESET) : 0;
	token_type == 10 ? ft_printf("TOKEN_REDIR "ANSI_RESET) : 0;
	token_type == 11 ? ft_printf("TOKEN_ASS_WORD "ANSI_RESET) : 0;
	token_type == 12 ? ft_printf("TOKEN_OP_CMD "ANSI_RESET) : 0;
	token_type == 13 ? ft_printf("TOKEN_OP_CURLY "ANSI_RESET) : 0;
	token_type == 14 ? ft_printf("TOKEN_CL_CURLY "ANSI_RESET) : 0;
	token_type == 15 ? ft_printf("TOKEN_EQUAL "ANSI_RESET) : 0;
	token_type == 16 ? ft_printf("TOKEN_WORD "ANSI_RESET) : 0;
	token_type == 17 ? ft_printf("TOKEN_FOR "ANSI_RESET) : 0;
	token_type == 18 ? ft_printf("TOKEN_WHILE "ANSI_RESET) : 0;
	token_type == 19 ? ft_printf("TOKEN_BSLASH "ANSI_RESET) : 0;
	token_type == 20 ? ft_printf("TOKEN_NULL "ANSI_RESET) : 0;
}

void				print_lexer(t_list *lexer)
{
	t_token		*token;
	size_t		i;

	ft_printf("===========================LEXER============================\n");
	while (lexer)
	{
		i = 0;
		token = (t_token *)(lexer->content);
		while (i < token->size)
		{
			ft_printf("%-s ", token->content[i]);
			i++;
		}
		print_tokentype(token->type);
		if (token->is_op)
			print_optype(token->op_type);
		lexer = lexer->next;
		if (lexer)
			ft_putchar('\n');
	}
	ft_printf("\n==========================================================\n");
}
