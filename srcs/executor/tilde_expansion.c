/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:11:24 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/04 01:21:15 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			*get_home_from_pwuid()
{
	struct passwd		*pwd;
	char				*home;

	if ((pwd = getpwuid(getuid())))
		home = ft_strjoin("/Users/", pwd->pw_name);
	else
		home = ft_strdup("/Users");
	return (home);
}

static char			*check_user(char *str, char *home)
{
	char	buff[MAX_PATH_LEN];

	ft_bzero((void *)buff, MAX_PATH_LEN);
	ft_strcpy(buff, "/Users/");
	ft_strcat(buff, str);
	if (check_dir(buff))
	{
		free(home);
		return (NULL);
	}
	else
		str = ft_strdup(buff);
	if (!str)
		ft_exit("Malloc failed in tilde_expansion");
	return (str);
}

void				tilde_expansion(char **ptr)
{
	char	*str;
	char	*home;

	if (!(str = *ptr) || *str++ != '~')
		return ;
	if (!(home = ft_strdup(get_homepath(g_shell->env))))
		home = get_home_from_pwuid();
	if (!(*str))
		str = home;
	else if (*str && *str != '/')
	{
		if (!(str = check_user(str, home)))
			return ;
	}
	else
		str = ft_strjoin(home, str);
	if (str != home)
		free(home);
	if (!str)
		ft_exit("Malloc failed in tilde_expansion");
	free(*ptr);
	*ptr = str;
}
