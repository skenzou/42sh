/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:42:03 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/16 20:23:31 by ghamelek         ###   ########.fr       */
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
# include <pwd.h>
# include <uuid/uuid.h>
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "prompt.h"
# include <errno.h>
# include <time.h>
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
# define NON_EXISTENT		2
# define IS_DIRECTORY		3
# define NO_RIGHT			4
# define INV_ARG			5
# define SETENV_USG			6
# define UNSETENV_USG		7
# define FAILFORK			8
# define NOT_DIR			9
# define ECHO_BUILTIN		10
# define CD_BUILTIN			11
# define SETENV_BUILTIN		12
# define UNSETENV_BUILTIN	13
# define ENV_BUILTIN		14
# define EXIT_BUILTIN		15
# define NOT_FOUND			16
# define SETENV_INVALID_KEY	17
# define SET_BUILTIN		18
# define EXPORT_BUILTIN		19
# define UNSET_BUILTIN		20
# define JOBS_BUILTIN		21
# define TYPE_BUILTIN		22
# define TEST_BUILTIN		23
# define OPEN_ERR			24
# define AMBIGOUS_REDIRECT	25
# define BAD_FD				26

typedef struct	s_shell
{
	t_list		*hash_indexes;
	t_cap		*tcap;
	char		**env;
	char		**intern;
	char		**env_tmp;
	char		**intern_tmp;
	t_list		*redir;
	t_list		*lexer;
	t_ast		*ast;
	char		*var[256];
	t_history	*history;
	t_hash_entry	*hash_table[TABLE_SIZE];
	int			fd_table[10];
	char		print_flags;
	char		lastsignal;
	size_t		curr_pipe;
	t_ab		*autocomp;
	t_cc		*copy_cut;
	t_ctrl_r	*ctrl_r;
	t_term		*term;
	t_term		*term_backup;
	t_list		*temp_redir;
}				t_shell;

extern t_shell *g_shell;

char		**dup_env(const char **env);
int			handler(const char *input);
#endif
