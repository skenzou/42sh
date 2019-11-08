/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 06:02:13 by aben-azz          #+#    #+#             */
/*   Updated: 2019/11/08 00:58:06 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		init_autocomp(t_cap *tcap, t_ab *autocomp)
{
	int max_offset;
	int i;

	max_offset = autocomp->max_offset;
	autocomp->state = 1;
	autocomp->row = tcap->cursx_max / (ft_max(max_offset + 2, 1));
	autocomp->col = autocomp->len / ft_max(autocomp->row, 1);
	autocomp->carry = autocomp->len % ft_max(autocomp->row, 1);
	if (!autocomp->len)
		return (tputs(tcap->sound, 1, ft_put_termcaps) && 0);
	else if (autocomp->len == 1)
	{
		i = ft_strlen(g_shell->autocomp->match);
		while (i--)
			ft_delete_back(tcap);
		ft_insert(g_shell->autocomp->data[0], tcap);
		if (!g_shell->autocomp->isdir && g_shell->autocomp->after[0])
			ft_insert(g_shell->autocomp->after, tcap);
		autocomp->state = 0;
		return (0);
	}
	return (max_offset);
}

int		smart_completion(t_ab *autocomp, t_cap *tc, int position)
{
	char str[MAX_PATH];

	get_word(tc, position, str);
	if (!*str)
		return (0);
	autocomp->len = 0;
	get_quote(autocomp, str);
	if (is_first_argi(tc, position))
		return (first_arg_completion(autocomp, tc, str, position));
	else
		return (arg_completion(autocomp, tc, str, position));
	return (0);
}

int		get_words_completion(t_ab *autocomp, t_cap *tc)
{
	int pos;

	pos = tc->cursy * (tc->cursx_max + 1) + (tc->cursx) - tc->prompt_len;
	pos = pos - 1;
	if (pos == -1 || is_space_before(tc, pos))
	{
		ft_insert("    ", tc);
		return (0);
	}
	else if (tc->command[pos] == ' ' && ((pos + 1 < tc->char_len &&
					tc->command[pos + 1] == ' ') || pos == tc->char_len - 1))
	{
		add_to_completion(autocomp, ".", 0);
		return (1);
	}
	else
	{
		if (smart_completion(autocomp, tc, pos + 1))
			return (1);
	}
	return (0);
}

int		process_completion(t_ab *autocomp)
{
	int		row;
	int		col;
	int		i;
	int		o;
	t_cap	*tcap;

	tcap = g_shell->tcap;
	row = 0;
	i = 0;
	col = -1;
	end_event(tcap);
	o = tcap->cursy * (tcap->cursx_max + 1) + (tcap->cursx) - tcap->prompt_len;
	ft_move(tcap, "left", tcap->char_len - o);
	ft_move(tcap, "down", 1);
	autocomp->row = ft_max(autocomp->row, 1);
	while (++col < autocomp->col && (row = -1))
	{
		while (++row < autocomp->row)
		{
			print_name(autocomp, autocomp->data[i], i);
			i++;
		}
		ft_move(g_shell->tcap, "down", 1);
	}
	return (print_completion(autocomp, row, i));
}

int		ft_tab(t_cap *tcap, t_ab *autocomp)
{
	autocomp->max_offset = 0;
	autocomp->len = 0;
	autocomp->isdir = 0;
	ft_bzero(autocomp->after, MAX_PATH);
	ft_bzero(autocomp->match, MAX_PATH);
	if (!get_words_completion(autocomp, tcap) || !init_autocomp(tcap, autocomp))
		return (1);
	if (autocomp->max_offset >= g_shell->tcap->cursx_max)
	{
		autocomp->state = 0;
		return (1);
	}
	process_completion(autocomp);
	return (1);
}
