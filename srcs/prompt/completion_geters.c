/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_geters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 23:59:43 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/20 06:35:43 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	get_tilde(char *path, char *final_path)
{
	int		i;
	char	*home;

	home = get_all_key_value("HOME", g_shell->env);
	i = -1;
	if (home && path[0] == '~')
	{
		ft_strcpy(final_path, home);
		ft_strcpy(final_path + ft_strlen(home), path + 1);
	}
	else
		ft_strcpy(final_path, path);
}

int		get_argi(t_cap *tc, int position)
{
	int i;
	int argi;

	argi = 0;
	i = 0;
	while (tc->command[i] && i < position)
		if (tc->command[i] && tc->command[i] == ' ')
		{
			while (tc->command[i] && tc->command[i] == ' ')
				i++;
			argi++;
		}
		else
			while (tc->command[i] && tc->command[i] != ' ')
				i++;
	return (argi);
}

void	get_word(t_cap *tc, int position, char *path)
{
	int i;

	i = position - 1;
	ft_bzero(path, MAX_PATH);
	while (ft_isprint(tc->command[i]) &&
			((!ft_isspace(tc->command[i]) && !is_separator(tc->command, i))
				|| tc->command[i - 1] == '\\'))
		i--;
	ft_strncpy(path, tc->command + i + 1, position - 1 - i);
}

void	get_quote(t_ab *autocomp, char *str)
{
	int		i;
	char	copy[MAX_PATH];

	ft_strcpy(copy, str);
	i = 0;
	if (str[0] == '\'' || str[0] == '"' || str[0] == '{' || str[0] == '[' ||
		str[0] == '(')
	{
		i = 1;
		str[0] == '\'' && (autocomp->after[0] = '\'');
		str[0] == '"' && (autocomp->after[0] = '"');
		str[0] == '{' && (autocomp->after[0] = '}');
		str[0] == '[' && (autocomp->after[0] = ']');
		autocomp->after[1] = '\0';
	}
	else
		autocomp->after[0] = '\0';
	ft_bzero(str, MAX_PATH);
	ft_strcpy(str, copy + i);
}

void	cat_fullpath(char *full_path, char *name, char *path)
{
	ft_bzero(full_path, MAX_PATH);
	if (path)
	{
		ft_strcpy(full_path, path);
		if (*path != '/' || *(path + 1))
			ft_strcat(full_path, "/");
	}
	ft_strcat(full_path, name);
}
