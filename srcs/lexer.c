/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:51:02 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/30 19:02:00 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static const t_oplist existing_token[] =
{
	{"while", 5, TOKEN_WHILE},
	{"$((", 3, TOKEN_OP_ARITHM},
	{">>-", 3, TOKEN_REDIR},
	{"for", 3, TOKEN_FOR},
	{"$(", 2, TOKEN_OP_CMD},
	{"${", 2, TOKEN_OP_CURLY},
	{">>", 2, TOKEN_REDIR},
	{"<<", 2, TOKEN_REDIR},
	{"||", 2, TOKEN_DBLOR},
	{">|", 2, TOKEN_REDIR},
	{"<>", 2, TOKEN_REDIR},
	{"<&", 2, TOKEN_REDIR},
	{">&", 2, TOKEN_REDIR},
	{"&&", 2, TOKEN_DBLAND},
	{"{ ", 2, TOKEN_OP_BRA},
	{"{\n", 2, TOKEN_OP_BRA},
	{"{\v", 2, TOKEN_OP_BRA},
	{"{\t", 2, TOKEN_OP_BRA},
	{"{\r", 2, TOKEN_OP_BRA},
	{"{\f", 2, TOKEN_OP_BRA},
	{" {", 2, TOKEN_CL_BRA},
	{"\n{", 2, TOKEN_CL_BRA},
	{"\v{", 2, TOKEN_CL_BRA},
	{"\t{", 2, TOKEN_CL_BRA},
	{"\r{", 2, TOKEN_CL_BRA},
	{"\f{", 2, TOKEN_CL_BRA},
	{";;", 2, TOKEN_DBL_SEMI},
	{"! ", 2, TOKEN_NEG},
	{"}", 1, TOKEN_CL_BRA},
	{"|", 1, TOKEN_PIPE},
	{"&", 1, TOKEN_AND},
	{"(", 1, TOKEN_OP_PAR},
	{")", 1, TOKEN_CL_PAR},
	{">", 1, TOKEN_REDIR},
	{"<", 1, TOKEN_REDIR},
	{"(", 1, TOKEN_OP_PAR},
	{")", 1, TOKEN_CL_PAR},
	{"{", 1, TOKEN_OP_CURLY},
	{"}", 1, TOKEN_CL_CURLY},
	{";", 1, TOKEN_SEMI},
	{" ", 1, TOKEN_EAT},
	{"\n", 1, TOKEN_EAT},
	{"\v", 1, TOKEN_EAT},
	{"\t", 1, TOKEN_EAT},
	{"\r", 1, TOKEN_EAT},
	{"\f", 1, TOKEN_EAT},
	{"=", 1, TOKEN_EQUAL},
	{NULL, 1, 0}
};

static void 		create_token(t_list **lexer, char *str, size_t len,
															e_token_type type)
{
	t_token token;
	t_list *list;

	token.content = ft_strsub(str, 0, len);
	token.len = len;
	token.type = type;
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

void 				print_list(t_list *lexer)
{
	t_token token;
	while (lexer)
	{
		token = *((t_token *)(lexer->content));
		ft_printf("<%s  (%d)> ", token.content, token.type);
		lexer = lexer->next;
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
			create_token(lexer, prev, input - prev, TOKEN_NAME);
		if (curr.op)
		{
			if (curr.type != TOKEN_EAT)
				create_token(lexer, input, curr.len, curr.type);
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
		create_token(lexer, prev, input - prev, TOKEN_NAME);
	return (1);
}
