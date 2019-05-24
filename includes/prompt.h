/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 07:12:40 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/24 17:24:36 by midrissi         ###   ########.fr       */
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
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# define PROMPT1 				"\x1b[0m\x1b[32m\x1b[1m➜  \x1b[0m"
# define PROMPT1_ERR 				"\x1b[0m\x1b[31m\x1b[1m➜  \x1b[0m"
# define PROMPT2 				"\x1b[36m\x1b[1m%s \x1b[0m"
# define PROMPT3 			"\x1b[1m\x1b[34mgit:(\x1b[31m%s\x1b[34m) \x1b[0m"
# define PROMPT4 				"\x1b[1m\x1b[31m%s\x1b[0m\x1b[33m\x1b[1m ✗ \x1b[0m"
# define DEFAULT_HISTORY_NAME	".21sh_history"
# define DEFAULT_ENV_FILE_NAME	".21sh_env"
# define DEFAULT_PROMPT_COLOR	"\x1b[37m"
# define BUFFSIZE				4096
# define ARROW_CODE1			27
# define ARROW_CODE2			91
# define UP						65
# define DOWN					66
# define RIGHT					67
# define LEFT					68
# define SHIFT_CODE1			27
# define SHIFT_CODE2			91
# define SHIFT_CODE3			49
# define ARROW_CODE3			59
# define ARROW_CODE4			50
# define SHIFT_UP				75
# define SHIFT_DOWN				76
# define SHIFT_RIGHT			77
# define SHIFT_LEFT				78
# define BACKSPACE				127
# define ENTER					10
# define CTRL_R					18
# define CTRL_D					4
# define TAB					9
# define HOME_END1				27
# define HOME_END2				91
# define HOME					72
# define END					70
# define MAX_HISTORY_LENGHT		4096
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
	char		*carriage;
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
	char					*file_name;
	int						position;
	int						match[BUFFSIZE];
	char					*data[MAX_HISTORY_LENGHT];
}				t_history;

extern t_event g_arrow_event[];
extern t_event g_key_event[];

/*
**	ARROW_EVENTS.C
*/

int		arrow_up_event(t_cap *tcap);
int		arrow_down_event(t_cap *tcap);
int		arrow_right_event(t_cap *tcap);
int		arrow_left_event(t_cap *tcap);
void	ft_clear_replace(t_cap *tcap);

/*
**	SHIFT_ARROW_EVENTS.C
*/

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
int		ctrl_d_event(t_cap *tcap);

/*
**	HOME_END_EVENTS.C
*/

int		home_event(t_cap *tcap);
int		end_event(t_cap *tcap);

/*
**	VAR.C
*/

int		read_var(char **var);
char	*get_string_var(char *string, char **var);
int		get_int_var(char *string, char **var);

/*
**	READER.C
*/

int		read_buffer(char *buffer, t_cap *tcap);
void	ft_clear_all_lines(t_cap *tcap);

/*
** PROMPT_PREFIX.c
*/

void		print_prompt_prefix(void);

/*
**	OTHERS.C
*/

int		ft_put_termcaps(int c);
char	**dup_env(char **env);
char	*correct(char *string, char **possible, int *difference);
char	*get_git_status(void);

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
** MOVE.C
*/

void	ft_replace_cursor(t_cap *tcap);
int		ft_left(t_cap *tcap);
int		ft_right(t_cap *tcap);
int		ft_up(t_cap *tcap);
int		ft_down(t_cap *tcap);

/*
**	HISTORY.C
*/

int		write_history(char *string, t_history *history);
int		add_cmd_to_history(char *string, t_history *history);
int		debug_history(t_history *history);
int		read_history(t_history *history);

/*
**PUSH.c
*/

int		ft_add_n_char(char buff[4], int pos, int len, t_cap *tcap);
int		ft_insert(char buff[4], t_cap *tcap);
int		ft_delete_n_char(t_cap *tcap, int pos, int len);
int		ft_delete_back(t_cap *tcap);
void	ft_clean_buff(t_cap *tcap);

/*
**INIT_STRUCT.c
*/

int		init_struct(t_term *trm, char **env);

/*
**	MAIN.C
*/

int		wcharlen(char nb);
char	*read_line(t_cap *tcap);

#endif
