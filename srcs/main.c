/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:27:48 by aben-azz          #+#    #+#             */
/*   Updated: 2019/04/28 12:02:41 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <stdio.h>

int		fputchar(int c)
{
	write(1, &c, 1);
	return (1);
}

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

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, sig_handler);
		printf("on quitte\n");
		exit(0);
	}
}

void display_prompt()
{
	ft_printf("\x1b[32m$21sh>\x1b[0m ");
}

void read_arrows(char touche[2], int shift, int *curseur)
{
	(void)curseur;
	if (shift)
	{
		if (touche[1] == ARROW_UP)
			ft_printf("{LU}\n");
		else if (touche[1] == ARROW_DOWN)
			ft_printf("{LD}\n");
		else if (touche[1] == ARROW_LEFT)
			ft_printf("{LL}\n");
		else if (touche[1] == ARROW_RIGHT)
			ft_printf("{LR}\n");
		display_prompt();
	}
	else
	{
		if (touche[1] == ARROW_UP)
			ft_printf("{LU}");
		else if (touche[1] == ARROW_DOWN)
			ft_printf("{LD}");
		else if (touche[1] == ARROW_LEFT)
		{
			if (*curseur)
			{
				tputs(tgoto(tgetstr("LE", NULL), 1, 0), 0, fputchar);
			}
		}
		else if (touche[1] == ARROW_RIGHT)
		{
			tputs(tgoto(tgetstr("RI", NULL), 1, 0), 0, fputchar);
		}
		if (touche[1] == ARROW_UP || touche[1] == ARROW_DOWN ||
				touche[1] == ARROW_LEFT || touche[1] == ARROW_RIGHT)
				;
	}
}

int		exec_command(char *command)
{
	ft_printf("%s\n", command);
	return (1);
}

void	get_col(void)
{
	ft_printf("col {%d, %d}\n", tgetnum("co"), tgetnum("li"));
}

int		main(int ac, char **av)
{
	t_term	term;
	char	buffer;
	char	touche[2];
	char	command[BUFFSIZE];
	int		curseur;

	curseur = 0;
	command[BUFFSIZE - 1] = '\0';

	(void)ac;
	(void)av;
	buffer = 0;
	if (!(tgetent(NULL, getenv("TERM"))) || !init_termcaps(&term))
		return (-1);
	get_col();
	signal(SIGINT, sig_handler);
	display_prompt();
	while (19)
	{
		read(0, &buffer, 1);
		if (buffer == 27 || buffer == 59)
		{
			read(0, touche, 2);
			read_arrows(touche, buffer == 59, &curseur);
		}
		else if (buffer == 4)
		{
			printf("Ctlr+d\n");
			return (0);
		}
		else if (buffer == 10)
		{
			command[curseur] = '\0';
			curseur = 0;
			ft_putchar('\n');
			exec_command(command);
			display_prompt();
		}
		else if (buffer == 127)
		{
			if (curseur)
			{
				tputs(tgetstr("le", NULL), 1, fputchar);
				ft_putchar(' ');
				tputs(tgetstr("le", NULL), 1, fputchar);
				curseur--;
			}
		}
		else
		{
			command[curseur++] = buffer;
			ft_printf("%c", buffer);
		}
	}
	return (0);
}
