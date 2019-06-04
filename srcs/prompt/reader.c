/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:31:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/25 08:23:10 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_clear_all_lines(t_cap *tcap)
{
	ft_move(tcap, "up", tcap->cursy);
	tputs(tcap->carriage, 1, ft_put_termcaps);
	ft_move(tcap, "!right", tcap->prompt_len);
	tputs(tcap->clr_curr_line, 1, ft_put_termcaps);
	if (tcap->char_len + tcap->prompt_len > tcap->cursx_max + 1)
	{
		ft_move(tcap, "down", 1);
		tputs(tcap->carriage, 1, ft_put_termcaps);
		tputs(tcap->clr_all_line, 1, ft_put_termcaps);
		ft_move(tcap, "up", 1);
		ft_move(tcap, "!right", tcap->prompt_len);
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

	if ((ft_isprint(buffer[0]) || wcharlen(buffer[0]) >1 ) && buffer[0] != SPACE)
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
