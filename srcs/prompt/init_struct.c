/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 00:37:47 by aben-azz          #+#    #+#             */
/*   Updated: 2019/07/11 22:52:08 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			init_termcap(t_cap *tcap)
{
	struct winsize	*w;

	if (!(w = ft_memalloc(sizeof(*w))))
		return (0);
	if (ioctl(1, TIOCGWINSZ, w) != 0)
	{
		tcap->cursx_max = tgetnum("co") - 1;
		tcap->cursy_max = tgetnum("li") - 1;
	}
	else
	{
		tcap->cursx_max = w->ws_col - 1;
		tcap->cursy_max = w->ws_row - 1;
	}
	tcap->cursy = 0;
	free(w);
	tcap->prompt = NULL;
	tcap->overflow = 0;
	ft_bzero(tcap->carry, 2);
	return (1);
}

static int	init_history(t_history *history)
{
	char *home;

	if ((home = ft_strdup(get_key_value("HOME", g_shell->env))))
	{
		if (!(history->file_name = ft_strcjoin(home, ".42sh_history", '/')))
		{
			ft_strdel(&home);
			return (0);
		}
			ft_strdel(&home);
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

static int	init_struct_variable(t_ab *autocomp, t_cap *tcap)
{
	autocomp->state = 0;
	autocomp->pos = 0;
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
	g_shell->copy_cut->state = 0;
	g_shell->copy_cut->from = -1;
	g_shell->copy_cut->to = -1;
	g_shell->copy_cut->type = -1;
	g_shell->ctrl_r->state = 0;
	g_shell->ctrl_r->index = 0;
	g_shell->ctrl_r->not_found = 0;
	ft_bzero(g_shell->copy_cut->copied, BUFFSIZE);
	ft_bzero(g_shell->ctrl_r->data, BUFFSIZE);
	g_shell->env_tmp = g_shell->env;
	g_shell->intern_tmp = g_shell->intern;
	return (1);
}

int			init_struct(char **env)
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
	if (!~tcgetattr(0, g_shell->term_backup) || !~tcgetattr(0, g_shell->term))
		return (0);
	if (!(g_shell->env = dup_env(env)) || !g_shell->tcap || !g_shell->history ||
		!g_shell->autocomp || !g_shell->copy_cut)
		return (0);
	if (!init_termcap(g_shell->tcap) || !init_history(g_shell->history) ||
					!init_struct_variable(g_shell->autocomp, g_shell->tcap))
		return (0);
	if (tcsetattr(0, TCSADRAIN, g_shell->term) == -1)
		return (0);
	g_shell->term->c_lflag &= ~(ICANON | ECHO);
	g_shell->term->c_cc[VMIN] = 1;
	g_shell->term->c_cc[VTIME] = 0;
	return (1);
}
