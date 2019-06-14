/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 06:02:13 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/12 05:54:11 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		init_autocomp(t_cap *tcap, t_ab *autocomp)
{
	int max_offset;

	max_offset = autocomp->max_offset;
	autocomp->state = 1;
	//autocomp->len = 0;
	//autocomp->type = 0;
	ft_bzero(autocomp->after, MAX_PATH);
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

void file_name_ext(char *string, t_stat stats, char *name)
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
}

static void		cat_fullpath(char *full_path, char *name, char *path)
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

void create_file(char *name, char *path, t_ab *autocomp)
{
	t_stat		stats;
	char full_path[MAX_PATH];
	char file[MAX_PATH];

	ft_bzero(file, MAX_PATH);
	cat_fullpath(full_path, name, path);
	lstat(full_path, &stats);
	file_name_ext(name, stats, file);
	autocomp->data[autocomp->len] = ft_strdup(file);
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
void		add_to_completion(t_ab *autocomp, char *path)
{
	t_dirent	*d;
	DIR			*dir;

	autocomp->max_offset = 0;
	autocomp->len = 0;
	if ((dir = opendir(path)))
		while ((d = readdir(dir)))
		{
			if (d->d_name[0] != '.')
			{
				create_file(d->d_name, path, autocomp);
				autocomp->max_offset =
								ft_max(autocomp->max_offset, ft_strlen(d->d_name));
				autocomp->len++;
			}
		}
	closedir(dir);
}

int		is_separator(char *s, int position)
{
 	return ((s[position] && s[position] == ';') ||
			(s[position] && s[position] == '|') ||
			(s[position] && s[position] == '&'));
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

void get_word(t_ab *autocomp, t_cap *tc, int position, char *path)
{
	(void)autocomp;
	ft_bzero(path, MAX_PATH);
	int i = position - 1;
	while (ft_isprint(tc->command[i]) &&
			((!ft_isspace(tc->command[i]) && !is_separator(tc->command, i))
				|| tc->command[i - 1] == '\\'))
		i--;
	ft_strncpy(path, tc->command + i + 1, position - 1 - i);
}

int is_env_var(t_ab *autocomp, char *path)
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
	else if (path[0] == '$' || path[0] == '\'' || path[0] == '"')
	{
		i = 1;
		autocomp->after[0] = path[0] == '$' ? '\0' : path[0];
		autocomp->after[1] = '\0';
	}
	ft_bzero(path, MAX_PATH);
	ft_strcpy(path, copy + i);
	return i > 0;
}

int 	env_completion(t_ab *autocomp, char *key)
{
	int i;
	int len;
	char **env;
	char **intern;
	int index;

	env = g_shell->env;
	intern = g_shell->intern;
	i = -1;
	len = ft_strlen(key);
	autocomp->max_offset = 0;
	autocomp->len = 0;
	while (env && env[++i])
	{
		if (env[i] && !ft_strncmp(key, env[i], len))
		{
			index = ft_indexof(env[i], '=');
			autocomp->data[autocomp->len] = ft_strdup(env[i] + index + 1);
			autocomp->max_offset =
							ft_max(autocomp->max_offset, ft_strlen(env[i] + index + 1));
			autocomp->len++;
		}
	}
	i = 0;
	while (intern && intern[++i])
	{
		if (intern[i] && !ft_strncmp(key, intern[i], len))
		{
			autocomp->data[autocomp->len] = ft_strdup(intern[i]);
			autocomp->max_offset =
							ft_max(autocomp->max_offset, ft_strlen(intern[i]));
			autocomp->len++;
		}
	}
	return (1);
}

int		first_arg_completion(t_ab *autocomp, t_cap *tc, int position)
{
	char path[MAX_PATH];

	get_word(autocomp, tc, position, path);
	if (is_env_var(autocomp, path))
	{
		dprintf(debug(), "env: |%s|\n", path);
		return (env_completion(autocomp, path));
	}
	if (tc->command[position - 1] && tc->command[position - 1] == '/')
	{

		add_to_completion(autocomp,  path);
		return (1);
	}
	return (0);
}

int		smart_completion(t_ab *autocomp, t_cap *tc, int position)
{
	(void)autocomp;
	if (is_first_argi(tc, position))
	{
		return (first_arg_completion(autocomp, tc, position));
	}
	else
	{

	}
	dprintf(debug(), "%d pos: %d: %c\n", is_first_argi(tc, position), position, tc->command[position]);
	return (0);
}

int 	get_words_completion(t_ab *autocomp, t_cap *tc)
{
	int pos;

	pos = tc->cursy * (tc->cursx_max + 1) + (tc->cursx) - tc->prompt_len;
	pos = pos - 1;
	if (pos == -1 || is_space_before(tc, pos))
	{
		ft_insert("    ", tc);
		return (0);
	}
	else if (tc->command[pos] == ' ' && ((pos + 1 < tc->char_len &&
					tc->command[pos + 1] == ' ') || pos == tc->char_len - 1))
	{
		dprintf(debug(), "space \n");
		add_to_completion(autocomp, ".");
		return (1);
	}
	else
	{
		if (smart_completion(autocomp, tc, pos + 1))
			return (1);
	}
	return (0);
}

int		ft_tab(t_cap *tcap, t_ab *autocomp)
{
	int row;
	int col;
	int i;

	if (!get_words_completion(autocomp, tcap))
		return (0);
	//dprintf(debug(), "segv");
	init_autocomp(tcap, autocomp);
	i = 0;
	col = -1;
	//end_event(tcap);
	int o;

	o = tcap->cursy * (tcap->cursx_max + 1) + (tcap->cursx) - tcap->prompt_len;
	end_event(tcap);
	//tputs(tcap->clr_all_line, 1, ft_put_termcaps);
	ft_move(tcap, "left", tcap->char_len - o);
	ft_move(tcap, "down", 1);
	while (++col < autocomp->col)
	{
		row = -1;
		while (++row < autocomp->row)
			print_name(autocomp, autocomp->data[i], i) && i++;
		ft_move(tcap, "down", 1);
	}
	if (autocomp->carry > 0)
	{
		row = autocomp->carry;
		while (row--)
			print_name(autocomp, autocomp->data[i], i) && i++;
	}
	ft_replace_cursor(tcap);
	i = 0;
	while (i < autocomp->col + (autocomp->carry > 0 ? 1 : +1))
	{
		ft_move(tcap, "up", 1);
		i++;
	}
	return (1);
}
