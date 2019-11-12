/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_r.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 06:02:13 by aben-azz          #+#    #+#             */
/*   Updated: 2019/11/12 16:11:34 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		clear_before_ctrl_r(t_cap *tcap, t_ctrl_r *ctrl_r)
{
	ft_move(tcap, "up", 1);
	ft_move(tcap, "down", 1);
	tputs(tcap->clr_all_line, 1, ft_put_termcaps);
	ft_move(tcap, "up", 1);
	tputs(tcap->clr_all_line, 1, ft_put_termcaps);
	ft_move(tcap, "up", 1);
	return (back_i_search(ctrl_r, tcap));
}

int		add_buffer_ctrl_r(char *buffer, t_ctrl_r *ctrl_r)
{
	int i;

	i = -1;
	while (++i < (int)ft_strlen2(buffer))
		ctrl_r->data[ctrl_r->index++] = buffer[0];
	ctrl_r->data[ctrl_r->index] = '\0';
	return (clear_before_ctrl_r(g_shell->tcap, ctrl_r));
}

int		end_ctrl_r(t_ctrl_r *ctrl_r)
{
	t_cap *tcap;

	tcap = g_shell->tcap;
	ctrl_r->state = 0;
	ctrl_r->index = 0;
	ft_bzero(ctrl_r->data, BUFFSIZE);
	if (!ctrl_r->not_found)
	{
		ft_strcpy(tcap->command, ctrl_r->found);
		tcap->char_len = ft_strlen2(ctrl_r->found);
	}
	ctrl_r->not_found = 0;
	ft_bzero(ctrl_r->found, BUFFSIZE);
	return (-2);
}

int		search_ctrl_r(t_ctrl_r *ctrl_r, t_history *history)
{
	int		i;
	char	string[BUFFSIZE];
	int		len;

	if (!ctrl_r->index)
		return (1);
	len = 0;
	i = -1;
	ft_bzero(string, BUFFSIZE);
	ft_bzero(ctrl_r->found, BUFFSIZE);
	while (++i < history->len)
	{
		ft_strcpy(string, history->data[history->len - i - 1]);
		if ((len = ft_strlen2(string)))
		{
			if (!ft_strncmp(string, ctrl_r->data, ctrl_r->index))
			{
				ft_bzero(ctrl_r->found, BUFFSIZE);
				ft_strncpy(ctrl_r->found, string, len);
				return (1);
			}
		}
	}
	ctrl_r->not_found = 1;
	return (1);
}

int		back_i_search(t_ctrl_r *ctrlr, t_cap *tcap)
{
	end_event(tcap);
	ft_move(tcap, "down", 1);
	if (!(search_ctrl_r(ctrlr, g_shell->history)))
		return (0);
	if (12 + ctrlr->index > tcap->cursx_max - 2)
	{
		ft_putstr("bck_i_search: command too long");
		ft_move(tcap, "down", 1);
		ft_putstr("error");
	}
	else
	{
		ft_printf("bck_i_search: %s_", ctrlr->data);
		ft_move(tcap, "down", 1);
		ft_printf("result: %s", ctrlr->not_found ? "no results" : ctrlr->found);
	}
	return (1);
}
