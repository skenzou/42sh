/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:27:48 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/09 07:01:49 by aben-azz         ###   ########.fr       */
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

int	read_custom_env(void)
{
	char		*str;
	int			i;
	int			fd;
	char		env_file[BUFFSIZE];
	int			userlen;

	i = 0;
	userlen = ft_strlen(getenv("USER"));
	ft_strcpy(env_file, "/Users/");
	ft_strcpy(env_file + 7, getenv("USER"));
	ft_strcpy(env_file + 7 + userlen, "/");
	ft_strcpy(env_file + 7 + userlen + 1, DEFAULT_ENV_FILE_NAME);
	env_file[8 + userlen + ft_strlen(DEFAULT_ENV_FILE_NAME)] = '\0';
	fd = open(env_file, O_RDONLY);
	ft_printf("fd file: %s %d\n", env_file, fd);
	if (fd > 0)
	{
		while (get_next_line(fd, &str, '\n') > 0)
		{
			ft_printf("ligne: %d |%s|\n", i, str);
			i++;
		}
	}
	close(fd);
	return (1);
}

int				main(int ac, char **av, char **env)
{
	t_term	term;
	char	buffer[4];

	(void)ac;
	(void)av;
	read_custom_env();
	if (!(tgetent(NULL, getenv("TERM"))) || !init_struct(&term, env))
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
