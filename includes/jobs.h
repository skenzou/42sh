/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 00:52:53 by tlechien          #+#    #+#             */
/*   Updated: 2019/06/26 02:04:46 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOBS_H
# define JOBS_H

# include "shell.h"
# define ID_RUN			0
# define ID_DONE		SIGHUP
# define ID_SUSP		SIGTSTP
# define ID_CONT		SIGCONT
# define ID_TERM		SIGTERM
# define ID_PIPE		g_pid_table->is_pipe
# define ID_PRIORITY	g_pid_table->priority
# define ID_PID			g_pid_table->pid
# define ID_INDEX		g_pid_table->index
# define ID_STATUS		g_pid_table->status
# define ID_EXEC		g_pid_table->exec
# define ID_LEFT		g_pid_table->left
# define ID_RIGHT		g_pid_table->right
# define ID_PREV		g_pid_table->prev
# define OPT_L			1
# define OPT_P			2
# define S_SIZE			27
# define S_TERM			0
# define S_ABN			1
# define S_IGN			2
# define S_STOP			3
# define S_CONT			4

typedef struct		s_child{
	int				is_pipe;
	int				index;
	pid_t			pid;
	int				priority;
	int				status;
	char			*exec;
	struct s_child	*left;
	struct s_child	*right;
	struct s_child	*prev;
}					t_child;

typedef struct		s_signal
{
	int				sig;
	int				action;
	char			*handler;
	char			*status;
}					t_signal;

extern	t_child		*g_pid_table;
extern	t_signal	*g_signal[];
/*
** BG_BUILTIN.C
*/
int					bg_builtin(int ac, char **cmd);
int					bg_resume(t_child **node);
/*
** FG_BUILTIN.C
*/
int					fg_builtin(int ac, char **cmd);
/*
** FG_UTILS.C
*/
int					search_index(t_child **node, char *str_index);
int					search_pid(t_child **node, char *str_pid, pid_t pid);
int					search_priority(t_child **node);
int					search_status(t_child **node, int status);
int					search_process(t_child **node, char *p_name);
/*
** FT_FORK.C
*/
int					ft_fork(char **cmd, char **env);
int					ft_fork_amper(char **cmd, char **env);
int					ft_fork_builtin(t_builtin *builtin, int ac, char **cmd);
int					ft_waitprocess(pid_t pid, char **cmd, char *handler,
					char *stat);
/*
** JOB_UTILS.C
*/
int					add_pid(int is_pipe, int pid, char **cmd, int status);
int					add_amperpipe(int pid_origin, int pid, char *cmd,
																	int status);
int					init_pid(void);
int					update_priority(int first, t_child *tmp_f, t_child *tmp_s);
int					kill_pids(void);
int					remove_pid(t_child *node);
char				*full_cmd(char **cmd);
/*
** JOBS_BUILTIN.C
*/
int					update_pid_table(void);
int					display_pid_status(t_child *node, char option);
int					jobs_builtin(int ac, char **cmd);
/*
** JOBS_PIPES.C
*/
int					update_amperpipe(t_child *head);
int					display_amperpipe(t_child *node, char option);
int					check_remove_pids(void);
/*
** SIGNALS.C
*/
void				sigchld_handler(int sig);
void				init_signal(void);
int					s_get_values(int status, int *action, char **handler,
																char **stat);
void				s_child_handler(int status, t_child *node);
void				resetsign(void);
/*
**	SIGNAL_HANDLER.C
*/
void				sigfork(int sig);
void				sigint_handler(int sig);
void				sigwinch_handler(int sig);
void				sigtstp_handler(int sig);
void				sigtstp_dflhandler(int sig);
/*
** SIGNAL_UTILS.C
*/

void				sigint_inhib_handler(int sig);
int					waitabit(int min, int nsec);
int					get_nb_len(long long nb);

#endif
