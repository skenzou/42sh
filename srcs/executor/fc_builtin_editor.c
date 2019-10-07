/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtin_editor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:37:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/07 22:42:47 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		write_in_file(char *file, int index, int max)
{
	int fd;
	t_history *history;
	int i;

	if (!(fd = open(file, O_RDWR | O_TRUNC |O_CREAT, 0666)))
		return (1);
	history = g_shell->history;
	if (!~index && !~max)
	{
		index = g_shell->history->len - 2;
		max = index + 1;
	}
	i = index;
	while (i < max)
	{
		ft_putstr_fd(history->data[i], fd);
		ft_putchar_fd(10, fd);
		//ft_printf("on ecrit: %s dans fd\n", history->data[i]);

		i++;
	}
	close(fd);
	return (0);
}

int		read_file(char *file)
{
	int ret;
	int fd;
	char *line;
	char *string;
	if (!(fd = open(file, O_RDONLY, 0666)))
		return (1);
	while ((ret = get_next_line(fd, &line, '\n')))
	{
		if (!(string = ft_strnew(ft_strlen(line) + 1)))
			return (1);
		ft_strcpy(string, line);
		string[ft_strlen(string)] = '\n';
		lex_del_list(&g_shell->lexer);
		//ft_printf("Line actuelle: {%s}\n", string);
		handler(string);
		//ft_strdel(&line);
	}
	return (1);
}

int		exec_command(char *editor, int index, int max)
{
	char **editors;
	int pid;

	if (!(editor = ft_strcjoin(editor, "/tmp/42shtmp", ' ')))
		return (1);
	if (!(editors = ft_strsplit(editor, ' ')))
		return (1);
	write_in_file("/tmp/42shtmp", index, max);
	if (!(pid = fork()))
	{
		if (!~execvp(editors[0], editors))
		{
			ft_putstr_fd("42sh: command not found: ", 2);
			ft_putstr_fd(editors[0], 2);
			ft_putchar_fd(10, 2);
			exit(1);
		}
	}
	else
	{
		wait(&pid);
		read_file("/tmp/42shtmp");
		//ft_printf("Process terminé\n");
	}
	return (1);
}

int		fc_editor(int argc, char **argv, int param)
{
	(void)argc;
	(void)argv;
	(void)param;
	char *fcedit;

	fcedit = get_key_value("FCEDIT", g_shell->env);
	int i = 1;
	while (i < argc && argv[i][0] == '-' && !~ft_indexof(argv[i], 'e'))
		i++;
	while (i < argc && argv[i + 1] && argv[i + 1][0] == '-' && argv[i + 1][1] == 'e')
		i++;
	ft_printf("%d/%d\n", i, argc);
	if (argc - 1 > i && argv[i + 1][0] == '-')
	{
		ft_printf("erreur param apres -e\n");
		return (1);
	}
	if (i == argc - 1)
	{
		ft_printf("Aucun argument\n");
	}

	else
	{
		i++;
		//ft_printf("ac: %d i: %d, arg: |%s| fcedit: %s\n", argc, i, argv[i], fcedit);
		if (argc - 1 > i)
			ft_printf("ya d args supp : {%s, %s}\n", argv[i + 1], argc - 1 - i == 2 ? argv[i + 2] : NULL);
		else
		{
			//ft_printf("Aucun argument, editeur: |%s|\n", argv[i]);
			exec_command(argv[i], -1, -1);
		}
	}

	//ft_printf("editor actif reverse :%d\n", (param & FC_REVERSE) > 0);
	return (0);
}
