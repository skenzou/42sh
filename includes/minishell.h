/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 21:38:26 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/24 13:55:16 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# define ANSI_RED		"\x1b[1m\x1b[31m"
# define ANSI_GREEN		"\x1b[1m\x1b[32m"
# define ANSI_YELLOW	"\x1b[1m\x1b[33m"
# define ANSI_BLUE		"\x1b[1m\x1b[34m"
# define ANSI_MAGENTA	"\x1b[1m\x1b[35m"
# define ANSI_CYAN		"\x1b[1m\x1b[36m"
# define ANSI_RESET		"\x1b[0m"
# define MAX_PATH_LEN	4096
# define NON_EXISTENT	1
# define IS_DIRECTORY	2
# define NO_RIGHT		3
# define INV_ARG		4
# define SETENV_USG		5
# define UNSETENV_USG	6
# define FAILFORK		7
# define NOT_DIR		8
# define ECHO			9
# define CD				10
# define SETENV			11
# define UNSETENV		12
# define ENV			13
# define EXIT			14
# define NOT_FOUND		15

/*
**UTILS.C
*/
char			*get_env_path(char **env);
void			set_path(char fullpath[], char *cmd, char *path);
int				is_path(char *str);
void			print_prompt(void);
void			print_env(char **env);

/*
**CD_BUILTIN.C
*/
int				cd_builtin(int argc, char **argv, char ***env);
char			*get_homepath(char **env);

/*
**ERR_HANDLER.C
*/
void			err_handler(int err_id, char *str);

/*
**ECHO_BUILTIN.C
*/
int				echo_builtin(int argc, char **argv);

/*
**SIGNAL_HANDLERS.C
*/
void			sigfork(int sig);
void			sighandler(int sig);

/*
**EXIT_BUILTIN.C
*/
void			exit_builtin(void);

/*
**SETENV_BUILTIN.C
*/
int				setenv_builtin(int ac, char **av, char ***env);
int				is_set(char *key, char **env);
void			ft_setenv(char *key, char *value, char ***env);

/*
**UNSETENV_BUILTIN.C
*/
int				unsetenv_builtin(int ac, char **av, char ***env);

/*
**BIN_HANDLER.C
*/
void			exec_bin(char **bin, char **env);

/*
**CMD_HANDLER.C
*/
void			cmd_handler(char *cmd, char ***env);

/*
**EXPANSIONS.C
*/
void			manage_expansions(char **input, char **env);

#endif
