/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:23:43 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/09 23:33:34 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		enter_event(t_cap *tcap)
{
	tcap->cursx = tcap->prompt_len;
	tcap->cursy = 0;
	if (tcap->char_len >= BUFFSIZE - 1)
	{
		tcap->command[BUFFSIZE - 2] = '\n';
		tcap->command[BUFFSIZE - 1] = '\0';
	}
	else
		tcap->command[tcap->char_len] = '\n';
	if (add_cmd_to_history(tcap->command, g_shell->history) == -1)
		return (-1);
	tcap->char_len = 0;
	if (!ft_strcmp(tcap->command, "history\n"))
		debug_history(g_shell->history);
	else if (!ft_strcmp(tcap->command, "exit\n"))
		exit(0);
	else
		ft_printf("\n%s", tcap->command);
	ft_bzero(tcap->command, BUFFSIZE);
	display_prompt_prefix();
	return (1);
}

int		backspace_event(t_cap *tcap)
{
	return (ft_delete_back(tcap));
}

int		ctrl_r_event(t_cap *tcap)
{
	ft_insert("ctrl_r", tcap);
	return (1);
}

int		ctrl_d_event(t_cap *tcap)
{
	(void)tcap;
	ft_insert("ctrl_d", tcap);
	exit(0);
	return (1);
}

int		tab_event(t_cap *tcap)
{
	(void)tcap;
	return (1);
}
