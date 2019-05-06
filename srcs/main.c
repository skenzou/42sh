/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:27:48 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/07 00:37:35 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <stdio.h>

t_arrow_event g_arrow_event[] = {
	{UP, &arrow_up_event},
	{DOWN, &arrow_down_event},
	{RIGHT, &arrow_right_event},
	{LEFT, &arrow_left_event},
	{SHIFT_UP, &shift_arrow_up_event},
	{SHIFT_DOWN, &shift_arrow_down_event},
	{SHIFT_RIGHT, &shift_arrow_right_event},
	{SHIFT_LEFT, &shift_arrow_left_event}
};
t_key_event g_key_event[] = {
	{ENTER, &enter_event},
	{BACKSPACE, &backspace_event},
	{CTRL_R, &ctrl_r_event},
	{CTRL_D, &ctrl_d_event},
	{TAB, &tab_event},
	{HOME, &home_event},
	{END, &end_event}
};
t_curs	g_curs = (t_curs){
	.x = 0,
	.y = 0,
	.prompt_len = 0,
	.last = 0,
};
int		init_termcaps(t_term *term)
{
	if (tcgetattr(0, term) == -1)
		return (0);
	term->c_lflag &= ~(ICANON | ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, term) == -1 ||
		!(g_curs.command = ft_strnew(BUFFSIZE)))
		return (0);
	return (1);
}

int		wcharlen(char nb)
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

void	display_prompt_prefix(void)
{
	char *string;
	char *name;

	name = get_env("USER");
	name || (name = "21sh");
	string = NULL;
	string = getcwd(string, 20);
	g_curs.prompt_len = ft_strlen((string + ft_lastindexof(string, '/') + 1)) +
		ft_strlen(name) + 4;
	ft_printf(PREFIX);
	ft_printf(SUFFIX, (string + ft_lastindexof(string, '/') + 1), name);
}

int		main(int ac, char **av, char **env)
{
	t_term	term;
	char	buffer[4];

	(void)ac;
	(void)av;
	init_env(env);
	if (init_history() == -1)
		return (-1);
	if (!(tgetent(NULL, getenv("TERM"))) || !init_termcaps(&term))
		return (-1);
	display_prompt_prefix();
	while ("21sh")
	{
		signal(SIGINT, sigint_handler);
		signal(SIGWINCH, sigwinch_handler);
		ft_bzero(buffer, 4);
		read(0, &buffer, 3);
		if ((ft_isprint(buffer[0]) || wcharlen(buffer[0]) > 1) && buffer[0] != 62)
		{
			ft_printf("%s", buffer, buffer[0]);
			add_to_cmd(buffer, -1, wcharlen(buffer[0]));
		}
		if (!read_buffer(buffer))
			return (-1);
	}
	return (0);
}
