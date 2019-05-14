/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 01:26:02 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/15 01:26:24 by midrissi         ###   ########.fr       */
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
		return (((t_token *)(tokens->content))->content[0]);
	while (tokens && tokens->next)
	{
		curr = (t_token *)(tokens->content);
		next = (t_token *)(tokens->next->content);
		if (curr->type == TOKEN_REDIR && next->type != TOKEN_WORD)
			return (next->content[0]);
		if (curr->type == TOKEN_CTL_OPERATOR && next->type == TOKEN_CTL_OPERATOR)
			return (next->content[0]);
		tokens = tokens->next;
	}
	curr = (t_token *)(tokens->content);
	if (curr->type == TOKEN_REDIR)
		return "\\n";
	return (NULL);
}
