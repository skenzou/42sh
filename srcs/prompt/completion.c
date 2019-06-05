/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 06:02:13 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/05 05:09:54 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		init_autocomp(t_cap *tcap, t_ab *autocomp)
{
	int max_offset;

	(void)tcap;
	max_offset = autocomp->max_offset;
	autocomp->row = g_shell->tcap->cursx_max / (ft_max(max_offset + 2, 1));
	autocomp->col = autocomp->len / ft_max(autocomp->row, 1);
	autocomp->carry = autocomp->len % ft_max(autocomp->row, 1);
	return (max_offset);
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

static void		cat_fullpath(t_file *file, char *name, char *path)
{
	ft_bzero((void *)&(file->full_path), MAX_PATH);
	if (path)
	{
		ft_strcpy(file->full_path, path);
		if (*path != '/' || *(path + 1))
			ft_strcat(file->full_path, "/");
	}
	ft_strcat(file->full_path, name);
	file->name = ft_strdup(name);
	!file->name ? exit(1) : 0;
	file->path = path;
}

t_file			create_file(char *name, char *path)
{
	t_file		file;

	ft_bzero((void *)&file, sizeof(t_file));
	cat_fullpath(&file, name, path);
	lstat(file.full_path, &(file.stats));
	return (file);
}

void		get_words_completion(t_ab *autocomp, t_cap *tcap)
{
	(void)autocomp;
	char **argv;
	int i;

	i = (tcap->cursx - tcap->prompt_len);
	argv = ft_strsplit(tcap->command, ' ');
	if (i && ft_isspace(tcap->command[i - 1]) && (i + 1 < tcap->char_len &&
											ft_isspace(tcap->command[i + 1])))
	{
		dprintf(debug(), "|%c| Space aucun mot\n", tcap->command[i]);
	}
	else if ((ft_isspace(tcap->command[i]) && (i + 1 < tcap->char_len &&
											ft_isprint(tcap->command[i - 1]))))
	{
		dprintf(debug(), "|%c| Printable fin de mot\n", tcap->command[i]);
	}
	else if ((i && ft_isspace(tcap->command[i - 1])) || !i)
	{
		dprintf(debug(), "|%c| Printable debut de mot\n", tcap->command[i]);
	}
	else if (i == tcap->char_len)
	{
		dprintf(debug(), "|%c| Printable fin de ligne\n", tcap->command[i]);
	}
	else
	{
		dprintf(debug(), "|%c| Printable dans le mot\n", tcap->command[i]);
	}
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
	// int row;
	// int col;
	// int i;

	get_words_completion(autocomp, tcap);
	// init_autocomp(tcap, autocomp);
	// i = 0;
	// col = -1;
	// tputs(tcap->clr_all_line, 1, ft_put_termcaps);
	// ft_move(tcap, "down", 1);
	// while (++col < autocomp->col)
	// {
	// 	row = -1;
	// 	while (++row < autocomp->row)
	// 		print_name(autocomp, autocomp->data[i].name, i) && i++;
	// 	ft_move(tcap, "down", 1);
	// }
	// if (autocomp->carry > 0)
	// {
	// 	row = autocomp->carry;
	// 	while (row--)
	// 		print_name(autocomp, autocomp->data[i].name, i) && i++;
	// }
	// ft_replace_cursor(tcap);
	// i = 0;
	// while (i < autocomp->col + (autocomp->carry > 0 ? 1 : +1))
	// {
	// 	ft_move(tcap, "up", 1);
	// 	i++;
	// }
	return (1);
}
