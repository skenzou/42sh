/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 07:12:40 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/30 20:34:17 by midrissi         ###   ########.fr       */
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
# include <dirent.h>
# include <curses.h>
# include <sys/ioctl.h>
# define PROMPT1 				"\x1b[0m\x1b[32m\x1b[1m➜  \x1b[0m"
# define PROMPT1_ERR 				"\x1b[0m\x1b[31m\x1b[1m➜  \x1b[0m"
# define PROMPT2 				"\x1b[36m\x1b[1m%s \x1b[0m"
# define PROMPT3 			"\x1b[1m\x1b[34mgit:(\x1b[31m%s\x1b[34m) \x1b[0m"
# define PROMPT4 			"\x1b[1m\x1b[31m%s\x1b[0m\x1b[33m\x1b[1m ✗ \x1b[0m"
# define DEFAULT_HISTORY_NAME	".42sh_history"
# define DEFAULT_ENV_FILE_NAME	".42sh_env"
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
# define ALT_CODE1				27
# define ALT_CODE2				27
# define ALT_CODE3				91
# define ARROW_CODE3			59
# define ARROW_CODE4			50
# define SHIFT_UP				75
# define SHIFT_DOWN				76
# define SHIFT_RIGHT			77
# define SHIFT_LEFT				78
# define BACKSPACE				127
# define SPACE					32
# define ENTER					10
# define CTRL_R					18
# define CTRL_D					4
# define TAB					9
# define SHIFT_TAB				90
# define HOME_END1				27
# define HOME_END2				91
# define HOME					72
# define END					70
# define COPY					0
# define CUT					-120
# define PASTE					-102
# define MAX_HISTORY_LENGHT		4096
# define MAX_PATH		PATH_MAX
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
typedef struct stat			t_stat;
typedef struct dirent		t_dirent;
typedef struct passwd		t_passwd;
typedef struct group		t_group;
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
	char		*save;
	char		*restore;
	int			cursx;
	int			cursx_max;
	int			cursy;
	int			prompt_len;
	int			init_len;
	int			char_len;
	char		command[BUFFSIZE];
	int			overflow;
	char		carry[2];
	char		*prompt;

}				t_cap;

typedef struct				s_cc
{
	int						state;
	int						type;
	int						from;
	int						to;
	char					copied[BUFFSIZE];
}							t_cc;

typedef struct				s_file
{
	t_stat					stats;
	char					*name;
	char					*path;
	char					full_path[MAX_PATH];
}							t_file;

typedef struct	s_event
{
	int						key;
	int						(*function)(t_cap *tcap);
}				t_event;
typedef struct	s_tab
{
	int						state;
	int						pos;
	int						len;
	int						carry;
	int						row;
	int						col;
	int						max_offset;
	char					*match;
	t_file					data[MAX_HISTORY_LENGHT];
}				t_ab;
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
extern t_event g_alt_event[];

/*
**	ARROW_EVENTS.C
*/

int		arrow_up_event(t_cap *tcap);
int		arrow_down_event(t_cap *tcap);
int		arrow_right_event(t_cap *tcap);
int		arrow_left_event(t_cap *tcap);
void	ft_clear_replace(t_cap *tcap);

/*
**	SHIFT_EVENTS.C
*/

int		shift_arrow_up_event(t_cap *tcap);
int		shift_arrow_down_event(t_cap *tcap);
int		shift_arrow_right_event(t_cap *tcap);
int		shift_arrow_left_event(t_cap *tcap);
int		shift_tab_event(t_cap *tcap);

/*
**	KEY_EVENTS.C
*/

int		enter_event(t_cap *tcap);
int		backspace_event(t_cap *tcap);
int		ctrl_r_event(t_cap *tcap);
int		tab_event(t_cap *tcap);
int		ctrl_d_event(t_cap *tcap);
int		space_event(t_cap *tcap);

/*
**	HOME_END_EVENTS.C
*/

int		home_event(t_cap *tcap);
int		end_event(t_cap *tcap);
/*
**	COPY_CUT.C
*/


int		ft_copy(t_cap *tcap);
int		ft_cut(t_cap *tcap);
int		ft_paste(t_cap *tcap);
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
void	sigfork(int sig);
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
**	READ_ALT.C
*/


int		is_alt(char *key);
/*
** MOVE.C
*/

void	ft_replace_cursor(t_cap *tcap);
int		ft_left(t_cap *tcap);
int		ft_right(t_cap *tcap);
int		ft_move(t_cap *tcap, char *string, int n);

/*
**	HISTORY.C
*/

int		write_history(char *string, t_history *history);
int		add_cmd_to_history(char *string, t_history *history);
int		debug_history(t_history *history);
int		read_history(t_history *history);

/*
**HISTO_UP_DOWN.c
*/
int	histo_up(t_cap *tcap, t_history *h);
int	histo_down(t_cap *tcap, t_history *h);

/*
**PUSH.c
*/

int		ft_add_n_char(char *buff, int pos, int len, t_cap *tcap);
int		ft_insert(char *buff, t_cap *tcap);
int		ft_delete_n_char(t_cap *tcap, int pos, int len);
int		ft_delete_back(t_cap *tcap);
void	ft_clean_buff(t_cap *tcap);

/*
**COMPLETION.c
*/
int		ft_tab(t_cap *tcap, t_ab *autocomp);
/*
**INIT_STRUCT.c
*/

int		init_struct(char **env);
int		init_termcap(t_cap *tcap);
/*
**	MAIN.C
*/

int		wcharlen(char nb);
char	*read_line(t_cap *tcap);
int		debug(void);
#endif
