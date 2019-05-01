/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:06:21 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/01 19:53:58 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H
# include <term.h>
# include <termios.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <unistd.h>
# include "libft.h"
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# define PREFIX "\x1b[32m➜ \x1b[0m\x1b[37m\x1b[1m"
# define SUFFIX "%s\x1b[0m \x1b[1m\x1b[31m%s\x1b[0m\x1b[32m> \x1b[0m"
# define HISTORY_FILE_NAME	"/Users/aben-azz/.21sh_history.log"
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
# define DEBUG_LOG		1
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
typedef struct	s_history
{
	int						len;
	int						read;
	char					*history[MAX_HISTORY_LENGHT];
}				t_history;
extern t_arrow_event g_arrow_event[];
extern t_key_event g_key_event[];

extern t_history *g_history;
/*
**	ARROW_EVENTS.C
*/
int		arrow_up_event(t_curs *curseur);
int		arrow_down_event(t_curs *curseur);
int		arrow_right_event(t_curs *curseur);
int		arrow_left_event(t_curs *curseur);
int		shift_arrow_up_event(t_curs *curseur);
int		shift_arrow_down_event(t_curs *curseur);
int		shift_arrow_right_event(t_curs *curseur);
int		shift_arrow_left_event(t_curs *curseur);
/*
**	KEY_EVENTS.C
*/
int		enter_event(t_curs *curseur, char *command);
int		backspace_event(t_curs *curseur, char *command);
int		ctrl_r_event(t_curs *curseur, char *command);
int		tab_event(t_curs *curseur, char *command);
int		home_event(t_curs *curseur, char *command);
int		end_event(t_curs *curseur, char *command);
int		ctrl_d_event(t_curs *curseur, char *command);
/*
**	READER.C
*/
int		read_buffer(char buffer[4], t_curs *curseur, char *cmd, int unicode);
/*
**	OTHERS.C
*/
int		ft_put_termcaps(int c);
void	display_prompt(void);

/*
**	SIGNAL_HANDLER.C
*/
void	sigint_handler(int sig);
void	sigwinch_handler(int sig);

/*
**	READ_KEY.C
*/
int		is_key(char key[3]);
int		read_key(char buffer, t_curs *curseur, char *c);
/*
**	READ_ARROW.C
*/

char	is_shift_arrow(char key[4]);
int		is_arrow(char key[4]);
int		read_arrow(char buffer, t_curs *curseur);
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
void	display_prompt(void);
int		wcharlen(char nb);

/*
** MIMISHELL.C
*/

int		find_built(char **argv);
int		ft_echo(char **argv);
int		ft_env(char **argv);
int		change_dir(char *path, int print_path);
int		ft_cd(char **argv);
void	signal_handler_command(int sig);
int		quick_cd(char **cmd);
int		set_env(char *key, char *value);
int		ft_setenv(char **argv);
char	**realloc_env(int new_size, int exception);
int		ft_unsetenv(char **argv);
int		ft_exit(char **argv);
void	display_prompt_prefix(void);
int		env_len(char **env);
void	init_env(char **env);
char	*get_env(char *name);
int		get_env_index(char *name);
int		execute(char **cmd, int dir);
int		exec_valid_command(char **argv, int m);
int		is_expansion_printable(char *s, int dollar_index, int i);
char	*get_expansion(char *string, char *act_env, int length);
char	*expansion_dollar(char *string);
int		handler(char *string);
#endif
