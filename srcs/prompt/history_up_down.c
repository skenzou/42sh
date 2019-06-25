/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_up_down.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 06:28:16 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/25 23:55:04 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	histo_up(t_cap *tcap, t_history *h)
{
	char		*string;
	char		*command;
	int			len;

	if (h->position == h->len)
	{
		tputs(tcap->sound, 1, ft_put_termcaps);
		return (1);
	}
	h->position++;
	ft_clear_replace(tcap);
	command = h->data[h->len - h->position - 1];
	if (!command)
		return (1);
	len = ft_strlen(command);
	if (!len)
		return (1);
	string = ft_strnew(len);
	ft_strncpy(string, command, len);
	ft_insert(string, tcap);
	return (1);
}

int	histo_down(t_cap *tcap, t_history *h)
{
	char		*string;
	char		*command;
	int			len;

	if (h->position == -1)
	{
		tputs(tcap->sound, 1, ft_put_termcaps);
		return (1);
	}
	h->position--;
	ft_clear_replace(tcap);
	command = h->data[h->len - h->position - 1];
	if (!command)
		return (1);
	len = ft_strlen(command);
	if (!len)
		return (1);
	string = ft_strnew(len);
	ft_strncpy(string, command, len);
	ft_insert(string, tcap);
	return (1);
}
