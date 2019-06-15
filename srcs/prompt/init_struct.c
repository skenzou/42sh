/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 00:37:47 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/15 15:48:08 by ghamelek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	init_termcap(t_cap *tcap)
{
	struct winsize	*w;

	if (!(w = ft_memalloc(sizeof(*w))))
		return (0);
	if (ioctl(1, TIOCGWINSZ, w) != 0)
		tcap->cursx_max = tgetnum("co") - 1;
	else
		tcap->cursx_max = w->ws_col - 1;
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
	char *home;

	if ((home = getenv("HOME")))
	{
		if (!(history->file_name = ft_strcjoin(home, ".42sh_history", '/')))
			return (0);
	}
	else if (!(history->file_name = ft_strdup(".42sh_history")))
		return (0);
	history->len = 0;
	history->data[0] = NULL;
	history->read = 0;
	history->position = -1;
	ft_bzero(history->match, BUFFSIZE);
	if (read_history(history) == -1)
		return (0);
	return (1);
}

static int	init_autocomp(t_ab *autocomp)
{
	autocomp->state = 0;
	autocomp->pos = 0;
	return (1);
}

static int	init_copy_cut_ctrl_r(t_cc *copy_cut, t_ctrl_r *ctrl_r)
{
	copy_cut->state = 0;
	copy_cut->from = -1;
	copy_cut->to = -1;
	copy_cut->type = -1;
	ctrl_r->state = 0;
	ctrl_r->index = 0;
	ctrl_r->not_found = 0;
	ft_bzero(copy_cut->copied, BUFFSIZE);
	ft_bzero(ctrl_r->data, BUFFSIZE);
	return (1);
}

int			init_struct(const char **env)
{
	if (!(g_shell = ft_memalloc(sizeof(*g_shell))))
		return (0);
	g_shell->history = ft_memalloc(sizeof(*g_shell->history));
	g_shell->tcap = ft_memalloc(sizeof(*g_shell->tcap));
	g_shell->autocomp = ft_memalloc(sizeof(*g_shell->autocomp));
	g_shell->copy_cut = ft_memalloc(sizeof(*g_shell->copy_cut));
	g_shell->ctrl_r = ft_memalloc(sizeof(*g_shell->ctrl_r));
	g_shell->term = ft_memalloc(sizeof(*g_shell->term));
	g_shell->term_backup = ft_memalloc(sizeof(*g_shell->term_backup));
	if (tcgetattr(0, g_shell->term_backup) == -1 || !~tcgetattr(0, g_shell->term))
		return (0);
	if (!(g_shell->env = dup_env(env)) || !g_shell->tcap || !g_shell->history ||
		!g_shell->autocomp || !g_shell->copy_cut)
		return (0);
	if (!init_termcap(g_shell->tcap) ||
		!init_history(g_shell->history) || !init_autocomp(g_shell->autocomp) ||
					!init_copy_cut_ctrl_r(g_shell->copy_cut, g_shell->ctrl_r))
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
