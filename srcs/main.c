/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:27:48 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/01 00:40:30 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <stdio.h>

t_arrow_event g_arrow_event[] = {
	{ARROW_UP, &arrow_up_event},
	{ARROW_DOWN, &arrow_down_event},
	{ARROW_RIGHT, &arrow_right_event},
	{ARROW_LEFT, &arrow_left_event}
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

int wcharlen(int nb)
{
	ft_printf("wchar %d|%d|\n", nb, nb > 128);
	int i;
	int count;

	if (nb < 128)
		return (1);
	i = 7;
	count = 0;
	while (i > 3)
	{
		if ((nb & (1 << i)) > 0)
			count++;
		i--;
	}
	return count;
}

int		main(int ac, char **av, char **env)
{
	t_term	term;
	//int		buffer;
	wchar_t	buffer[6];
	char	command[BUFFSIZE];
	t_curs	*curseur;

	(void)ac;
	(void)av;
	char lol[3];

	lol[0] = 0b11100010;
	lol[1] = 0b10000010;
	lol[2] = 0b10101100;
	ft_printf("jpp: %s\n", lol);
	buffer[5] = '\0';
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
		read(0, &buffer, 5);

		// if (!read_buffer(buffer, curseur, command))
		// 	return (-1);

		ft_printf("buffer: |%hhb|%d|\n", buffer[0], wcharlen(buffer[0]));
		buffer[0] = 0;
	}
	return (0);
}
