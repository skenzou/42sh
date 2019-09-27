/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 00:52:53 by tlechien          #+#    #+#             */
/*   Updated: 2019/09/27 00:51:50 by tlechien         ###   ########.fr       */
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

typedef struct		s_child
{
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
int					is_branch_stp(t_child *head);
int					bg_resume(t_child *node);
int					bg_builtin(int ac, char **cmd);
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
** FG_UTILS2.C
*/
int					search_prio(t_child **node, char *str_index);
/*
** FT_FORK.C
*/
int					ft_waitprocess(pid_t pid, char **cmd, char *handler,
					char *stat);
int					ft_fork_amper(char **cmd, char **env);
int					ft_fork_builtin(t_builtin *builtin, int ac, char **cmd);
int					ft_fork(char **cmd, char **env);
/*
** JOBS_BUILTIN.C
*/
int					jobs_builtin(int ac, char **cmd);
/*
** JOBS_INIT.C
*/
int					init_pid(void);
int					add_pid(int is_pipe, int pid, char **cmd, int status);
int					add_amperpipe(int pid_origin, int pid, char *cmd,
					int status);
/*
** JOBS_PIPES.C
*/
t_child				*get_head(t_child *node);
int					update_amperpipe(t_child *head);
int					check_remove_pids(void);
int					display_amperpipe(t_child *node, char option,
					char *stat, char current);
/*
** JOBS_UPDATES.C
*/
int					display_pid_status(t_child *node, char option);
int					update_priority(int first, t_child *tmp_f, t_child *tmp_s);
int					update_pid_table(void);
/*
** JOB_UTILS.C
*/
int					kill_pids(void);
int					remove_pid(t_child *node);
char				*full_cmd(char **cmd);
/*
**	SIGNAL_HANDLER.C
*/
void				sigint_handler(int sig);
void				sigfork(int sig);
void				sigwinch_handler(int sig);
void				sigtstp_dflhandler(int sig);
/*
** SIGNAL_UTILS.C
*/
void				sigtstp_handler(int sig);
void				sigquit_dflhandler(int sig);
void				init_signal(void);
int					get_nb_len(long long nb);
int					waitabit(int min, int nsec);
/*
** SIGNALS.C
*/
void				s_child_handler(int status, t_child *node);
int					s_get_values(int status, int *action, char **handler,
					char **stat);
void				sigchld_updater(int sig);
void				sigchld_handler(int sig);
void				resetsign(void);

#endif
