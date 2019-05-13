/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:04:00 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/13 07:31:06 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void ft_clear_replace(t_cap *tcap)
{
	ft_clear_all_lines(tcap);
	ft_bzero(tcap->command, BUFFSIZE);
	tcap->char_len = 0;
	tcap->cursx = tcap->prompt_len;
	tcap->cursy = 0;
	ft_replace_cursor(tcap);
}

int        arrow_up_event(t_cap *tcap)
{
	t_history	*h;
	char		*string;
	char		*command;
	int			len;

	h = g_shell->history;

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
	ft_strncpy(string, command, len - 1);
	ft_insert(string, tcap);
	return (1);
}

int		arrow_down_event(t_cap *tcap)
{
	t_history	*h;
	char		*string;
	char		*command;
	int			len;

	h = g_shell->history;
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
	ft_strncpy(string, command, len - 1);
	ft_insert(string, tcap);
	return (1);
}

int		arrow_right_event(t_cap *tcap)
{
	return (ft_right(tcap));
}

int		arrow_left_event(t_cap *tcap)
{
	return (ft_left(tcap));
}
