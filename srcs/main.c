/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:27:48 by aben-azz          #+#    #+#             */
/*   Updated: 2019/04/27 18:05:15 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <stdio.h>

int		init_termcaps(t_term *term)
{
	if (tcgetattr(0, term) == -1)
		return (0);
	term->c_lflag &= ~(ICANON);
	term->c_lflag &= ~(ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, term) == -1)
		return (0);
	return (1);
}

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("on quitte\n");
		exit(0);
	}
}
void display_prompt()
{
	ft_printf("\x1b[32m$21sh>\x1b[0m ");
}
int		main(int ac, char **av)
{
	t_term	term;
	char	buffer;
	char	touche[2];
	(void)ac;
	(void)av;
	buffer = 0;
	if (!(tgetent(NULL, getenv("TERM"))) || !init_termcaps(&term))
		return (-1);
	signal(SIGINT, sig_handler);
	display_prompt();
	while (19)
	{
		read(0, &buffer, 1);
		if (buffer == 27)
		{
			read(0, touche, 2);
			if (touche[1] == ARROW_UP)
				ft_printf("{U}\n");
			else if (touche[1] == ARROW_DOWN)
				ft_printf("{D}\n");
			else if (touche[1] == ARROW_LEFT)
				ft_printf("{L}\n");
			else if (touche[1] == ARROW_RIGHT)
				ft_printf("{R}\n");
			display_prompt();
		}
		else if (buffer == 4)
		{
			printf("Ctlr+d\n");
			return (0);
		}
		else if (buffer == 10)
		{
			ft_putchar('\n');
			display_prompt();

		}
		else
		{
			//printf("touche: %d\n", buffer);
			ft_printf("%c", buffer);
		}
	}
	return (0);
}
