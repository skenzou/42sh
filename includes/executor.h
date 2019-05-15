/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 00:40:57 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/15 06:01:10 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		pipe_cmds(char **cmd1, char **cmd2, char **env);
void		search_pipe(t_ast *root,char *str, char **env);
void		redir_delone(void *data, size_t size);
int			ft_fork(char **cmd, char **env);
void		remove_quote(char **str);
int			hash_table(char **str,char **env);
void		expand_and_execute(char **args);
void		handle_redir();
void		print_redir(t_list *redir);
int			check_file(char *path);
void		ft_execute_ast(t_ast *root , char **env);
void		ft_execute(char **args);
void		ft_expand(char **args);
void 		pipe_cmds(char **cmd1, char **cmd2, char **env);
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
int			ft_fork_amper(char *path, char **command, char **env);
int			update_pid_table(int pid, char **command);
int 		jobs_builtin(char **command);
int			init_pid();
int 		kill_pids();

typedef struct s_child t_child;

struct s_child{
		int		index;
		int 	pid;
		int		status;
		char	*exec; //**
		t_child *next;
		t_child *prev;
};

extern t_child *g_pid_table;

typedef struct s_hash_entry
{
	unsigned char *data;
	unsigned char *key;
}				t_hash_entry;
