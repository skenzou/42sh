/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:11:24 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/07 06:24:21 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			*get_home_from_pwuid(void)
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

static char			*get_home(void)
{
	char *home;

	home = get_key_value("HOME", g_shell->env);
	if (!home)
		home = get_key_value("HOME", g_shell->intern);
	if (!home)
		home = get_home_from_pwuid();
	else
	{
		if (!(home = ft_strdup(home)))
			ft_exit("Malloc failed in tilde_expansion");
	}
	return (home);
}

void				tilde_expansion(char **ptr)
{
	char	*str;
	char	*home;

	if (!(str = *ptr) || *str++ != '~')
		return ;
	home = get_home();
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
