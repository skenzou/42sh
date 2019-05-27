/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 06:45:33 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/27 17:28:32 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int check_dir(char *path)
{
	struct stat buff;

	if (!stat(path, &buff))
	{
		if (S_ISDIR(buff.st_mode) == 1)
		{
			if (!access(path, X_OK))
				return (0);
			return (NO_RIGHT);
		}
		return (NOT_DIR);
	}
	return (NON_EXISTENT);
}

int check_file(char *path)
{
	struct stat buff;

	if (!stat(path, &buff))
	{
		if (!S_ISDIR(buff.st_mode) == 1)
		{
			if (!access(path, X_OK))
				return (0);
			return (NO_RIGHT);
		}
		return (IS_DIRECTORY);
	}
	return (NON_EXISTENT);
}

void	print_split(char **split)
{
	int i;

	i = -1;
	while (split && split[++i])
		ft_printf("%s\n", split[i]);
}

int		is_path(char *str)
{
	while (*str)
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}
