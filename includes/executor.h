/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 00:40:57 by midrissi          #+#    #+#             */
/*   Updated: 2019/11/06 16:45:24 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "shell.h"

# define ALIAS_FILE		".21sh_alias"
# define FC_OPTIONS 	"erlns"
# define FC_EDITOR 		(1 << 0)
# define FC_REVERSE 	(1 << 1)
# define FC_LIST 		(1 << 2)
# define FC_NO_NUMBER 	(1 << 3)
# define FC_NO_EDITOR 	(1 << 4)

typedef struct		s_hash_entry
{
	unsigned char	*data;
	unsigned char	*key;
	size_t			hit;
}					t_hash_entry;

typedef struct		s_pipe
{
	int				fd[2];
	char			**cmd;
	int				pid;
	int				redir;
	struct s_pipe	*next;
}					t_pipe;

typedef struct		s_builtin
{
	char			*cmd;
	int				(*function)(int ac, char **av);
}					t_builtin;

extern	const char	*g_status[];
extern	const char	*g_reserved[];
extern	char		**g_aliases;

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
** BIN_HASH.C
*/
t_hash_entry		*hash_search(unsigned char *key);
t_hash_entry		*hash_insert(unsigned char *key, char **env);
int					hash_table(char **str, char **env);
/*
** BIN_HASH_TOOLS.C
*/
char				*free_duo(char **s1, t_hash_entry **s2);
char				*my_env(char **env);
unsigned char		*add_path(char **bin, unsigned char *argv);
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
int					shell_exit(int err_code);
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
** FC_BUILTIN.C
*/
int					fc_builtin(int ac, char **cmd);
/*
** FC_BUILTIN_EDITOR.c
*/
int		fc_editor(int argc, char **argv, int param);
/*
** FC_BUILTIN_LIST.C
*/
int					fc_list(int ac, char **av, int param);
/*
** FC_BUILTIN_LIST.C
*/
int					fc_no_editor(int ac, char **av);
/*
** FC_BUILTIN_UTILS.c
*/
void				arg_to_number(char *str, char *str2, int *index, int *max);
char 				*randomize_path(char *path);
int					get_param(int argc, char **argv);
int					check_compatibility(int p);
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
** HANDLE_REDIR.C
*/
char				**handle_redir();
/*
** HASH_BUILTIN.C
*/
int					hash_builtin(int ac, char **av);
void				empty_table(void);
/*
** PARAM_EXPANSION.C
*/
void				param_expansion(char **ptr);
/*
** PIPE_EXEC.C
*/
int 				launch_pipe (t_pipe **begin, t_pipe *pipe, int is_bg);
/*
** PIPE_SETUP.C
*/
void 				push_pipe(t_ast *root, t_pipe **begin);
void 				parse_pipe (t_ast *root, t_ast *origin, t_pipe **pipe);
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
char				*get_all_key_value(char *key, char **env);
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
void				compare_paths(char *path);
/*
** TAB_UTILS.C
*/
char				**dup_tab(char **array, size_t size);
void				remove_n_first_entries(char **old, int n);
char				**join_2tab(char **curr, char **next, size_t curr_size,
															size_t next_size);
char				**realloc_new_tab(char *needle, char **old, size_t size);
/*
** TEST_BUILTIN.C
*/
int					test_builtin(int ac, char **args);
/*
** TEST_BUILTIN_TOOLS.C
*/
int					is_integer(char *str, char *str2);
int					arithmetic_test(char **av, char *op);
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
char				**removekey2(char *key, int keylen, const char **env);
int					unsetenv_builtin(int ac, char **av);
/*
** UTILS2.C
*/
int					is_special_char(char c);
void				close_fd();
int					is_key_valid(char *key);
int					get_indexof_key2(char *key, char **env);
void				update_env(char *key, char *value);

#endif
