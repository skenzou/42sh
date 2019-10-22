/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtin_subst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 07:32:50 by aben-azz          #+#    #+#             */
/*   Updated: 2019/09/28 07:50:40 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void				fc_execute_command(int index, char *string)
{
	t_history	*history;
	char		*command;

	history = g_shell->history;
	if (~index)
	{
		if (!~index || index > history->len - 1 || !history->len)
			return ;
		if (!(command = ft_strnew(ft_strlen(history->data[index]) + 1)))
			return ;
		ft_strcpy(command, history->data[index]);
		command[ft_strlen(history->data[index])] = '\n';
		lex_del_list(&g_shell->lexer);
		if (add_cmd_to_history(command, history) == -1)
			return ;
		handler(command);
		ft_strdel(&command);
	}
	else
	{
		lex_del_list(&g_shell->lexer);
		if (add_cmd_to_history(string, history) == -1)
			return ;
		handler(string);
	}
}

static inline void		fc_replace(int b, char **command, char **av, int ac)
{
	int		i;
	char	*replace;
	int		index;
	char	*orig;

	i = b - 1;
	while (++i < ac && ~(index = ft_indexof(av[i], '=')))
	{
		orig = ft_strnew(index);
		ft_strncpy(orig, av[i], index);
		replace = ft_strreplace(*command, orig, ft_strdup(av[i] + index + 1));
		ft_strdel(command);
		*command = ft_strdup(replace);
		ft_strdel(&replace);
	}
	fc_execute_command(-1, *command);
	ft_strdel(command);
}

static int				fc_replace_in_command(int ac, int b, char **av)
{
	int		i;
	int		index;
	char	*command;
	int		to;

	index = -1;
	i = b;
	while (i < ac && ~(index = ft_indexof(av[i], '=')))
		i++;
	i == ac ? to = ft_max(g_shell->history->len - 2, 0) :
									arg_to_number(av[i], NULL, &to, NULL);
	if (!~to || to > g_shell->history->len - 1 || !g_shell->history->len)
		return (1);
	if (!(command = ft_strnew(ft_strlen(g_shell->history->data[to]) + 1)))
		return (1);
	ft_strcpy(command, g_shell->history->data[to]);
	command[ft_strlen(g_shell->history->data[to])] = '\n';
	i = b - 1;
	fc_replace(b, &command, av, ac);
	return (0);
}

int						fc_no_editor(int ac, char **av)
{
	int index;
	int max;
	int i;

	index = 0;
	max = 0;
	if (ac == 2)
		fc_execute_command(g_shell->history->len - 2, NULL);
	else
	{
		i = 1;
		while (i < ac && !~ft_indexof(av[i], '='))
			i++;
		if (i == ac || i > 2)
		{
			arg_to_number(av[2], NULL, &index, &max);
			fc_execute_command(index, NULL);
		}
		else
			fc_replace_in_command(ac, i, av);
	}
	return (0);
}
