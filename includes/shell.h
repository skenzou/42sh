/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:42:03 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/13 06:16:52 by midrissi         ###   ########.fr       */
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
}				t_shell;

extern t_shell *g_shell;

void		print_prompt(void);
void		sighandler(int sig);
void 		ft_exit(char *str);
void		sigfork(int sig);
char		**dup_env(char **env);
int		handler(char *input);
#endif
