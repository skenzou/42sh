/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:27:48 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/02 16:15:45 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdio.h>

t_event g_arrow_event[] = {
	{UP, &arrow_up_event},
	{DOWN, &arrow_down_event},
	{RIGHT, &arrow_right_event},
	{LEFT, &arrow_left_event},
	{SHIFT_UP, &shift_arrow_up_event},
	{SHIFT_DOWN, &shift_arrow_down_event},
	{SHIFT_RIGHT, &shift_arrow_right_event},
	{SHIFT_LEFT, &shift_arrow_left_event},
	{SHIFT_TAB, &shift_tab_event}
};
t_event g_key_event[] = {
	{ENTER, &enter_event},
	{BACKSPACE, &backspace_event},
	{CTRL_R, &ctrl_r_event},
	{CTRL_D, &ctrl_d_event},
	{TAB, &tab_event},
	{HOME, &home_event},
	{END, &end_event},
	{SPACE, &space_event}
};
t_event		g_alt_event[] = {
	{COPY, &ft_copy},
	{CUT, &ft_cut},
	{PASTE, &ft_paste}
};

t_shell		*g_shell;
t_child		*g_pid_table;
char		**g_aliases;

char				*clean_before_return(t_cap *tcap)
{
	tcsetattr(0, TCSADRAIN, g_shell->term_backup);
	ft_printf("\x1b[0m");
	tcap->cursx = tcap->prompt_len;
	tcap->cursy = 0;
	tcap->command[tcap->char_len] = '\n';
	if (add_cmd_to_history(tcap->command, g_shell->history) == -1)
		return (NULL);
	tcap->char_len = 0;
	ft_printf("\n");
	return (tcap->command);
}

static void			check_flags(char **av, int ac)
{
	int i;

	i = 0;
	while (++i < ac)
		if (!ft_strcmp(av[i], "-ast"))
			g_shell->print_flags |= PRINT_AST;
		else if (!ft_strcmp(av[i], "-lexer"))
			g_shell->print_flags |= PRINT_LEXER;
		else if (!ft_strcmp(av[i], "-redir"))
			g_shell->print_flags |= PRINT_REDIR;
}

static int			init_fd_table(void)
{
	int i;

	i = -1;
	while (++i < 10)
		if ((g_shell->fd_table[i] = dup(i)) == -1)
			return (-1);
	return (0);
}

int					main(int ac, char **av, char **env)
{
	char	*string;

	if (!(tgetent(NULL, get_key_value("TERM", env))) || !init_struct(env) ||
			init_pid() || init_alias(1) || init_fd_table())
		return (-1);
	ft_bzero((void *)g_shell->hash_table, TABLE_SIZE);
	if (ac > 1)
		check_flags(av, ac);
	while ("42sh")
	{
		init_signal();
		update_pid_table();
		if (!(string = read_line(g_shell->tcap)))
			return (-1);
		if (!handler(string))
			return (-1);
		update_pid_table();
	}
	save_alias(1);
	kill_pids();
	return (0);
}
