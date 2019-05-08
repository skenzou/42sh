/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:27:48 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/08 02:43:40 by aben-azz         ###   ########.fr       */
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

int		init_termcaps(t_term *trm)
{
	struct winsize	*w;

	if (!(g_shell = ft_memalloc(sizeof(*g_shell))))
		return (0);
	g_shell->history = ft_memalloc(sizeof(*g_shell->history));
	g_shell->tcap = ft_memalloc(sizeof(*g_shell->tcap));
	w = ft_memalloc(sizeof(*w));
	if (tcgetattr(0, trm) == -1 || !g_shell->tcap|| !g_shell->history || !w)
		return (0);
	g_shell->tcap->cursx_max = (ioctl(1, TIOCGWINSZ, w) ?
		w->ws_col - 1 : tgetnum("co") - 1);
	free(w);
	trm->c_lflag &= ~(ICANON | ECHO);
	trm->c_cc[VMIN] = 1;
	trm->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, trm) == -1)
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
	g_shell->tcap->prompt_len =
		ft_strlen((string + ft_lastindexof(string, '/') + 1)) +
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

	//ft_printf("xd\n");
	if (!(tgetent(NULL, getenv("TERM"))) || !init_termcaps(&term))
		return (-1);
	if (init_history() == -1)
		return (-1);
	display_prompt_prefix();
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
