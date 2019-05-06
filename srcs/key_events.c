/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:23:43 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/07 00:48:08 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		enter_event()
{
	g_curs.x = 0;
	if (add_cmd_to_history(g_curs.command) == -1)
		return (-1);
	ft_putchar('\n');
	if (!ft_strcmp(g_curs.command, "history"))
	{
		debug_history();
	}
	else
		handler(g_curs.command);
	ft_bzero(g_curs.command, BUFFSIZE + 1);
	display_prompt_prefix();
	return (1);
}

int		backspace_event()
{
	tputs(tgoto(tgetstr("ch", NULL), UNUSED, g_curs.prompt_len + 1), 1, ft_put_termcaps);
	tputs(tgetstr("cd", NULL), 1, ft_put_termcaps);
	g_curs.x = 0;
	return (1);
}

int		ctrl_r_event()
{
	ft_printf("ctrl_r\n");
	display_prompt_prefix();
	return (1);
}

int		ctrl_d_event()
{
	ft_printf("ctrl_d\n");
	exit(0);
	return (1);
}

int		tab_event()
{
	ft_printf("tab\n");
	display_prompt_prefix();
	return (1);
}

int		home_event()
{
	//ft_printf("home\n");
	tputs(tgoto(tgetstr("ch", NULL), UNUSED, g_curs.prompt_len + 1), 1, ft_put_termcaps);
	//display_prompt_prefix();
	return (1);
}

int		end_event()
{
	tputs(tgoto(tgetstr("ch", NULL), UNUSED, g_curs.prompt_len + 1 + g_curs.last), 1, ft_put_termcaps);
	return (1);
}
