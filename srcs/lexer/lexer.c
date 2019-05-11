/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:51:02 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/11 23:50:18 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	{"\\", 1, TOKEN_BSLASH, OTHER_OP},
	{"=", 1, TOKEN_EQUAL, OTHER_OP},
	{NULL, 1, 0, OTHER_OP}
};

static int		join_if_2words(t_list **lexer, char *str, e_token_type type)
{
	t_token *token;
	char *tmp;

	if (type == TOKEN_WORD && *lexer &&
		((t_token *)((*lexer)->content))->type == TOKEN_WORD)
	{
		token = (t_token *)(*lexer)->content;
		tmp = token->content;
		token->content = ft_strcjoin(tmp, str, ' ');
		ft_strdel(&tmp);
		return (1);
	}
	return (0);
}

static void 		create_token(t_list **lexer, char *str,
										e_token_type type, e_op_type op_type)
{
	t_token token;
	t_list *list;

	if (!str)
		ft_exit("Malloc fail");
	ft_putstr(str);
	ft_putchar('|');
	ft_putchar('\n');
	if (join_if_2words(lexer, str, type))
		return ;
	if (op_type == SEMI && (*lexer == NULL || (*lexer &&
		((t_token *)((*lexer)->content))->op_type == SEMI)))
		{
			free(str);
			return ;
		}
	token.content = str;
	token.len = ft_strlen(str);
	token.type = type;
	token.is_op = op_type != OTHER_OP;
	token.op_type = op_type;
	token.redir = 0;
	list = ft_lstnew((void *)&token, sizeof(token));
	if (!list)
		ft_exit("Failed to malloc a node of my lexer list");
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

int					build_lexer(char *input, t_list **lexer)
{
	t_oplist	curr;
	char		*prev;

	prev = input;
	input[ft_strlen(input) - 1] = '\0';
	while (input && *input)
	{
		// while (*input && *input == '\\')
		// 	input++;
		curr = check_ops(input);
		if ((curr.op) && prev != input)
			create_token(lexer, ft_strsub(prev, 0, input - prev), TOKEN_WORD, OTHER_OP);
		if (curr.op)
		{
			if (curr.type == TOKEN_BSLASH)
			{
				create_token(lexer, ft_strsub(input, 0, 2), TOKEN_WORD, OTHER_OP);
				curr.len = 2;
			}
			else if (curr.type != TOKEN_EAT)
				create_token(lexer, ft_strdup(curr.op), curr.type, curr.op_type);
			input += curr.len;
			prev = input;
		}
		else if (*input == '\'' || *input == '"')
		{
			input++;
			while (*input && *input != '\'' && *input != '"')
				input++;
			// if (!*input || (*input != '\'' && *input != '"'))
			// 	return (0);
			input++;
		}
		else
			input++;
	}
	if (prev != input)
		create_token(lexer, ft_strsub(prev, 0, input - prev), TOKEN_WORD, OTHER_OP);
	return (1);
}
