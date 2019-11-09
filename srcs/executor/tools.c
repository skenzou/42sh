/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 06:45:33 by midrissi          #+#    #+#             */
/*   Updated: 2019/10/23 12:48:22 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*get_key_value(char *key, char **taba)
{
	char	*entry;
	int		key_index;

	if (!(key = ft_strjoin(key, "=")))
		shell_exit(MALLOC_ERR);
	key_index = get_indexof_key(key, taba);
	if (key_index >= 0)
	{
		entry = taba[key_index];
		while (*entry && *entry != '=')
			entry++;
		free(key);
		entry += (*entry == '=');
		return (ft_strlen(entry) ? entry : NULL);
	}
	free(key);
	return (NULL);
}

int		check_dir(char *path)
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

int		check_file(char *path)
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
