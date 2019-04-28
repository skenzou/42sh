/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:27:48 by aben-azz          #+#    #+#             */
/*   Updated: 2019/04/28 16:10:32 by aben-azz         ###   ########.fr       */
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
	term->c_lflag &= ~(ICANON);
	term->c_lflag &= ~(ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	*curseur = (t_curs){0, 0, 0};
	if (tcsetattr(0, TCSADRAIN, term) == -1)
		return (0);
	return (1);
}

int		exec_command(char *command)
{
	if (!ft_strcmp(command, "clear"))
		tputs(tgetstr("cl", NULL), 0, ft_put_termcaps);
	else if (!ft_strcmp(command, "exit"))
		kill(0, SIGINT);
	else
		ft_printf("%s\n", command);
	return (1);
}

int		main(int ac, char **av, char **env)
{
	t_term	term;
	int		buffer;
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
	display_prompt();
	while ("21sh")
	{
		read(0, &buffer, 4);
		if (!read_buffer(buffer, curseur, command))
			return (-1);
		buffer = 0;
	}
	return (0);
}
