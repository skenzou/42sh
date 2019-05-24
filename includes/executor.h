/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 00:40:57 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/24 16:20:56 by tlechien         ###   ########.fr       */
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

# define S_RUN	0
# define S_DONE 1
# define S_SUSP	2
# define S_CONT 3
# define S_TERM 4
# define ID_PRIORITY  g_pid_table->index
# define ID_PID       g_pid_table->pid
# define ID_INDEX     g_pid_table->index
# define ID_STATUS    g_pid_table->status
# define ID_EXEC      g_pid_table->exec
# define ID_NEXT      g_pid_table->next
# define ID_PREV      g_pid_table->prev
# define ALIAS_FILE	".21sh_alias"

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
}				t_hash_entry;

typedef struct s_pipe
{
	int			pipe[2];
}				t_pipe;

extern	t_child		*g_pid_table;
extern	const char	*g_status[];
extern	const char	*g_reserved[];
extern	char		**g_aliases;

/*
** ## FUNCTIONS ##
*/

void		handle_pipe(t_ast *root);
void		redir_delone(void *data, size_t size);
int			ft_fork(char **cmd, char **env);
void		remove_quote(char **str);
int			hash_table(char **str,char **env);
void		expand_and_execute(char **args);
char		**handle_redir();
void		print_redir(t_list *redir);
int			check_file(char *path);
void		ft_execute_ast(t_ast *root , char **env);
void		ft_expand(char **args);
int			unsetenv_builtin(int ac, char **av, char ***env);
int			setenv_builtin(int ac, char **av, char ***env);
int			is_set(char *key, char **env);
void		ft_setenv(char *key, char *value, char ***env);
int			echo_builtin(int argc, char **argv);
void		exit_builtin(void);
int			cd_builtin(int argc, char **argv, char ***env);
void		err_handler(int err_id, char *str);
void		print_env(char **env);
char		**get_curr_cmd(t_list *redir);
int			open_file(t_redir *redir);
int			is_path(char *str);
int			check_dir(char *path);
void 		restore_fd();
int			ft_pre_execution(char ***args, int redir);

/*
**	ft_fork.c
*/

int		ft_fork(char **cmd, char **env);
int		ft_fork_amper(char **cmd, char **env);
int		ft_waitprocess(pid_t pid, char **cmd);

/*
**	jobs_builtin.c & dependencies
*/

int		update_pid_table(int pid, char **cmd, int status);
int		display_pid_status(t_child *node, int option);
int		jobs_builtin(char **cmd);
int		init_pid(void);
int		update_priority(int first);
int		kill_pids(void);

/*
**	fg_builtin.c & dependencies
*/

int		fg_builtin(char **cmd);
int		search_index(t_child **node, char *str_index);
int		search_pid(t_child **node, char *str_pid, pid_t pid);
int		search_priority(t_child **node);
int		search_status(t_child **node, int status);
int		search_process(t_child **node, char *p_name);

/*
**	bg_builtin.c & dependencies
*/

int		bg_builtin(char **cmd);
int		bg_resume(t_child **node);

/*
**	alias_builtin.c & dependencies
*/

int		init_alias(int file);
char	*parse_aliases(char *line);
char	*substitute_alias(char **origin, char *line, int size);
int		save_alias(int save);
int		ft_arraylen(char **array);
int		display_alias(void);
int		is_reserved(char *key);
int		is_alias(char *key);
char 	*get_alias(char *key);
int		alias_builtin(char **cmd);

/*
**	cd_builtin_posix.c & dependencies
*/

int		begin_with(char *env_key, char *str);
int		search_env(char *var);
char	*get_env(char *var);

#endif
