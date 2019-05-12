/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 23:42:34 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/12 04:00:30 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		read_var(char **var)
{
	char		*str;
	int			i;
	int			fd;
	char		env_file[BUFFSIZE];
	int			userlen;

	i = 0;
	userlen = ft_strlen(getenv("USER"));
	ft_strcpy(env_file, "/Users/");
	ft_strcpy(env_file + 7, getenv("USER"));
	ft_strcpy(env_file + 7 + userlen, "/");
	ft_strcpy(env_file + 7 + userlen + 1, DEFAULT_ENV_FILE_NAME);
	env_file[8 + userlen + ft_strlen(DEFAULT_ENV_FILE_NAME)] = '\0';
	if ((fd = open(env_file, O_RDONLY)) > 0)
	{
		while (get_next_line(fd, &str, '\n') > 0)
		{
			if (!(var[i] = ft_strdup(str)) || !~ft_indexof(var[i], '='))
				return (!~ft_indexof(var[i], '=') ? -2 : -1);
			i++;
		}
		var[i] = NULL;
	}
	close(fd);
	return (1);
}

char	*get_string_var(char *string, char **var)
{
	int		i;
	char	*name;

	i = -1;
	while (var[++i])
	{
		if (!(name = ft_substr(var[i], 0, ft_indexof(var[i], '='))))
			return (NULL);
		if (!ft_strcmp(string, name))
			return (var[i] + ft_indexof(var[i], '=') + 1);
	}
	return (NULL);
}

int		get_int_var(char *string, char **var)
{
	int		i;
	char	*name;

	i = -1;
	while (var[++i])
	{
		if (!(name = ft_substr(var[i], 0, ft_indexof(var[i], '='))))
			return (-1);
		if (!ft_strcmp(string, name))
			return (ft_atoi(var[i] + ft_indexof(var[i], '=') + 1));
	}
	return (-1);
}
