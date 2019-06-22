/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 00:40:57 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/22 21:19:22 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

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
# define ALIAS_FILE		".21sh_alias"
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

typedef struct		s_hash_entry
{
	unsigned char	*data;
	unsigned char	*key;
	size_t			hit;
}					t_hash_entry;

typedef struct		s_pipe
{
	int				pipe[2];
	char			job;
	int				pid;
}					t_pipe;

typedef struct		s_builtin
{
	char			*cmd;
	int				(*function)(int ac, char **av);
}					t_builtin;

typedef struct		s_signal
{
	int				sig;
	int				action;
	char			*handler;
	char			*status;
}					t_signal;

extern	t_child		*g_pid_table;
extern	const char	*g_status[];
extern	const char	*g_reserved[];
extern	char		**g_aliases;
extern	t_signal	*g_signal[];

/*
** ALIAS_BUILTIN.C
*/
int					alias_builtin(int ac, char **cmd);
int					unalias_builtin(int ac, char **cmd);
/*
** ALIAS_INIT.C
*/
int					init_alias(int file);
char				*parse_aliases(char *line, char *origin, char *prev);
char				*substitute_alias(char **origin, char *line, int size);
int					save_alias(int save);
/*
** ALIAS_UTILS.C
*/
int					ft_arraylen(char **array);
int					display_alias(void);
int					is_reserved(char *key);
int					is_alias(char *key);
char				*get_alias(char *key);
/*
** BG_BUILTIN.C
*/
int					bg_builtin(int ac, char **cmd);
int					bg_resume(t_child **node);
/*
** BIN_HASH.C
*/
t_hash_entry		*hash_search(unsigned char *key);
t_hash_entry		*hash_insert(unsigned char *key, char **env);
int					hash_table(char **str, char **env);
/*
** CD_BUILTIN_CHDIR.C
*/
int					change_dir(char *path, char flag);
/*
** CD_BUILTIN_UTILS.C
*/
char				*get_oldpwd(char **env);
int					cd_err(int err_id, char *dest);
char				*join_path(char *path, char *dir);
char				*test_full_paths(char *entry, char *dir);
char				*get_path(char *dir);
/*
** CD_BUILTIN.C
*/
int					cd_builtin(int argc, char **argv);
/*
** ECHO_BUILTIN.C
*/
int					echo_builtin(int argc, char **argv);
/*
** ENV_BUILTIN.C
*/
int					env_builtin(int ac, char **av);
/*
** ERR_HANDLER.C
*/
void				err_handler(int err_id, char *str);
void				redir_errors(int err_id, char *dest, int fd);
int					err_display(char *start, char *mid, char *end);
/*
** EXECUTOR.C
*/
void				ft_execute_ast(t_ast *root);
void				ft_post_exec(t_ast *root);
/*
** EXIT_BUILTIN.C
*/
int					exit_builtin(int ac, char **av);
/*
** EXPANSIONS.C
*/
void				ft_expand_one(char **ptr);
void				ft_expand(char **args);
/*
** EXPORT_BUILTIN.C
*/
int					export_builtin(int ac, char **av);
/*
** EXPORT_BUILTIN2.C
*/
int					export_options(int ac, char **av);
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
int					ft_waitprocess(pid_t pid, char **cmd);
/*
** GET_OPTIONS.C
*/
int					ft_flags(char c, char *flags, char *opt);
int					get_options(char *flags, char *opt, char *str,
																int (*usage)());
int					params(char **flags, int ac, char **av, int (*usage)());
/*
** HANDLE_HDOC.C
*/
void				handle_hdoc(t_list *redir);
/*
** HANDLE_PIPE.C
*/
void				handle_pipe(t_ast *root, char job);
/*
** HANDLE_REDIR.C
*/
char				**handle_redir();
/*
** HASH_BUILTIN.C
*/
int					hash_builtin(int ac, char **av);
/*
** JOB_UTILS.C
*/
int					add_pid(int is_pipe, int pid, char **cmd, int status);
int					add_amperpipe(int pid_origin, int pid, char *cmd,
																	int status);
int					init_pid(void);
int					update_priority(int first);
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
** PARAM_EXPANSION.C
*/
void				param_expansion(char **ptr);
/*
** PARSE_PIPES.C
*/
void				parse_pipes(t_ast *root, t_pipe **pipes, size_t nbpipes);
/*
** PRE_EXEC.C
*/
t_builtin			*get_builtin(char *cmd);
int					ft_pre_execution(char ***args, int redir,
														t_builtin **builtin);
/*
** QUOTE_EXPANSION.C
*/
void				remove_quote(char **str);
/*
** REDIR_UTILS.C
*/
void				print_redir(t_list *redir);
char				**get_curr_cmd(t_list *redir);
void				go_to_next_cmd(t_list *redir);
void				redir_delone(void *data, size_t size);
int					open_file(t_redir *redir);
/*
** SET_BUILTIN.C
*/
int					set_builtin();
/*
** SETENV_BUILTIN.C
*/
int					setenv_builtin(int ac, char **av);
int					get_indexof_key(char *key, char **env);
void				ft_setenv(char *key, char *value, char ***env);
/*
** SHELL_VAR.C
*/
void				handle_intern_var(char **args);
/*
** SIGNAL_UTILS.C
*/
int					waitabit(int min, int nsec);
int					get_nb_len(long long nb);
/*
** SIGNALS.C
*/
void				sigchld_handler();
void				init_signal(void);
int					s_get_values(int status, int *action, char **handler,
																char **stat);
void				s_child_handler(int status, t_child *node);
void				resetsign(void);
/*
** TAB_UTILS.C
*/
char				**dup_tab(char **tab, size_t size);
void				remove_n_first_entries(char **old, int n);
char				**join_2tab(char **curr, char **next, size_t curr_size,
															size_t next_size);
char				**realloc_new_tab(char *needle, char **old, size_t size);
/*
** TEST_BUILTIN.C
*/
int					test_builtin(int ac, char **args);
/*
** TILDE_EXPANSION.C
*/
void				tilde_expansion(char **ptr);
/*
** TOOLS.C
*/
char				*get_key_value(char *key, char **array);
int					check_file(char *path);
void				print_split(char **split);
int					is_path(char *str);
int					check_dir(char *path);
/*
** TYPE_BUILTIN.C
*/
int					type_builtin(int ac, char **args);
/*
** UNSET_BUILTIN.C
*/
int					unset_builtin(int ac, char **av);
/*
** UNSETENV_BUILTIN.C
*/
char				**removekey(char *key, int keylen, const char **env);
int					unsetenv_builtin(int ac, char **av);
/*
** UTILS2.C
*/
int					is_special_char(char c);
void				close_fd();
int					is_key_valid(char *key);

#endif
