/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:27:48 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/10 09:00:22 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <stdio.h>

t_event g_arrow_event[] = {
	{UP, &arrow_up_event},
	{DOWN, &arrow_down_event},
	{RIGHT, &arrow_right_event},
	{LEFT, &arrow_left_event},
	{SHIFT_UP, &shift_arrow_up_event},
	{SHIFT_DOWN, &shift_arrow_down_event},
	{SHIFT_RIGHT, &shift_arrow_right_event},
	{SHIFT_LEFT, &shift_arrow_left_event}
};
t_event g_key_event[] = {
	{ENTER, &enter_event},
	{BACKSPACE, &backspace_event},
	{CTRL_R, &ctrl_r_event},
	{CTRL_D, &ctrl_d_event},
	{TAB, &tab_event},
	{HOME, &home_event},
	{END, &end_event}
};
t_shell *g_shell;

int				wcharlen(char nb)
{
	int i;
	int count;

	i = 7;
	count = 0;
	if (nb > 0)
		return (1);
	while (i > 3)
	{
		if ((nb & (1 << i)) > 0)
			count++;
		i--;
	}
	return (count);
}

int				main(int ac, char **av, char **env)
{
	t_term	term;
	char	buffer[4];

	(void)ac;
	(void)av;
	if (!(tgetent(NULL, getenv("TERM"))) || !init_struct(&term, env))
		return (-1);
	print_prompt_prefix();
	while ("21sh")
	{
		signal(SIGINT, sigint_handler);
		signal(SIGWINCH, sigwinch_handler);
		ft_bzero(buffer, 4);
		read(0, &buffer, 3);
		if (!read_buffer(buffer, g_shell->tcap))
			return (-1);
	}
	return (0);
}
