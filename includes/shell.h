/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:42:03 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/07 17:47:42 by ghamelek         ###   ########.fr       */
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

void		ft_compiler(t_ast *root ,char **env);
void		print_prompt(void);
void		sighandler(int sig);
void ft_exit(char *str);

#endif
