/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 06:02:13 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/25 23:57:40 by aben-azz         ###   ########.fr       */
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
	{
		tputs(tcap->sound, 1, ft_put_termcaps);
		return (0);
	}
	else if (autocomp->len == 1)
	{
		i = ft_strlen(g_shell->autocomp->match);
		while (i--)
			ft_delete_back(tcap);
		ft_insert(g_shell->autocomp->data[0], tcap);
		if (g_shell->autocomp->after[0] && !g_shell->autocomp->isdir)
			ft_insert(g_shell->autocomp->after, tcap);
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

void	process_completion(t_ab *autocomp, int row, int col, int i)
{
	while (++col < autocomp->col)
	{
		row = -1;
		while (++row < autocomp->row)
			print_name(autocomp, autocomp->data[i], i) && i++;
		ft_move(g_shell->tcap, "down", 1);
	}
	if (autocomp->carry > 0)
	{
		row = autocomp->carry;
		while (row--)
			print_name(autocomp, autocomp->data[i], i) && i++;
	}
	ft_replace_cursor(g_shell->tcap);
	i = 0;
	if (autocomp->col > g_shell->tcap->cursy_max)
		sigint_handler(SIGINT);
	else
		while (i < autocomp->col + (autocomp->carry > 0 ? 1 : +1))
		{
			ft_move(g_shell->tcap, "up", 1);
			i++;
		}
}

int		ft_tab(t_cap *tcap, t_ab *autocomp)
{
	int row;
	int col;
	int i;
	int o;

	row = 0;
	autocomp->max_offset = 0;
	autocomp->len = 0;
	autocomp->isdir = 0;
	ft_bzero(autocomp->after, MAX_PATH);
	ft_bzero(autocomp->match, MAX_PATH);
	if (!get_words_completion(autocomp, tcap) || !init_autocomp(tcap, autocomp))
		return (1);
	i = 0;
	col = -1;
	o = tcap->cursy * (tcap->cursx_max + 1) + (tcap->cursx) - tcap->prompt_len;
	end_event(tcap);
	ft_move(tcap, "left", tcap->char_len - o);
	ft_move(tcap, "down", 1);
	process_completion(autocomp, row, col, i);
	return (1);
}
