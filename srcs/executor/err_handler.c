/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 00:14:11 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/15 00:55:15 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static	void err_helper(char *first, char *second, char *third)
{
	if (first && second && third)
	{
		ft_putstr_fd(first, 2);
		ft_putstr_fd(second, 2);
		ft_putendl_fd(third, 2);
	}
	if (!first && !second)
		ft_putendl_fd(third, 2);
	if (first && second && !third)
	{
		ft_putstr_fd(first, 2);
		ft_putendl_fd(second, 2);
	}
}

void	err_handler(int err_id, char *str)
{
	if (err_id == NON_EXISTENT)
		err_helper("42sh: ", str, ": No such file or directory");
	if (err_id == IS_DIRECTORY)
		err_helper("42sh: ", str, ": Is a directory");
	if (err_id == NO_RIGHT)
		err_helper("42sh: ", str, ": Permission denied");
	if (err_id == INV_ARG)
		err_helper("42sh: ", str, ": Invalid argument");
	if (err_id == SETENV_USG)
		err_helper(NULL, NULL, "usage: setenv [<Key> <Value> | <Key>]");
	if (err_id == SETENV_INVALID_KEY)
		err_helper(NULL, NULL,
			"setenv: Variable name must contain alphanumeric characters.");
	if (err_id == UNSETENV_USG)
		err_helper(NULL, NULL, "usage: unsetenv <Key>");
	if (err_id == FAILFORK)
		err_helper("42sh: ", "Fork failed", NULL);
	if (err_id == NOT_DIR)
		err_helper("42sh: ", "Not a directory: ", str);
	if (err_id == NOT_FOUND)
		err_helper("42sh: ", str, ": command not found");
}
