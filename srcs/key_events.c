/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:23:43 by aben-azz          #+#    #+#             */
/*   Updated: 2019/04/28 16:28:31 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		enter_event(t_curs *curseur, char *command)
{
	command[curseur->x] = '\0';
	curseur->x = 0;
	ft_putchar('\n');
	//exec_command(command);
	handler(command);
	display_prompt_prefix();
	return (1);
}

int		backspace_event(t_curs *curseur, char *command)
{
	(void)command;
	if (curseur->x > 0)
	{
		tputs(tgetstr("le", NULL), 1, ft_put_termcaps);
		ft_putchar(' ');
		tputs(tgetstr("le", NULL), 1, ft_put_termcaps);
		curseur->x--;
	}
	return (1);
}
