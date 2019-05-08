/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 00:37:47 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/09 00:43:04 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

static int	init_termcap(t_cap *tcap)
{
	struct winsize	*w;

	if (!(w = ft_memalloc(sizeof(*w))))
		return (0);
	tcap->cursx_max = (ioctl(1, TIOCGWINSZ, w) ? w->ws_col : tgetnum("co")) - 1;
	tcap->cursy = 0;
	free(w);
	tcap->up = tgetstr("up", NULL);
	tcap->down = tgetstr("sf", NULL);
	tcap->right = tgetstr("nd", NULL);
	tcap->left = tgetstr("le", NULL);
	tcap->carriage = tgetstr("cr", NULL);
	tcap->clr_curr_line = tgetstr("ce", NULL);
	tcap->clr_all_line = tgetstr("cd", NULL);
	tcap->place_cursor = tgetstr("ch", NULL);
	tcap->sound = tgetstr("bl", NULL);
	return (1);
}

static int	init_history(t_history *history)
{
	history->len = 0;
	history->data[0] = NULL;
	history->read = 0;
	if (read_history() == -1)
		return (0);
	return (1);
}

int			init_struct(t_term *trm, char **env)
{
	if (tcgetattr(0, trm) == -1 || !(g_shell = ft_memalloc(sizeof(*g_shell))))
		return (-1);
	g_shell->history = ft_memalloc(sizeof(*g_shell->history));
	g_shell->tcap = ft_memalloc(sizeof(*g_shell->tcap));
	if (!(g_shell->env = dup_env(env)) || !g_shell->tcap || !g_shell->history)
		return (-1);
	init_termcap(g_shell->tcap);
	init_history(g_shell->history);
	trm->c_lflag &= ~(ICANON | ECHO);
	trm->c_cc[VMIN] = 1;
	trm->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, trm) == -1)
		return (-1);
	return (1);
}
