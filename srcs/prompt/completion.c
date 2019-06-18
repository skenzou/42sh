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

void create_file(char *name, char *path, t_ab *autocomp, int onlydir)
{
	t_stat		stats;
	char full_path[MAX_PATH];
	char file[MAX_PATH];

	ft_bzero(file, MAX_PATH);
	cat_fullpath(full_path, name, path);
	lstat(full_path, &stats);
	if ((autocomp->isdir = (file_name_ext(name, stats, file) == 'd')) || !onlydir)
	{
		autocomp->data[autocomp->len++] = ft_strdup(file);
		autocomp->max_offset =
						ft_max(autocomp->max_offset, ft_strlen(file));
	}
}


int		add_to_completion(t_ab *autocomp, char *path, int onlydir)
{
	t_dirent	*d;
	DIR			*dir;

	dprintf(debug(), "addcompletion match: |%s|\n", autocomp->match);
	if ((dir = opendir(path)))
	{
		while ((d = readdir(dir)))
		{
			if (d->d_name[0] != '.' && !ft_strncmp(d->d_name, autocomp->match, ft_strlen(autocomp->match)))
				create_file(d->d_name, path, autocomp, onlydir);
		}
		closedir(dir);
		return (1);
	}
	else
		dprintf(debug(), "probleme opendir\n");
	return 0;
}




int		env_completion(t_ab *autocomp, char *key)
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



int		command_completion(t_ab *autocomp, char *key)
{
	int i;
	int len;
	char **path_split;
	char *path;

	path = env_path(g_shell->env);
	if (!path)
		return (0);
	if (!(path_split = ft_strsplit(path, ':')))
		return (0);
	i = -1;
	len = ft_strlen(key);
	//autocomp->match = ft_strdup(key);
	ft_strcpy(autocomp->match, key);
	dprintf(debug(), "match: |%s|\n", autocomp->match);
	while (path_split && path_split[++i])
	{
		dprintf(debug(), "pathbin: |%s|\n", path_split[i]);
		add_to_completion(autocomp, path_split[i], 0);
	}
	return (1);
}

int		path_completion(t_ab *autocomp, char *key)
{
	char path[BUFFSIZE];

	ft_bzero(path, BUFFSIZE);
	dprintf(debug(), "pathcompletion, |%s|\n", key);
	int i;
	if (~ft_indexof(key, '/'))
	{
		i = ft_strlen(key) - 1;
		dprintf(debug(), "i ici vaut: %d\n", i);
		while (key[i] && key[i] != '/')
			i--;
		dprintf(debug(), "i ici vaut: %d\n", i);
		ft_strcpy(autocomp->match, key + i+ 1);
		ft_strncpy(path, key, i == 0 ? 1 : i);
	}
	else
	{
		ft_strcpy(autocomp->match, key);
		ft_strcpy(path, ".");
	}
	dprintf(debug(), "|%s| path match: |%s|\n", path, autocomp->match);
	return (add_to_completion(autocomp, path, 0));
}

int		first_arg_completion(t_ab *autocomp, t_cap *tc, char *str, int position)
{
	if (is_env_var(autocomp, str))
	{
		dprintf(debug(), "env arg: |%s|\n", str);
		return (env_completion(autocomp, str));
	}
	else if (tc->command[position - 1] && tc->command[position - 1] == '/')
		return (add_to_completion(autocomp, str, 0));
	command_completion(autocomp, str);
	path_completion(autocomp, str);

	return (autocomp->len > 0);
}

int		arg_completion(t_ab *autocomp, t_cap *tc, char *str, int position)
{

	if (is_env_var(autocomp, str))
	{
		return (env_completion(autocomp, str));
	}
	else if (tc->command[position - 1] && tc->command[position - 1] == '/')
	{
		add_to_completion(autocomp, str, 0);
		return (1);
	}
	path_completion(autocomp, str);
	return (autocomp->len > 0);
}

int		smart_completion(t_ab *autocomp, t_cap *tc, int position)
{
	char str[MAX_PATH];

	get_word(tc, position, str);
	if (!*str)
		return (0);
	autocomp->len = 0;
	get_quote(autocomp, str);
	if (is_first_argi(tc, position))
	{
		dprintf(debug(), "firstarg: |%s|\n", str);
		return (first_arg_completion(autocomp, tc, str, position));
	}
	else
	{
		dprintf(debug(), "arg: |%s|\n", str);
		return (arg_completion(autocomp, tc, str, position));
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
		add_to_completion(autocomp, ".", 0);
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

	autocomp->max_offset = 0;
	autocomp->len = 0;
	autocomp->isdir = 0;
	ft_bzero(autocomp->after, MAX_PATH);
	ft_bzero(autocomp->match, MAX_PATH);
	if (!get_words_completion(autocomp, tcap))
		return (0);
	dprintf(debug(), "len |%d|\n", autocomp->len);
	if (!autocomp->len)
	{
		tputs(tcap->sound, 1, ft_put_termcaps);
		return (0);
	}
	if (autocomp->len > 50)
	{
		tputs(tcap->sound, 1, ft_put_termcaps);
		return (0);
	}
	else if (autocomp->len == 1)
	{
		int i = ft_strlen(g_shell->autocomp->match);
		while (i--)
			ft_delete_back(tcap);
		ft_insert(g_shell->autocomp->data[0], tcap);
		if(g_shell->autocomp->after[0] && !g_shell->autocomp->isdir)
			ft_insert(g_shell->autocomp->after, tcap);
		return (1);
	}
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
