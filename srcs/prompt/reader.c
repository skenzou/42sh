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
oui	oui
ls -l
ls -a
*/

int	handle_eol(char *buffer, t_cap *tcap)
{
	(void)buffer;
	char str[2];
	(void)tcap;
	if (buffer[0] == '\n')
	{
		ft_insert(buffer + 1, tcap);
		return (-2);
	}
	else if (buffer[1] == '\n')
	{
		ft_bzero(str, 2);
		str[0] = buffer[0];
		ft_insert(buffer, tcap);
		tcap->overflow = 1;
		ft_bzero(tcap->carry, 2);
		tcap->carry[0] = buffer[2];
		return (-2);
	}
	else
	{
		ft_strncpy(str, buffer, 2);
		ft_insert(str, tcap);
		return (-2);
	}

	return (1);
}

int		read_buffer(char *buffer, t_cap *tcap)
{
	char key;

//dprintf(debug(), "{%d, %d, %d}'\n",buffer[0], buffer[1], buffer[2]);
	 if (~ft_indexof(buffer, '\n'))
	 	return (handle_eol(buffer, tcap));
	else if ((ft_isprint(buffer[0]) || wcharlen(buffer[0]) >1 ) && buffer[0] != SPACE)
		return (ft_insert(buffer, tcap));
	else if (is_arrow(buffer))
		return (read_arrow(buffer[2], tcap));
	else if ((key = is_shift_arrow(buffer)) != -1)
		return (read_arrow(key + 10, tcap));
	else if ((key = is_key(buffer)) != -1)
		return (read_key(key, tcap));
	else if (DEBUG_LOG)
		ft_printf("%c|%hhd", buffer[0], buffer[0]);
	return (1);
}
