/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 07:12:40 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/12 00:57:27 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H
# include <term.h>
# include <termios.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <unistd.h>
# include "../libft/includes/libft.h"
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
#include <sys/ioctl.h>
# define PREFIX "\x1b[32m➜ \x1b[0m\x1b[37m\x1b[1m"
# define SUFFIX "%s\x1b[0m \x1b[1m\x1b[31m%s\x1b[0m\x1b[32m> \x1b[0m"
# define HISTORY_FILE_NAME	"/Users/midrissi/.21sh_history.log"
# define BUFFSIZE					4096
# define ARROW_CODE1				27
# define ARROW_CODE2				91
# define UP							65
# define DOWN						66
# define RIGHT						67
# define LEFT						68
# define SHIFT_CODE1				27
# define SHIFT_CODE2				91
# define SHIFT_CODE3				49
# define ARROW_CODE3				59
# define ARROW_CODE4				50
# define SHIFT_UP					75
# define SHIFT_DOWN					76
# define SHIFT_RIGHT				77
# define SHIFT_LEFT					78
# define BACKSPACE					127
# define ENTER						10
# define CTRL_R						18
# define CTRL_D						30
# define TAB						9
# define HOME_END1					27
# define HOME_END2					91
# define HOME						72
# define END						70
# define MAX_HISTORY_LENGHT			4096


# define UNUSED			0
# define DEBUG_LOG		0
typedef struct	s_data
{
	int				xd;
	char			**argv;
}				t_data;
char					**g_env;
typedef struct stat	t_stat;
typedef struct termios	t_term;
typedef struct	s_built
{
	char			*builtin;
	int				(*function)(char **argv);
}				t_built;
typedef struct	s_cap
{
	char		*up;
	char		*down;
	char		*right;
	char		*left;
	char		*chariot;
	char		*clr_curr_line;
	char		*clr_all_line;
	char		*place_cursor;
	char		*sound;
	int			cursx;
	int			cursx_max;
	int			cursy;
	int			prompt_len;
	int			char_len;
	char		command[BUFFSIZE];
	char		*prompt;
}				t_cap;
typedef struct	s_event
{
	int						key;
	int						(*function)(t_cap *tcap);
}				t_event;

typedef struct	s_history
{
	int						len;
	int						read;
	char					*data[MAX_HISTORY_LENGHT];
}				t_history;
typedef struct	s_shell
{
	t_cap		*tcap;
	char		**env;
	t_history	*history;
}				t_shell;
extern t_event g_arrow_event[];
extern t_event g_key_event[];
extern t_shell *g_shell;
/*
**	ARROW_EVENTS.C
*/
int		arrow_up_event(t_cap *tcap);
int		arrow_down_event(t_cap *tcap);
int		arrow_right_event(t_cap *tcap);
int		arrow_left_event(t_cap *tcap);
int		shift_arrow_up_event(t_cap *tcap);
int		shift_arrow_down_event(t_cap *tcap);
int		shift_arrow_right_event(t_cap *tcap);
int		shift_arrow_left_event(t_cap *tcap);
/*
**	KEY_EVENTS.C
*/
int		enter_event(t_cap *tcap);
int		backspace_event(t_cap *tcap);
int		ctrl_r_event(t_cap *tcap);
int		tab_event(t_cap *tcap);
int		home_event(t_cap *tcap);
int		end_event(t_cap *tcap);
int		ctrl_d_event(t_cap *tcap);
/*
**	READER.C
*/
int		read_buffer(char buffer[4], t_cap *tcap);
void	add_to_cmd(char buffer[4], int len);
void	ft_delete_n_char(t_cap *tcap, int pos, int len);
void	ft_delete_back(t_cap *tcap);
/*
**	OTHERS.C
*/
int		ft_put_termcaps(int c);
void	ft_move_right(t_cap *tcap);
void	ft_move_left(t_cap *tcap);
/*
**	SIGNAL_HANDLER.C
*/
void	sigint_handler(int sig);
void	sigwinch_handler(int sig);

/*
**	READ_KEY.C
*/
int		is_key(char key[3]);
int		read_key(char buffer, t_cap *tcap);
/*
**	READ_ARROW.C
*/

char	is_shift_arrow(char key[4]);
int		is_arrow(char key[4]);
int		read_arrow(char buffer, t_cap *tcap);
/*
**	HISTORY.C
*/

int		write_history(char *string);
int		init_history(void);
int		add_cmd_to_history(char *string);
int		debug_history(void);
int		read_history(void);
/*
**	MAIN.C
*/

int		fputchar(int c);
int		exec_command(char *command);
void	display_prompt_prefix(void);
int		wcharlen(char nb);

#endif
