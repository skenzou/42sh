/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:42:03 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/21 14:23:15 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "prompt.h"
# include <errno.h>
# define ANSI_RED		"\x1b[31m"
# define ANSI_GREEN		"\x1b[32m"
# define ANSI_YELLOW	"\x1b[33m"
# define ANSI_BLUE		"\x1b[34m"
# define ANSI_MAGENTA	"\x1b[35m"
# define ANSI_CYAN		"\x1b[36m"
# define ANSI_BRED		"\x1b[1m\x1b[31m"
# define ANSI_BGREEN		"\x1b[1m\x1b[32m"
# define ANSI_BYELLOW	"\x1b[1m\x1b[33m"
# define ANSI_BBLUE		"\x1b[1m\x1b[34m"
# define ANSI_BMAGENTA	"\x1b[1m\x1b[35m"
# define ANSI_BCYAN		"\x1b[1m\x1b[36m"
# define ANSI_RESET		"\x1b[0m"
# define DQUOTE			'"'
# define QUOTE			'\''
# define BSLASH			'\\'
# define HERE_DOC_TMP "/tmp/.21sh_tmp"
# define TABLE_SIZE 1999
# define PRINT_LEXER  (1 << 0)
# define PRINT_AST  (1 << 1)
# define PRINT_REDIR (1 << 2)
# define MAX_PATH_LEN		4096
# define NON_EXISTENT		1
# define IS_DIRECTORY		2
# define NO_RIGHT			3
# define INV_ARG			4
# define SETENV_USG			5
# define UNSETENV_USG		6
# define FAILFORK			7
# define NOT_DIR			8
# define ECHO_BUILTIN		9
# define CD_BUILTIN			10
# define SETENV_BUILTIN		11
# define UNSETENV_BUILTIN	12
# define ENV_BUILTIN		13
# define EXIT_BUILTIN		14
# define NOT_FOUND			15
# define SETENV_INVALID_KEY	16

typedef struct	s_shell
{
	t_cap		*tcap;
	char		**env;
	t_list		*redir;
	t_list		*lexer;
	t_ast		*ast;
	char		*var[256];
	t_history	*history;
	t_hash_entry	*hash_table[TABLE_SIZE];
	int			fd_table[10];
  char    print_flags;
}				t_shell;

extern t_shell *g_shell;

void		print_prompt(void);
void		sighandler(int sig);
void 		ft_exit(char *str);
void		sigfork(int sig);
char		**dup_env(char **env);
int			handler(char *input);
#endif
