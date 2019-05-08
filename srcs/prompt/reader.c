/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:31:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/08 08:06:51 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_replace_cursor(t_cap *tcap)
{
	int		i;
	int		remainder;

	i = (tcap->char_len + tcap->prompt_len) / (tcap->cursx_max + 1);
	remainder = (tcap->char_len + tcap->prompt_len) % (tcap->cursx_max + 1);
	if (remainder == 0)
		i--;
	while (i > 0)
	{
		tputs(tcap->up, 1, ft_put_termcaps);
		i--;
	}
	i = -1;
	while (++i < tcap->cursy)
		tputs(tcap->down, 1, ft_put_termcaps);
	tputs(tcap->chariot, 1, ft_put_termcaps);
	i = -1;
	while (++i < tcap->cursx + 1)
		tputs(tcap->right, 1, ft_put_termcaps);
}

void	ft_add_n_char(char buff[4], int pos, int len, t_cap *tcap)
{
	char	*tmp;

	if (len > (int)ft_strlen(buff))
		len = ft_strlen(buff);
	tmp = ft_strdup(tcap->command);
	ft_bzero(tcap->command, BUFFSIZE);
	ft_strncpy(tcap->command, tmp, pos);
	ft_strncpy(tcap->command + pos, buff, len);
	ft_strcpy(tcap->command + pos + len, tmp + pos);
	tcap->char_len = tcap->char_len + len;
	ft_strdel(&tmp);
}

void	ft_clear_all_lines(t_cap *tcap)
{
	(void)tcap;
	tputs(tgoto(tcap->place_cursor, UNUSED,
		tcap->prompt_len + 1), 1, ft_put_termcaps);
	tputs(tcap->clr_all_line, 1, ft_put_termcaps);
}

/*
**up = tcap->up;
**down = tcap->down;
**right = tcap->right;
**left = tcap->left;
*/

void	ft_move_left(t_cap *tcap)
{
	if (tcap->cursy == 0 && tcap->cursx == tcap->prompt_len)
		tputs(tcap->sound, 1, ft_put_termcaps);
	else if (tcap->cursx != 0)
	{
		tputs(tcap->left, 1, ft_put_termcaps);
		tcap->cursx--;
	}
	else if (tcap->cursx == 0)
	{
		tputs(tcap->up, 1, ft_put_termcaps);
		tcap->cursy--;
	}
}

void	ft_move_right(t_cap *tcap)
{
	if (tcap->cursy * (tcap->cursx_max + 1) + tcap->cursx + 1
		== tcap->char_len + tcap->prompt_len + 1)
		tputs(tcap->sound, 1, ft_put_termcaps);
	else if (tcap->cursx + 1== tcap->cursx_max)
	{
		tputs(tcap->down, 1, ft_put_termcaps);
		tputs(tcap->chariot, 1, ft_put_termcaps);
		tcap->cursy++;
		tcap->cursx = 0;
	}
	else
	{
		tputs(tcap->right, 1, ft_put_termcaps);
		tcap->cursx++;
	}
}
void	ft_insert(char buff[4], t_cap *tcap)
{
	int		pos;
	int		i;
	int		len;

	if (tcap->char_len + ft_strlen(buff) >= BUFFSIZE - 2)
	{
		tputs(tcap->sound, 1, ft_put_termcaps);
		return ;
	}
	len = ft_strlen(buff);
	pos = tcap->cursy * (tcap->cursx_max + 1) + tcap->cursx - tcap->prompt_len;
	//ft_printf("curs: {%d, %d}\n", tcap->cursx, tcap->cursy);
	ft_clear_all_lines(tcap);
	ft_add_n_char(buff, pos, len, tcap);
	ft_putstr(tcap->command);
	ft_replace_cursor(tcap);
	i = -1;
	while (++i < len)
		ft_move_right(tcap);
}

void	ft_delete_n_char(t_cap *tcap, int pos, int len)
{
	char	*tmp;

	tmp = ft_strdup(tcap->command);
	ft_bzero(tcap->command, BUFFSIZE);
	ft_strncpy(tcap->command, tmp, pos);
	ft_strcpy(tcap->command + pos, tmp + pos + len);
	ft_strdel(&tmp);
	tcap->char_len = tcap->char_len - len;
}

void	ft_delete_back(t_cap *tcap)
{
	int		pos;

	if (tcap->cursy == 0 && tcap->cursx == tcap->prompt_len)
	{
		tputs(tcap->sound, 1, ft_put_termcaps);
		return ;
	}
	pos = tcap->cursy * (tcap->cursx_max + 1) + tcap->cursx - tcap->prompt_len;
	pos--;
	ft_clear_all_lines(tcap);
	ft_delete_n_char(tcap, pos, 1);
	ft_putstr(tcap->command);
	ft_replace_cursor(tcap);
	ft_move_left(tcap);
}

int			read_buffer(char buffer[4], t_cap *tcap)
{
	char key;

	if (ft_isprint(buffer[0]) || wcharlen(buffer[0]) > 1)
	{
		ft_printf("%s", buffer);
		ft_insert(buffer, tcap);
	}
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
