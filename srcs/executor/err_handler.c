/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 00:14:11 by midrissi          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/06/04 02:28:32 by midrissi         ###   ########.fr       */
=======
/*   Updated: 2019/06/04 22:22:26 by tlechien         ###   ########.fr       */
>>>>>>> tlechien
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

<<<<<<< HEAD
=======
int		err_display(char *start, char *mid, char *end)
{
	(start) ? ft_putstr_fd(start, 2): 0;
	(mid) ? ft_putstr_fd(mid, 2): 0;
	(end) ? ft_putstr_fd(end, 2): 0;
	return (1);
}

>>>>>>> tlechien
static	void err_helper(char *error, char *cause)
{
		ft_putstr_fd(error, 2);
		ft_putendl_fd(cause, 2);
}

void	err_handler(int err_id, char *str)
{
	if (err_id == NON_EXISTENT)
		err_helper("42sh: No such file or directory: ", str);
	if (err_id == IS_DIRECTORY)
		err_helper("42sh: Is a directory: ", str);
	if (err_id == NO_RIGHT)
		err_helper("42sh: Permission denied: ", str);
	if (err_id == FAILFORK)
		err_helper("42sh: Fork failed", NULL);
	if (err_id == NOT_FOUND)
		err_helper("42sh: command not found: ", str);
	if (err_id == OPEN_ERR)
		err_helper("42sh: Error while opening: ", str);
}

void	redir_errors(int err_id, char *dest, int fd)
{
	ft_putstr_fd("42sh: ", 2);
	if (err_id == BAD_FD)
	{
		ft_putnbr_fd(fd, 2);
		ft_putendl_fd(": bad file descriptor", 2);
	}
	if (err_id == AMBIGOUS_REDIRECT)
	{
		ft_putstr_fd(dest, 2);
		ft_putendl_fd(": ambigous redirect", 2);
	}
}
