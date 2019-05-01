/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:27:48 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/01 16:16:12 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <stdio.h>

t_arrow_event g_arrow_event[] = {
	{UP, &arrow_up_event},
	{DOWN, &arrow_down_event},
	{RIGHT, &arrow_right_event},
	{LEFT, &arrow_left_event}
};
t_key_event g_key_event[] = {
	{ENTER, &enter_event},
	{BACKSPACE, &backspace_event}
};

int		init_termcaps(t_term *term, t_curs *curseur)
{
	if (tcgetattr(0, term) == -1)
		return (0);
	term->c_lflag &= ~(ICANON | ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	*curseur = (t_curs){0, 0, 0};
	if (tcsetattr(0, TCSADRAIN, term) == -1)
		return (0);
	return (1);
}

int	wcharlen(char nb)
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

int		main(int ac, char **av, char **env)
{
	t_term	term;
	char	buffer[4];
	char	command[BUFFSIZE];
	t_curs	*curseur;

	(void)ac;
	(void)av;
	init_env(env);
	if (!(curseur = malloc(sizeof(curseur))))
		return (-1);
	command[BUFFSIZE - 1] = '\0';
	if (!(tgetent(NULL, getenv("TERM"))) || !init_termcaps(&term, curseur))
		return (-1);
	signal(SIGINT, sig_handler);
	display_prompt_prefix();
	while ("21sh")
	{
		read(0, &buffer, 3);
		if (!read_buffer(buffer, curseur, command, wcharlen(buffer[0]) > 1))
			return (-1);
		ft_bzero(buffer, 6);
	}
	return (0);
}
