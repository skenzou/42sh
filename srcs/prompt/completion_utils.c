/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 06:02:13 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/22 20:14:32 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	create_file(char *name, char *path, t_ab *comp, int onlydir)
{
	t_stat		stats;
	char full_path[MAX_PATH];
	char file[MAX_PATH];

	ft_bzero(file, MAX_PATH);
	cat_fullpath(full_path, name, path);
	lstat(full_path, &stats);
	if ((comp->isdir = (file_name_ext(name, stats, file) == 'd')) || !onlydir)
	{
		comp->data[comp->len++] = ft_strdup(file);
		comp->max_offset = ft_max(comp->max_offset, ft_strlen(file));
	}
}

int		add_to_completion(t_ab *autocomp, char *path, int onlydir)
{
	t_dirent	*d;
	DIR			*dir;
	char		final_path[MAX_PATH];

	final_path[0] = 0;
	get_tilde(path, final_path);
	if ((dir = opendir(final_path)))
	{
		while ((d = readdir(dir)))
		{
			if (d->d_name[0] != '.' &&
			!ft_strncmp(d->d_name, autocomp->match, ft_strlen(autocomp->match)))
				create_file(d->d_name, final_path, autocomp, onlydir);
		}
		closedir(dir);
		return (1);
	}
	else
		dprintf(debug(), "probleme opendir\n");
	return (0);
}



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
int		first_arg_completion(t_ab *autocomp, t_cap *tc, char *str, int position)
{
	if (is_env_var(autocomp, str))
		return (env_completion(autocomp, str));
	else if (tc->command[position - 1] && tc->command[position - 1] == '/')
		return (add_to_completion(autocomp, str, 0));
	command_completion(autocomp, str);
	path_completion(autocomp, str);
	return (autocomp->len > 0);
}


int		print_name(t_ab *autocomp, char *str, int i)
{
	if (i == autocomp->pos)
		ft_putstr("\x1b[7m");
	ft_putstr(str);
	if (i == autocomp->pos)
		ft_putstr("\x1b[0m");
	ft_move(g_shell->tcap, "!right", autocomp->max_offset - ft_strlen(str) + 2);
	return (1);
}

char	file_name_ext(char *string, t_stat stats, char *name)
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
	return (ext);
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



int		is_first_argi(t_cap *tc, int position)
{
	int i;

	if (!get_argi(tc, position))
		return (1);
	i = position - 1;
	while (i)
	{
		if (tc->command[i] == ' '
				&& (tc->command[i - 1] && !is_separator(tc->command, i - 1)))
			return (0);
		else if (is_separator(tc->command, i))
			return (1);
		i--;
	}
	return (0);
}


int		is_env_var(t_ab *autocomp, char *path)
{
	int		i;
	char	copy[MAX_PATH];

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
