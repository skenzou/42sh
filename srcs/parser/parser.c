/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 23:37:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/06 18:57:53 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Cherche si un erreur de syntax existing_token
** Renvoie une erreur si un TOKEN_REDIR est pas suivie d'un TOKEN_WORD ou
** si deux TOKEN_CTL_OPERATOR se suivent (pour l'instant)
*/
char		*check_syntax_errors(t_list *tokens)
{
  t_token *curr;
  t_token *next;

	if (tokens && ((t_token *)(tokens->content))->type == TOKEN_CTL_OPERATOR)
		return (((t_token *)(tokens->content))->content);
	while (tokens && tokens->next)
	{
		curr = (t_token *)(tokens->content);
		next = (t_token *)(tokens->next->content);
		if (curr->type == TOKEN_REDIR && next->type != TOKEN_WORD)
			return (next->content);
		if (curr->type == TOKEN_CTL_OPERATOR && next->type == TOKEN_CTL_OPERATOR)
			return (next->content);
		tokens = tokens->next;
	}
	return (NULL);
}


void  ft_parse(t_list *lexer)
{
	char *error;

	error = check_syntax_errors(lexer);
	if (error)
	{
	ft_putstr_fd(ANSI_RED"21sh: parse error near'", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd("'", 2);
	}
}
