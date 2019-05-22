/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:27:48 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/21 16:13:26 by midrissi         ###   ########.fr       */
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

t_child *g_pid_table;

int				wcharlen(char nb)
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

char	*clean_before_return(t_cap *tcap)
{
	ft_printf("\x1b[0m");
	tcap->cursx = tcap->prompt_len;
	tcap->cursy = 0;
	if (tcap->char_len >= BUFFSIZE - 1)
	{
		tcap->command[BUFFSIZE - 2] = '\n';
		tcap->command[BUFFSIZE - 1] = '\0';
	}
	else
		tcap->command[tcap->char_len] = '\n';
	if (add_cmd_to_history(tcap->command, g_shell->history) == -1)
		return (NULL);
	tcap->char_len = 0;
	ft_printf("\n");
	return (tcap->command);
}

char	*read_line(t_cap *tcap)
{
	char	buffer[4];
	int		ret;

	ret = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGWINCH, sigwinch_handler);
	ft_bzero(buffer, 4);
	ft_bzero(tcap->command, BUFFSIZE);
	print_prompt_prefix();
	while ("21sh")
	{
		ft_bzero(buffer, 4);
		read(0, &buffer, 3);
		if ((ret = read_buffer(buffer, tcap)) == -2)
			return (clean_before_return(tcap));
		else if (!ret)
			return (NULL);
	}
}

static void check_flags(char **av, int ac)
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

static void init_fd_table()
{
	int i;

	i = -1;
	while (++i < 10)
		g_shell->fd_table[i] = dup(i);
}

int				main(int ac, char **av, char **env)
{
	t_term	term;
	char	*string;

	if (!(tgetent(NULL, getenv("TERM"))) || !init_struct(&term, env) ||
			init_pid())
		return (-1);
	if (ac > 1)
		check_flags(av, ac);
	init_fd_table();
	while ("21sh")
	{
		if ((string = read_line(g_shell->tcap)) == NULL)
			return (-1);
		if (handler(string) == 0)
			return (-1);
	}
	return (0);
}
