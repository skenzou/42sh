/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:31:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/12 02:07:26 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_go_up(size_t row)
{
	char	*res;

	if (row == 0)
		return ;
	res = tgetstr("UP", NULL);
	tputs(tgoto(res, 0, row), 0, ft_put_termcaps);
}

void	ft_clear_all_lines(t_cap *tcap)
{
	int		i;

	i = tcap->cursy + 1;
	while (--i > 0)
		tputs(tcap->up, 1, ft_put_termcaps);
	tputs(tgetstr("cr", NULL), 1, ft_put_termcaps);
	i = -1;
	while (++i < tcap->prompt_len + 1)
		tputs(tcap->right, 1, ft_put_termcaps);
	tputs(tgetstr("ce", NULL), 1, ft_put_termcaps);
	if (tcap->char_len + tcap->prompt_len + 1> tcap->cursx_max)
	{
		tputs(tcap->down, 1, ft_put_termcaps);
		tputs(tcap->carriage, 1, ft_put_termcaps);
		tputs(tgetstr("cd", NULL), 1, ft_put_termcaps);
		tputs(tcap->up, 1, ft_put_termcaps);
		i = -1;
		while (++i < tcap->prompt_len)
			tputs(tcap->right, 1, ft_put_termcaps);
	}
}

/*
**up = tcap->up;
**down = tcap->down;
**right = tcap->right;
**left = tcap->left;
*/

int		read_buffer(char buffer[4], t_cap *tcap)
{
	char key;

	if (ft_isprint(buffer[0]) || wcharlen(buffer[0]) > 1)
		return (ft_insert(buffer, tcap));
	if (is_arrow(buffer))
		return (read_arrow(buffer[2], tcap));
	else if ((key = is_shift_arrow(buffer)) != -1)
		return (read_arrow(key + 10, tcap));
	else if ((key = is_key(buffer)) != -1)
		return (read_key(key, tcap));
	else if (DEBUG_LOG)
		ft_printf("%c|%hhd", buffer[0], buffer[0]);
	return (1);
}
