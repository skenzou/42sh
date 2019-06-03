/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 00:37:47 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/30 20:36:00 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	init_termcap(t_cap *tcap)
{
	struct winsize	*w;

	if (!(w = ft_memalloc(sizeof(*w))))
		return (0);
	tcap->cursx_max = (ioctl(1, TIOCGWINSZ, w) ? w->ws_col : tgetnum("co"));
	tcap->cursx_max--;
	tcap->cursy = 0;
	free(w);
	tcap->prompt = NULL;
	tcap->up = tgetstr("up", NULL);
	tcap->down = tgetstr("sf", NULL);
	tcap->right = tgetstr("nd", NULL);
	tcap->left = tgetstr("le", NULL);
	tcap->carriage = tgetstr("cr", NULL);
	tcap->clr_curr_line = tgetstr("ce", NULL);
	tcap->clr_all_line = tgetstr("cd", NULL);
	tcap->place_cursor = tgetstr("ch", NULL);
	tcap->sound = tgetstr("bl", NULL);
	tcap->save = tgetstr("sc", NULL);
	tcap->restore = tgetstr("rc", NULL);
	tcap->overflow = 0;
	ft_bzero(tcap->carry, 2);
	return (1);
}

static int	init_history(t_history *history)
{
	history->len = 0;
	history->data[0] = NULL;
	history->read = 0;
	history->position = -1;
	history->file_name = ft_strjoin("/Users/",
						ft_strcjoin(getenv("USER"), DEFAULT_HISTORY_NAME, '/'));
	ft_bzero(history->match, BUFFSIZE);
	if (read_history(history) == -1)
		return (0);
	return (1);
}

static int	init_var(char **var)
{
	int state;

	ft_bzero(var, 256);
	if ((state = read_var(var)) < 0)
	{
		if (state == -2)
			ft_printf("Erreur verifiez le fichier var\n");
		return (0);
	}
	return (1);
}


static int	init_autocomp(t_ab *autocomp)
{
	autocomp->state = 0;
	autocomp->pos = 0;
	return (1);
}


int			init_struct(char **env)
{
	if (!(g_shell = ft_memalloc(sizeof(*g_shell))))
		return (0);
	g_shell->history = ft_memalloc(sizeof(*g_shell->history));
	g_shell->tcap = ft_memalloc(sizeof(*g_shell->tcap));
	g_shell->autocomp = ft_memalloc(sizeof(*g_shell->autocomp));
	g_shell->term = ft_memalloc(sizeof(*g_shell->term));
	g_shell->term_backup = ft_memalloc(sizeof(*g_shell->term_backup));
	if (tcgetattr(0, g_shell->term_backup) == -1 || !~tcgetattr(0, g_shell->term))
		return (0);
	if (!(g_shell->env = dup_env(env)) || !g_shell->tcap || !g_shell->history ||
		!g_shell->autocomp)
		return (0);
	if (!init_var(g_shell->var) || !init_termcap(g_shell->tcap) ||
				!init_history(g_shell->history) || !init_autocomp(g_shell->autocomp))
		return (0);
	g_shell->term->c_lflag &= ~(ICANON | ECHO);
	g_shell->term->c_cc[VMIN] = 1;
	g_shell->term->c_cc[VTIME] = 0;
	g_shell->env_tmp = g_shell->env;
	g_shell->intern_tmp = g_shell->intern;
	if (tcsetattr(0, TCSADRAIN, g_shell->term) == -1)
		return (0);
	return (1);
}
