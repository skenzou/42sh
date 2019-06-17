/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 00:40:57 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/17 17:37:41 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/*
**	## INCLUDES ##
*/

# include "shell.h"

/*
**	## DEFINES ##
*/

# define ID_RUN		0
# define ID_DONE	SIGHUP
# define ID_SUSP	SIGTSTP
# define ID_CONT	SIGCONT
# define ID_TERM	SIGTERM
# define ID_PRIORITY  g_pid_table->priority
# define ID_PID       g_pid_table->pid
# define ID_INDEX     g_pid_table->index
# define ID_STATUS    g_pid_table->status
# define ID_EXEC      g_pid_table->exec
# define ID_NEXT      g_pid_table->next
# define ID_PREV      g_pid_table->prev
# define ALIAS_FILE	".21sh_alias"
# define OPT_L 1
# define OPT_P 2
# define S_SIZE		27
# define S_TERM		0
# define S_ABN		1
# define S_IGN		2
# define S_STOP		3
# define S_CONT		4

/*
**	## STRUCTURES ##
*/

typedef struct s_child t_child;

struct s_child{
	int				index;
	pid_t			pid;
	int				priority;
	int				status;
	char			*exec; //**
	t_child			*next;
	t_child			*prev;
};

typedef struct s_hash_entry
{
	unsigned char	*data;
	unsigned char	*key;
	size_t			hit;
}				t_hash_entry;

typedef struct s_pipe
{
	int			pipe[2];
}				t_pipe;

typedef struct set_builtin
{
	char		*cmd;
	int			(*function)(int ac, char **av);
}				t_builtin;

typedef struct	s_signal
{
	int			sig;
	int			action;
	char		*handler;
	char		*status;
}				t_signal;

extern	t_child		*g_pid_table;
extern	const char	*g_status[];
extern	const char	*g_reserved[];
extern	char		**g_aliases;
extern	t_signal	*s_signal[];

/*
** ## FUNCTIONS ##
*/

void		handle_hdoc(t_list *redir);
int		is_special_char(char c);
void		parse_pipes(t_ast *root, t_pipe **pipes, size_t nbpipes);
int		change_dir(char *path, char flag);
char			*get_oldpwd(char **env);
int				cd_err(int err_id, char *dest);
char			*join_path(char *path, char *dir);
char			*test_full_paths(char *entry, char *dir);
char			*get_path(char *dir);
t_hash_entry	*hash_search(unsigned char* key);
t_hash_entry	*hash_insert(unsigned char *key, char **env);
int		hash_builtin(int ac, char **av);
void		ft_expand_one(char **ptr);
void		redir_errors(int err_id, char *dest, int fd);
int			env_builtin(int ac, char **av);
void		go_to_next_cmd(t_list *redir);
t_builtin	*get_builtin(char *cmd);
// int		get_builtin(char *cmd);
int			test_builtin(int ac, char **args);
int			type_builtin(int ac, char **args);
void		param_expansion(char **ptr);
char		*get_key_value(char *key, char **array);
void   		tilde_expansion(char **ptr);
int			unset_builtin(int ac, char **av);
int			export_builtin(int ac, char **av);
char		**removekey(char *key, int keylen,const char **env);
int			exec_builtin(char **builtin, int id, char ***env);
void		handle_pipe(t_ast *root);
void		redir_delone(void *data, size_t size);
int			ft_fork(char **cmd, char **env);
void		remove_quote(char **str);
int			hash_table(char **str,char **env);
void		expand_and_execute(char **args);
char		**handle_redir();
void		print_redir(t_list *redir);
int			check_file(char *path);
void		ft_execute_ast(t_ast *root);
void		ft_expand(char **args);
int			unsetenv_builtin(int ac, char **av);
int			setenv_builtin(int ac, char **av);
int			get_indexof_key(char *key, char **env);
void		ft_setenv(char *key, char *value, char ***env);
int			echo_builtin(int argc, char **argv);
int			exit_builtin(int ac, char **av);
int			cd_builtin(int argc, char **argv);
void		err_handler(int err_id, char *str);
void		print_split(char **split);
char		**get_curr_cmd(t_list *redir);
int			open_file(t_redir *redir);
int			is_path(char *str);
int			check_dir(char *path);
void 		close_fd();
int			ft_pre_execution(char ***args, int redir, t_builtin **builtin);
void		remove_n_first_entries(char **old, int n);
int			set_builtin();
void		handle_intern_var(char **args);
void		ft_post_exec(t_ast *root);
char		*get_homepath(char **env);
int			is_key_valid(char *key);
int			err_display(char *start, char *mid, char *end);

/*
**	ft_fork.c
*/

int		ft_fork(char **cmd, char **env);
int		ft_fork_amper(char **cmd, char **env);
int		ft_waitprocess(pid_t pid, char **cmd);

/*
**	jobs_builtin.c & dependencies
*/

int		add_pid(int pid, char **cmd, int status);
int		update_pid_table(void);
int		display_pid_status(t_child *node, char option);
int		jobs_builtin(int ac, char **cmd);
int		init_pid(void);
int		update_priority(int first);
int		kill_pids(void);
int 	display_pid_long(t_child *node, int fd);
int		remove_pid(t_child *node);

/*
**	fg_builtin.c & dependencies
*/

int		fg_builtin(int ac, char **cmd);
int		search_index(t_child **node, char *str_index);
int		search_pid(t_child **node, char *str_pid, pid_t pid);
int		search_priority(t_child **node);
int		search_status(t_child **node, int status);
int		search_process(t_child **node, char *p_name);

/*
**	bg_builtin.c & dependencies
*/

int		bg_builtin(int ac, char **cmd);
int		bg_resume(t_child **node);

/*
**	alias_builtin.c & dependencies
*/

int		init_alias(int file);
char	*parse_aliases(char *line, char *origin, char *prev);
char	*substitute_alias(char **origin, char *line, int size);
int		save_alias(int save);
int		ft_arraylen(char **array);
int		display_alias(void);
int		is_reserved(char *key);
int		is_alias(char *key);
char 	*get_alias(char *key);
int		alias_builtin(int ac, char **cmd);
int		unalias_builtin(int ac, char **cmd);

/*
**	cd_builtin_posix.c & dependencies
*/

int		begin_with(char *env_key, char *str);
int		search_env(char *var);
char	*get_env(char *var);

/*
**	get_options.c
*/

int		ft_flags(char c, char *flags, char *opt);
int		get_options(char *flags, char *opt, char *str, int (*usage)());
int		params(char **flags, int ac, char **av, int (*usage)());

/*
**	signals.c & dependencies
*/

void 	sigchld_handler();
void 	init_signal(void);
int 	s_get_values(int status, int *action, char **handler, char **stat);
void	s_child_handler(int status, t_child *node);
void	resetsign(void);
int		waitabit(int);

#endif
