/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:27:48 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/12 09:17:27 by aben-azz         ###   ########.fr       */
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

int		debug(void)
{
	int fd = open("./log.log", O_RDWR | O_APPEND, 0666);

	return (fd);

}
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
	//tcap->command[ft_strlen(tcap->command) - 1] = '\0';
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

int				handler(char *string)
{
	if (!ft_strcmp(string, "history\n"))
		debug_history(g_shell->history);
	else
		ft_printf("command: %s", string);
	g_shell->history->position = -1;
	return (1);
}

int				main(int ac, char **av, char **env)
{
	t_term	term;
	char	*string;

	(void)ac;
	(void)av;
	if (!(tgetent(NULL, getenv("TERM"))) || !init_struct(&term, env))
		return (-1);
	while ("21sh")
	{
		if ((string = read_line(g_shell->tcap)) == NULL)
			return (-1);
		if (handler(string) == 0)
			return (-1);
	}
	return (0);
}
