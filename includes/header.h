/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:42:03 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/29 23:36:54 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <fcntl.h>
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

void	print_prompt(void);
void	sighandler(int sig);

typedef enum
{
	TOKEN_EAT,
	TOKEN_DQ,
	TOKEN_SQ,
	TOKEN_SEMI,
	TOKEN_DBL_SEMI,
	TOKEN_OPERATOR,
	TOKEN_NEG,
	TOKEN_DBLAND,
	TOKEN_DBLOR,
	TOKEN_PIPE,
	TOKEN_OP_ARITHM,
	TOKEN_AND,
	TOKEN_OP_BRA,
	TOKEN_CL_BRA,
	TOKEN_OP_PAR,
	TOKEN_CL_PAR,
	TOKEN_REDIR,
	TOKEN_ASS_WORD,
	TOKEN_OP_CMD,
	TOKEN_OP_CURLY,
	TOKEN_CL_CURLY,
	TOKEN_EQUAL,
	TOKEN_STRING,
	TOKEN_NAME,
	TOKEN_FOR,
	TOKEN_WHILE,
	TOKEN_NULL
} e_token_type;

#endif
