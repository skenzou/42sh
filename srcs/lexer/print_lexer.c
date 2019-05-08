/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 00:34:12 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/08 04:23:00 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void print_optype(e_op_type op_type)
{
	ft_printf(ANSI_BCYAN"==>");
	op_type == 0 ? ft_printf("SEMI" ANSI_RESET): 0;
	op_type == 1 ? ft_printf("DBL_SEMI"ANSI_RESET): 0;
	op_type == 2 ? ft_printf("PIPE"ANSI_RESET): 0;
	op_type == 3 ? ft_printf("DBL_PIPE"ANSI_RESET): 0;
	op_type == 4 ? ft_printf("AND"ANSI_RESET): 0;
	op_type == 5 ? ft_printf("DBL_AND"ANSI_RESET): 0;
	op_type == 6 ? ft_printf("LESS"ANSI_RESET): 0;
	op_type == 7 ? ft_printf("DBL_LESS"ANSI_RESET): 0;
	op_type == 8 ? ft_printf("GREAT"ANSI_RESET): 0;
	op_type == 9 ? ft_printf("DBL_GREAT"ANSI_RESET): 0;
	op_type == 10 ? ft_printf("LESS_AND"ANSI_RESET): 0;
	op_type == 11 ? ft_printf("GREAT_AND"ANSI_RESET): 0;
	op_type == 12 ? ft_printf("LESS_GREAT"ANSI_RESET): 0;
	op_type == 13 ? ft_printf("DBL_LESS_DASH"ANSI_RESET): 0;
	op_type == 14 ? ft_printf("DBL_GREAT_DASH"ANSI_RESET): 0;
	op_type == 15 ? ft_printf("CLOBBER"ANSI_RESET): 0;
}

static void print_tokentype(e_token_type token_type)
{
	ft_printf(ANSI_BBLUE"==>");
	token_type == 0 ? ft_printf("TOKEN_EAT "ANSI_RESET): 0;
	token_type == 1 ? ft_printf("TOKEN_DQ "ANSI_RESET): 0;
	token_type == 2 ? ft_printf("TOKEN_SQ "ANSI_RESET): 0;
	token_type == 3 ? ft_printf("TOKEN_CTL_OPERATOR "ANSI_RESET): 0;
	token_type == 4 ? ft_printf("TOKEN_NEG "ANSI_RESET): 0;
	token_type == 5 ? ft_printf("TOKEN_OP_ARITHM "ANSI_RESET): 0;
	token_type == 6 ? ft_printf("TOKEN_OP_BRA "ANSI_RESET): 0;
	token_type == 7 ? ft_printf("TOKEN_CL_BRA "ANSI_RESET): 0;
	token_type == 8 ? ft_printf("TOKEN_OP_PAR "ANSI_RESET): 0;
	token_type == 9 ? ft_printf("TOKEN_CL_PAR "ANSI_RESET): 0;
	token_type == 10 ? ft_printf("TOKEN_REDIR "ANSI_RESET): 0;
	token_type == 11 ? ft_printf("TOKEN_ASS_WORD "ANSI_RESET): 0;
	token_type == 12 ? ft_printf("TOKEN_OP_CMD "ANSI_RESET): 0;
	token_type == 13 ? ft_printf("TOKEN_OP_CURLY "ANSI_RESET): 0;
	token_type == 14 ? ft_printf("TOKEN_CL_CURLY "ANSI_RESET): 0;
	token_type == 15 ? ft_printf("TOKEN_EQUAL "ANSI_RESET): 0;
	token_type == 16 ? ft_printf("TOKEN_WORD "ANSI_RESET): 0;
	token_type == 17 ? ft_printf("TOKEN_FOR "ANSI_RESET): 0;
	token_type == 18 ? ft_printf("TOKEN_WHILE "ANSI_RESET): 0;
	token_type == 19 ? ft_printf("TOKEN_NULL "ANSI_RESET): 0;
}

void 				print_lexer(t_list *lexer)
{
	t_token token;
	size_t len;
	t_list *temp;

	len = 1;
	temp = lexer;
	while (temp)
	{
		token = *((t_token *)(temp->content));
		if (ft_strlen(token.content) > len)
			len = ft_strlen(token.content);
		temp = temp->next;
	}
	while (lexer)
	{
		token = *((t_token *)(lexer->content));
		ft_printf("%-*s ", len, token.content);
		print_tokentype(token.type);
		if (token.is_op)
			print_optype(token.op_type);
		lexer = lexer->next;
		if (lexer)
			ft_putchar('\n');
	}
	ft_putchar('\n');
}
