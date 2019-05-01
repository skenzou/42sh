/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:06:21 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/01 16:00:55 by aben-azz         ###   ########.fr       */
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
# define ARROW_CODE1	27
# define ARROW_CODE2	91
# define UP				65
# define DOWN			66
# define RIGHT			67
# define LEFT			68
# define BACKSPACE		127
# define ENTER			10
# define BUFFSIZE		4096
# define UNUSED			0
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
extern t_arrow_event g_arrow_event[];
extern t_key_event g_key_event[];
extern char **g_env;
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
int		read_buffer(char buffer[4], t_curs *curseur, char *command, int unicode);
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
