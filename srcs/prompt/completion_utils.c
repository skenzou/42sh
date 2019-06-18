/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 06:02:13 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/15 13:55:14 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_separator(char *s, int position)
{
	return ((s[position] && s[position] == ';') ||
			(s[position] && s[position] == '|') ||
			(s[position] && s[position] == '&'));
}

int		is_space_before(t_cap *tcap, int position)
{
	int i;

	i = -1;
	while (++i <= position && i < tcap->char_len)
		if (tcap->command[i] != ' ')
			return (0);
	return (1);
}

int		init_autocomp(t_cap *tcap, t_ab *autocomp)
{
	int max_offset;

	max_offset = autocomp->max_offset;
	autocomp->state = 1;
	//autocomp->len = 0;
	//autocomp->type = 0;

	autocomp->row = tcap->cursx_max / (ft_max(max_offset + 2, 1));
	autocomp->col = autocomp->len / ft_max(autocomp->row, 1);
	autocomp->carry = autocomp->len % ft_max(autocomp->row, 1);
	return (max_offset);
}

int		print_name(t_ab *autocomp, char *str, int i)
{
	//dprintf(debug(), "printname: |%s|\n", str);
	if (i == autocomp->pos)
		ft_putstr("\x1b[7m");
	ft_putstr(str);
	if (i == autocomp->pos)
		ft_putstr("\x1b[0m");
	ft_move(g_shell->tcap, "!right", autocomp->max_offset - ft_strlen(str) + 2);
	return (1);
}

char file_name_ext(char *string, t_stat stats, char *name)
{
	char ext;

	ext = 0;
	if (S_ISDIR(stats.st_mode))
		ext = 'd';
	else if (S_ISREG(stats.st_mode))
		ext = '-';
	ft_bzero(name, MAX_PATH);
	ft_strcpy(name, string);
	if (ext == 'd')
		name[ft_strlen(name)] = '/';
	return ext;
}

void		cat_fullpath(char *full_path, char *name, char *path)
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


char	*env_path(char **env)
{
	int i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], "PATH=", 5))
			return ((char*)env[i] + 5);
	return (NULL);
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

int		is_first_argi(t_cap *tc, int position)
{
	int i;

	if (!get_argi(tc, position))
		return (1);
	i = position - 1;
	while (i)
	{
		if (tc->command[i] == ' '
				&& (tc->command[i - 1] &&  !is_separator(tc->command, i -1)))
			return (0);
		else if (is_separator(tc->command, i))
			return (1);
		i--;
	}
	return (0);
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


int		is_env_var(t_ab *autocomp, char *path)
{
	int i;
	char copy[MAX_PATH];

	ft_strcpy(copy, path);
	i = 0;
	if (path[0] == '$' && (path[1] && path[1] == '{'))
	{
		i = 2;
		autocomp->after[0] = '}';
		autocomp->after[1] = '\0';
	}
	else if (path[0] == '$')
	{
		i = 1;
		autocomp->after[0] = path[0] == '$';
		autocomp->after[1] = '\0';
	}
	ft_bzero(path, MAX_PATH);
	ft_strcpy(path, copy + i);
	return (i > 0);
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
		str[0] == '{' && (autocomp->after[0] = '{');
		str[0] == '[' && (autocomp->after[0] = '[');
		autocomp->after[1] = '\0';
	}
	else
		autocomp->after[0] = '\0';
	ft_bzero(str, MAX_PATH);
	ft_strcpy(str, copy + i);
}
