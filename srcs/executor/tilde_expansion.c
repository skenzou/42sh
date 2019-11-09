/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:11:24 by midrissi          #+#    #+#             */
/*   Updated: 2019/10/23 12:55:00 by tlechien         ###   ########.fr       */
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
		shell_exit(MALLOC_ERR);
	return (str);
}

static char			*get_home(void)
{
	char *home;

	home = get_all_key_value("HOME", g_shell->env);
	if (!home)
		home = get_home_from_pwuid();
	else
	{
		if (!(home = ft_strdup(home)))
			shell_exit(MALLOC_ERR);
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
		shell_exit(MALLOC_ERR);
	free(*ptr);
	*ptr = str;
}
