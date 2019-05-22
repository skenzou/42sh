/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:51:02 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/21 17:43:38 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const t_oplist existing_token[] =
{
	{"while", 5, TOKEN_WHILE, OTHER_OP},
	{"$((", 3, TOKEN_OP_ARITHM, OTHER_OP},
	{">>-", 3, TOKEN_REDIR, DBL_GREAT_DASH},
	{"<<-", 3, TOKEN_REDIR, DBL_LESS_DASH},
	// {"for", 3, TOKEN_FOR, OTHER_OP},
	{"0>&", 3, TOKEN_REDIR, GREAT_AND},
	{"1>&", 3, TOKEN_REDIR, GREAT_AND},
	{"2>&", 3, TOKEN_REDIR, GREAT_AND},
	{"3>&", 3, TOKEN_REDIR, GREAT_AND},
	{"4>&", 3, TOKEN_REDIR, GREAT_AND},
	{"5>&", 3, TOKEN_REDIR, GREAT_AND},
	{"6>&", 3, TOKEN_REDIR, GREAT_AND},
	{"7>&", 3, TOKEN_REDIR, GREAT_AND},
	{"8>&", 3, TOKEN_REDIR, GREAT_AND},
	{"9>&", 3, TOKEN_REDIR, GREAT_AND},
	{"0<&", 3, TOKEN_REDIR, LESS_AND},
	{"1<&", 3, TOKEN_REDIR, LESS_AND},
	{"2<&", 3, TOKEN_REDIR, LESS_AND},
	{"3<&", 3, TOKEN_REDIR, LESS_AND},
	{"4<&", 3, TOKEN_REDIR, LESS_AND},
	{"5<&", 3, TOKEN_REDIR, LESS_AND},
	{"6<&", 3, TOKEN_REDIR, LESS_AND},
	{"7<&", 3, TOKEN_REDIR, LESS_AND},
	{"8<&", 3, TOKEN_REDIR, LESS_AND},
	{"9<&", 3, TOKEN_REDIR, LESS_AND},
	{"0>", 2, TOKEN_REDIR, GREAT},
	{"1>", 2, TOKEN_REDIR, GREAT},
	{"2>", 2, TOKEN_REDIR, GREAT},
	{"3>", 2, TOKEN_REDIR, GREAT},
	{"4>", 2, TOKEN_REDIR, GREAT},
	{"5>", 2, TOKEN_REDIR, GREAT},
	{"6>", 2, TOKEN_REDIR, GREAT},
	{"7>", 2, TOKEN_REDIR, GREAT},
	{"8>", 2, TOKEN_REDIR, GREAT},
	{"9>", 2, TOKEN_REDIR, GREAT},
	{"0<", 2, TOKEN_REDIR, LESS},
	{"1<", 2, TOKEN_REDIR, LESS},
	{"2<", 2, TOKEN_REDIR, LESS},
	{"3<", 2, TOKEN_REDIR, LESS},
	{"4<", 2, TOKEN_REDIR, LESS},
	{"5<", 2, TOKEN_REDIR, LESS},
	{"6<", 2, TOKEN_REDIR, LESS},
	{"7<", 2, TOKEN_REDIR, LESS},
	{"8<", 2, TOKEN_REDIR, LESS},
	{"9<", 2, TOKEN_REDIR, LESS},
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

static int		join_if_2words(t_list **lexer, char *str, e_token_type type)
{
	t_token *token;
	size_t	i;

	i = 0;
	if (type == TOKEN_WORD && *lexer &&
		((t_token *)((*lexer)->content))->type == TOKEN_WORD && (!(*lexer)->next || ((t_token *)(((*lexer)->next)->content))->type != TOKEN_REDIR))
	{
		token = (t_token *)(*lexer)->content;
		token->content = realloc_new_tab(str, token->content, token->size);
		token->size++;
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
	if (join_if_2words(lexer, str, type))
		return ;
	if (op_type == SEMI && (*lexer == NULL || (*lexer &&
		((t_token *)((*lexer)->content))->op_type == SEMI)))
		{
			free(str);
			return ;
		}
	if (!(token.content = (char **)ft_memalloc((sizeof(char *) * 2))))
		ft_exit("Malloc failed in create_token");
	token.content[0] = str;
	token.content[1] = NULL;
	token.size = 1;
	token.len = ft_strlen(str);
	token.type = type;
	token.is_op = op_type != OTHER_OP;
	token.op_type = op_type;
	token.redir = op_type == TOKEN_REDIR;
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
		if (*input == '\\')
			input += 2;
		curr = check_ops(input);
		if ((curr.op) && prev != input)
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
			// if (!*input || (*input != '\'' && *input != '"'))
			// 	return (0);
			input++;
		}
		else
			input++;
	}
	if (prev != input)
		create_token(lexer, ft_strsub(prev, 0, input - prev), TOKEN_WORD, OTHER_OP);
	ft_lstrev(lexer);
	return (1);
}
