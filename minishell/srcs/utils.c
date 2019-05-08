/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 21:12:06 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/29 18:06:07 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env)
{
	int i;

	i = -1;
	while (env && env[++i])
		ft_printf("%s\n", env[i]);
}

void	print_prompt(void)
{
	char	buff[MAX_PATH_LEN];
	int		i;
	int		j;

	i = -1;
	j = 0;
	ft_bzero(buff, MAX_PATH_LEN);
	getcwd(buff, MAX_PATH_LEN);
	while (buff[++i])
		if (buff[i] == '/' && buff[i + 1])
			j = i + 1;
	ft_printf(ANSI_BLUE "-> " ANSI_RESET);
	ft_printf(ANSI_CYAN "%s" ANSI_RESET, buff + j);
	ft_printf(ANSI_BLUE "> "ANSI_RESET);
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

char	*get_env_path(char **env)
{
	int	i;

	i = -1;
	while (env && env[++i])
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (env[i] + 5);
	return (NULL);
}

void	set_path(char fullpath[], char *cmd, char *path)
{
	ft_bzero(fullpath, MAX_PATH_LEN);
	ft_strcpy(fullpath, path);
	ft_strcat(fullpath, "/");
	ft_strcat(fullpath, cmd);
}
