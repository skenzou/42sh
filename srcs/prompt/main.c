/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:27:48 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/25 07:24:43 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
t_event g_alt_event[] = {
	{COPY, &ft_copy},
	{CUT, &ft_cut},
	{PASTE, &ft_paste}
};

t_shell *g_shell;
t_child *g_pid_table;
char	**g_aliases;

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

int		debug(void)
{
	int fd;

	return (fd = open("log.log", O_RDWR | O_APPEND | O_CREAT, 0666));
}

char	*clean_before_return(t_cap *tcap)
{
	tcsetattr(0, TCSADRAIN, g_shell->term_backup);
	ft_printf("\x1b[0m");
	tcap->cursx = tcap->prompt_len;
	tcap->cursy = 0;
	tcap->command[tcap->char_len] = '\n';
	if (add_cmd_to_history(tcap->command, g_shell->history) == -1)
		return (NULL);
	tcap->char_len = 0;
	//tputs(tcap->clr_all_line, 1, ft_put_termcaps);
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
	fflush(stdout);
	while (g_shell->dprompt == 0)
	{
		g_shell->dprompt = 1;
		waitabit(0, 8000000);
	}
	print_prompt_prefix();
	if (tcap->overflow)
	{
		ft_insert(tcap->carry, tcap);
		ft_bzero(tcap->carry, 2);
		tcap->overflow = 0;
	}
	while ("42sh")
	{
		ft_bzero(buffer, 4);
		tcsetattr(0, TCSADRAIN, g_shell->term);
		read(0, &buffer, 3);
		if ((ret = read_buffer(buffer, tcap)) == -2)
			return (clean_before_return(tcap));
		else if (!ret)
		{
			tcsetattr(0, TCSADRAIN, g_shell->term_backup);
			return (NULL);
		}
	}
}

static void	check_flags(char **av, int ac)
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

static int	init_fd_table(void)
{
	int i;

	i = -1;
	while (++i < 10)
		if ((g_shell->fd_table[i] = dup(i)) == -1)
			return (-1);
	return (0);
}

int				main(int ac, char **av, const char **env)
{
	char	*string;

	if (!(tgetent(NULL, getenv("TERM"))) || !init_struct(env) ||
			init_pid() || init_alias(1) || init_fd_table())
		return (-1);
	ft_bzero((void *)g_shell->hash_table, TABLE_SIZE);
	if (ac > 1)
		check_flags(av, ac);
	g_shell->dprompt = 1;
	while ("42sh")
	{
		init_signal();
		update_pid_table();
		if (!(string = read_line(g_shell->tcap)))
			return (-1);
		if (!handler(string))
			return (-1);
	}
	save_alias(1);
	kill_pids();
	return (0);
}
