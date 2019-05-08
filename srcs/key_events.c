/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:23:43 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/08 08:10:02 by aben-azz         ###   ########.fr       */
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
	if (add_cmd_to_history(tcap->command) == -1)
		return (-1);
	//ft_printf("curs {%d, %d} {%d, %d}\n", tcap->cursx, tcap->cursy, tcap->char_len, tcap->prompt_len);
	tcap->char_len = 0;
	ft_putchar('\n');
	if (!ft_strcmp(tcap->command, "history"))
	{
		debug_history();
	}
	else
		handler(tcap->command);
	ft_bzero(tcap->command, BUFFSIZE);
	display_prompt_prefix();
	return (1);
}

int		backspace_event(t_cap *tcap)
{
	ft_delete_back(tcap);
	return (1);
}

int		ctrl_r_event(t_cap *tcap)
{
	(void)tcap;
	ft_printf("ctrl_r\n");
	display_prompt_prefix();
	return (1);
}

int		ctrl_d_event(t_cap *tcap)
{
	(void)tcap;
	ft_printf("ctrl_d\n");
	exit(0);
	return (1);
}

int		tab_event(t_cap *tcap)
{
	(void)tcap;
	ft_printf("curs: {%d, %d}\n", tcap->cursx, tcap->cursy);
	return (1);
}

int		home_event(t_cap *tcap)
{
	tputs(tgoto(tgetstr("ch", NULL), UNUSED,
		tcap->prompt_len + 1), 1, ft_put_termcaps);
	return (1);
}

int		end_event(t_cap *tcap)
{
	tputs(tgoto(tgetstr("ch", NULL), UNUSED,
		tcap->prompt_len + 1 + tcap->char_len), 1, ft_put_termcaps);
	return (1);
}
