/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 06:02:13 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/05 06:12:12 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		init_autocomp(t_cap *tcap, t_ab *autocomp)
{
	int max_offset;

	max_offset = autocomp->max_offset;
	autocomp->state = 1;
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

void comp_path(t_cap *tcap, char *path)
{
	char complet_path[MAX_PATH_LEN];
	t_ab *autocomp;

	autocomp = g_shell->autocomp;
	(void)tcap;
	(void)path;
	dprintf(debug(), "pathxd: |%s|\n",  path);
	int i;
	int j;
	t_dirent	*d;
	DIR			*dir;

	ft_bzero(complet_path, MAX_PATH_LEN);
	i = 0;
	j = 0;
	while (path[i])
	{
		if (path[i] != '\\')
			complet_path[j++] = path[i];
		i++;
	}
	autocomp->len = 0;
	autocomp->max_offset = 0;
	autocomp->match = ft_strdup(complet_path);
	//ft_bzero(autocomp->data, sizeof(autocomp->data));
	if ((dir = opendir(complet_path)))
		while ((d = readdir(dir)))
		{
			if (d->d_name[0] != '.')
			{
				create_file(d->d_name, path, autocomp);
				//dprintf(debug(), "autocomp->data: |%s|\n", autocomp->data[autocomp->len]);
				autocomp->max_offset =
						ft_max(autocomp->max_offset,
									ft_strlen(autocomp->data[autocomp->len]));
				autocomp->len++;

			}
		}
}

void ft_insert_path(char *path, t_cap *tcap)
{
	int i;
	char c[3];

	ft_bzero(c, 3);
	i = 0;
	while (path[i])
	{
		c[0] = path[i];
		if (c[0] == ' ')
		{
			c[0] = '\\';
			c[1] = ' ';
		}
		ft_insert(c, tcap);
		ft_bzero(c, 3);
		i++;
	}
	ft_insert("/", tcap);
}

int get_end_words(t_cap *tcap, int index)
{
	int i = index - 1;
	char comp[BUFFSIZE];
	int len;
	t_dirent	*d;
	DIR			*dir;

	len = 0;
	while (ft_isprint(tcap->command[i]) &&
		(!ft_isspace(tcap->command[i]) || tcap->command[i - 1] == '\\'))
		i--;
	ft_bzero(comp, BUFFSIZE);
	ft_strncpy(comp, tcap->command + i + 1, index - 1 - i);
	if (tcap->command[index - 1] == '/')
	{
		comp_path(tcap, comp);
		return (1);
	}
	len = ft_strlen(comp);
	if ((dir = opendir(".")))
		while ((d = readdir(dir)))
		{
			if (!ft_strncmp(d->d_name, comp, len))
			{
				while (len--)
					ft_delete_back(tcap);
				ft_insert_path(d->d_name, tcap);
				closedir(dir);
				return (0);
			}
		}
	closedir(dir);
	return (-1);
}


int is_first_arg(t_cap *tcap, int pos)
{
	int index_separator;

	index_separator = 0;
	if (tcap->char_len == pos)
		return (1);
	else if (~(index_separator = ft_indexof(tcap->command, ' ')))
	{
		//dprintf(debug(), "separator: %d\n", index_separator);
		if (pos - 1 < index_separator)
			return (1);
	}
	return (0);
}


int get_command_comp(t_cap *tcap, int index)
{
	int i = index - 1;
	int len;
	t_dirent	*d;
	DIR			*dir;
	t_ab *autocomp;

	autocomp = g_shell->autocomp;

	len = 0;
	while (ft_isprint(tcap->command[i]) &&
		(!ft_isspace(tcap->command[i]) || tcap->command[i - 1] == '\\'))
		i--;
	ft_bzero(autocomp->comp, BUFFSIZE);
	ft_strncpy(autocomp->comp, tcap->command + i + 1, index - 1 - i);
	dprintf(debug(), "comamnd comp |%s|\n", autocomp->comp);
	len = ft_strlen(autocomp->comp);
	char *path = getenv("PATH");
	autocomp->len = 0;
	autocomp->max_offset = 0;
	autocomp->type = 1;
	if (path)
	{
		char **split_path = ft_strsplit(path, ':');
		while (*split_path)
		{
			if ((dir = opendir(*split_path)))
				while ((d = readdir(dir)))
				{
					//dprintf(debug(), "dir |%s|, %s\n", *split_path, d->d_name);
					if (!ft_strncmp(d->d_name, autocomp->comp, len))
					{
						if (d->d_name[0] != '.')
						{
							create_file(d->d_name, path, autocomp);
							//dprintf(debug(), "autocomp->data: |%s|\n", autocomp->data[autocomp->len]);
							autocomp->max_offset =
									ft_max(autocomp->max_offset, ft_strlen(autocomp->data[autocomp->len]));
							autocomp->len++;
						}
					}
				}
			split_path++;
		}
	}
	return (1);
}

int get_dir_content(t_cap *tcap, int index)
{
	int i = index - 1;
	int len;
	t_dirent	*d;
	DIR			*dir;
	char directory[BUFFSIZE];
	char tmp[BUFFSIZE];
	t_ab *autocomp;
	autocomp = g_shell->autocomp;

	len = 0;
	while (ft_isprint(tcap->command[i]) &&
		(!ft_isspace(tcap->command[i]) || tcap->command[i - 1] == '\\'))
		i--;
	ft_bzero(tmp, BUFFSIZE);
	ft_strncpy(tmp, tcap->command + i + 1, index - 1 - i);
	int in;
	if (~(in = ft_lastindexof(tmp, '/')))
	{
		autocomp->len = 0;
		autocomp->max_offset = 0;
		autocomp->type = 1;
		ft_bzero(autocomp->comp, BUFFSIZE);
		ft_strcpy(autocomp->comp, tmp + in + 1);
		len = ft_strlen(autocomp->comp);
		ft_bzero(directory, BUFFSIZE);
		ft_strncpy(directory, tmp, ft_strlen(tmp) - ft_strlen(autocomp->comp));
		dprintf(debug(), "directory |%s|, content: |%s|\n", autocomp->comp, directory);
		if ((dir = opendir(directory)))
			while ((d = readdir(dir)))
			{
				if (!ft_strncmp(d->d_name, autocomp->comp, len))
				{
					create_file(d->d_name, directory, autocomp);
					//dprintf(debug(), "autocomp->data: |%s|\n", autocomp->data[autocomp->len]);
					autocomp->max_offset =
							ft_max(autocomp->max_offset, ft_strlen(autocomp->data[autocomp->len]));
					autocomp->len++;
				}
			}
		closedir(dir);
		return (1);
	}
	dprintf(debug(), "ici xd\n");
	return (0);
}

int		get_words_completion(t_ab *autocomp, t_cap *tcap)
{
	char **argv;
	int i;
	int ret;

	ret = 0;
	(void)autocomp;
	i = tcap->cursy * (tcap->cursx_max + 1) + (tcap->cursx) - tcap->prompt_len;
	argv = ft_strsplit(tcap->command, ' ');
	if (i && ft_isspace(tcap->command[i - 1]) && (i + 1 < tcap->char_len &&
											ft_isspace(tcap->command[i + 1])))
	{
		dprintf(debug(), "|%c| Space aucun mot\n", tcap->command[i]);
		return (0);
	}
	else if ((ft_isspace(tcap->command[i]) && (i + 1 < tcap->char_len &&
											ft_isprint(tcap->command[i - 1]))))
	{
		dprintf(debug(), "|%c| Printable fin de mot\n", tcap->command[i]);
		if (~(ret = get_end_words(tcap, i)))
		{
			dprintf(debug(), "ret: %d\n", ret);
			autocomp->type = 0;
			return (ret);
		}
		else if (get_dir_content(tcap, i))
		{
			return (1);
		}
		else
		{
			if (is_first_arg(tcap, i))
			{
				if (get_command_comp(tcap, i))
				{
					return (1);
				}
			}
		}
	}
	else if ((i && ft_isspace(tcap->command[i - 1])) || !i)
	{
		dprintf(debug(), "|%c| Printable debut de mot\n", tcap->command[i]);
		return (0);
	}
	else if (i == tcap->char_len)
	{
		dprintf(debug(), "|%c| Printable fin de ligne\n", tcap->command[i]);
		if (~(ret = get_end_words(tcap, i)))
		{
			dprintf(debug(), "ret: %d\n", ret);
			autocomp->type = 0;
			return (ret);
		}
		else if (get_dir_content(tcap, i))
		{
			return (1);
		}
		else
		{
			if (is_first_arg(tcap, i))
			{
				if (get_command_comp(tcap, i))
				{
					return (1);
				}
			}
		}
	}
	else
	{
		dprintf(debug(), "|%c| Printable dans le mot\n", tcap->command[i]);
		return (0);
	}
	tputs(tcap->sound, 1, ft_put_termcaps);
	return (0);
}

// void		get_current_dir_completion(t_ab *autocomp, char *path)
// {
// 	t_dirent	*d;
// 	DIR			*dir;
//
// 	autocomp->len = 0;
// 	autocomp->max_offset = 0;
// 	ft_bzero(autocomp->data, sizeof(autocomp->data));
// 	if ((dir = opendir(".")))
// 		while ((d = readdir(dir)))
// 		{
// 			if (d->d_name[0] != '.')
// 			{
// 				autocomp->data[autocomp->len] = create_file(d->d_name, path);
// 				autocomp->max_offset =
// 								ft_max(autocomp->max_offset, ft_strlen(d->d_name));
// 				autocomp->len++;
// 			}
// 		}
// 	closedir(dir);
// }

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
