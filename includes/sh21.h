/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:06:21 by aben-azz          #+#    #+#             */
/*   Updated: 2019/04/28 15:45:07 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H
# include <term.h>
# include <termios.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "libft.h"
# define ARROW_UP		4283163
# define ARROW_DOWN		4348699
# define ARROW_RIGHT	4414235
# define ARROW_LEFT		4479771
# define BACKSPACE		127
# define ENTER			10
# define BUFFSIZE		4096
# define UNUSED			0

typedef struct termios	t_term;
typedef struct	s_curs
{
	unsigned int			x;
	unsigned int			y;
	unsigned int			last;
}				t_curs;
typedef struct	s_arrow_event
{
	int						key;
	int						(*function)(t_curs *curseur);
}				t_arrow_event;
typedef struct	s_key_event
{
	int						key;
	int						(*function)(t_curs *curseur, char *command);
}				t_key_event;
extern t_arrow_event g_arrow_event[];
extern t_key_event g_key_event[];
/*
**	ARROW_EVENTS.C
*/
int		arrow_up_event(t_curs *curseur);
int		arrow_down_event(t_curs *curseur);
int		arrow_right_event(t_curs *curseur);
int		arrow_left_event(t_curs *curseur);
/*
**	KEY_EVENTS.C
*/
int		enter_event(t_curs *curseur, char *command);
int		backspace_event(t_curs *curseur, char *command);
/*
**	READER.C
*/
int		read_buffer(int buffer, t_curs *curseur, char *command);
/*
**	OTHERS.C
*/
int		ft_put_termcaps(int c);
void	display_prompt(void);

/*
**	SIGNAL_HANDLER.C
*/
void	sig_handler(int sig);
/*
**	MAIN.C
*/

int		fputchar(int c);
int		exec_command(char *command);
void	display_prompt(void);
#endif
