/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 00:40:57 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/15 01:38:45 by midrissi         ###   ########.fr       */
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

typedef struct s_hash_entry
{
	unsigned char *data;
	unsigned char *key;
}				t_hash_entry;
