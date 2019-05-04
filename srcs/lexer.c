/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:51:02 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/04 19:01:25 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell.h"

static const t_oplist existing_token[] =
{
	{"while", 5, TOKEN_WHILE, OTHER_OP},
	{"$((", 3, TOKEN_OP_ARITHM, OTHER_OP},
	{">>-", 3, TOKEN_REDIR, DBL_GREAT_DASH},
	{"<<-", 3, TOKEN_REDIR, DBL_LESS_DASH},
	{"for", 3, TOKEN_FOR, OTHER_OP},
	{"$(", 2, TOKEN_OP_CMD, OTHER_OP},
	{"${", 2, TOKEN_OP_CURLY, OTHER_OP},
	{">>", 2, TOKEN_REDIR, DBL_GREAT},
	{"<<", 2, TOKEN_REDIR, DBL_LESS},
	{"||", 2, TOKEN_CTL_OPERATOR, DBL_PIPE},
	{">|", 2, TOKEN_REDIR, CLOBBER},
	{"<>", 2, TOKEN_REDIR, LESS_GREAT},
	{"<&", 2, TOKEN_REDIR, LESS_AND},
	{">&", 2, TOKEN_REDIR, GREAT_AND},
	{"&&", 2, TOKEN_CTL_OPERATOR, DBL_AND},
	{"{ ", 2, TOKEN_OP_BRA, OTHER_OP},
	{"{\n", 2, TOKEN_OP_BRA, OTHER_OP},
	{"{\v", 2, TOKEN_OP_BRA, OTHER_OP},
	{"{\t", 2, TOKEN_OP_BRA, OTHER_OP},
	{"{\r", 2, TOKEN_OP_BRA, OTHER_OP},
	{"{\f", 2, TOKEN_OP_BRA, OTHER_OP},
	{" {", 2, TOKEN_CL_BRA, OTHER_OP},
	{"\n{", 2, TOKEN_CL_BRA, OTHER_OP},
	{"\v{", 2, TOKEN_CL_BRA, OTHER_OP},
	{"\t{", 2, TOKEN_CL_BRA, OTHER_OP},
	{"\r{", 2, TOKEN_CL_BRA, OTHER_OP},
	{"\f{", 2, TOKEN_CL_BRA, OTHER_OP},
	{";;", 2, TOKEN_CTL_OPERATOR, DBL_SEMI},
	{"! ", 2, TOKEN_NEG, OTHER_OP},
	{"}", 1, TOKEN_CL_BRA, OTHER_OP},
	{"|", 1, TOKEN_CTL_OPERATOR, PIPE},
	{"&", 1, TOKEN_CTL_OPERATOR, AND},
	{"(", 1, TOKEN_OP_PAR, OTHER_OP},
	{")", 1, TOKEN_CL_PAR, OTHER_OP},
	{">", 1, TOKEN_REDIR, GREAT},
	{"<", 1, TOKEN_REDIR, LESS},
	{"(", 1, TOKEN_OP_PAR, OTHER_OP},
	{")", 1, TOKEN_CL_PAR, OTHER_OP},
	{"{", 1, TOKEN_OP_CURLY, OTHER_OP},
	{"}", 1, TOKEN_CL_CURLY, OTHER_OP},
	{";", 1, TOKEN_CTL_OPERATOR, SEMI},
	{" ", 1, TOKEN_EAT, OTHER_OP},
	{"\n", 1, TOKEN_EAT, OTHER_OP},
	{"\v", 1, TOKEN_EAT, OTHER_OP},
	{"\t", 1, TOKEN_EAT, OTHER_OP},
	{"\r", 1, TOKEN_EAT, OTHER_OP},
	{"\f", 1, TOKEN_EAT, OTHER_OP},
	{"=", 1, TOKEN_EQUAL, OTHER_OP},
	{NULL, 1, 0, OTHER_OP}
};

static void 		create_token(t_list **lexer, char *str,
															e_token_type type, e_op_type op_type)
{
	t_token token;
	t_list *list;

	if (!str)
		ft_exit("Malloc fail");
	token.content = str;
	token.len = ft_strlen(str);
	token.type = type;
	token.is_op = op_type != OTHER_OP;
	token.op_type = op_type;
	list = ft_lstnew((void *)&token, sizeof(token));
	if (!list)
		exit(1);
	ft_lstadd(lexer, list);
}

static t_oplist		check_ops(char *str)
{
	const t_oplist *curr;
	int		i;

	curr = existing_token;
	i = -1;
	while (curr[++i].op)
		if (ft_strncmp(str, curr[i].op, curr[i].len) == 0)
			return (curr[i]);
	return (curr[i]);
}

static void print_optype(e_op_type op_type)
{
	ft_printf(ANSI_CYAN"==>");
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
	ft_printf(ANSI_BLUE"==>");
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

void 				print_list(t_list *lexer)
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

int					lex_input(char *input, t_list **lexer)
{
	t_oplist	curr;
	char		*prev;

	prev = input;
	while (input && *input)
	{
		while (*input && *input == '\\')
			input++;
		curr = check_ops(input);
		if ((curr.op || *input == '"' || *input == '\'') && prev != input)
			create_token(lexer, ft_strsub(prev, 0, input - prev), TOKEN_WORD, OTHER_OP);
		if (curr.op)
		{
			if (curr.type != TOKEN_EAT)
				create_token(lexer, ft_strdup(curr.op), curr.type, curr.op_type);
			input += curr.len;
			prev = input;
		}
		else if (*input == '\'' || *input == '"')
		{
			input++;
			while (*input && *input != '\'' && *input != '"')
				input++;
			if (!*input || (*input != '\'' && *input != '"'))
				return (0);
			input++;
		}
		else
			input++;
	}
	if (prev != input)
		create_token(lexer, ft_strsub(prev, 0, input - prev), TOKEN_WORD, OTHER_OP);
	return (1);
}
