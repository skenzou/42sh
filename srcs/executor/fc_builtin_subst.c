/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtin_subst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 07:32:50 by aben-azz          #+#    #+#             */
/*   Updated: 2019/11/10 17:47:11 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int				fc_execute_command(int index, char *string)
{
	char		*command;

	if (~index)
	{
		if (!~index || index > HISTORY->len - 1 || !HISTORY->len)
			return (handle_error(FC_NO_HISTORY));
		if (!(command = ft_strnew(ft_strlen(HISTORY->data[index]) + 1)))
			return (handle_error(FC_MALLOC_ERR));
		ft_strcpy(command, HISTORY->data[index]);
		command[ft_strlen(HISTORY->data[index])] = '\n';
		lex_del_list(&g_shell->lexer);
		if (!~add_cmd_to_history(command, HISTORY))
			return (handle_error(FC_MALLOC_ERR) && !ft_strdel2(&command));
		handler(command);
		ft_strdel(&command);
	}
	else
	{
		if (!~add_cmd_to_history(string, HISTORY))
			return (handle_error(FC_MALLOC_ERR));
		lex_del_list(&g_shell->lexer);
		handler(string);
	}
	return (0);
}

static inline int		fc_replace(int b, char **command, char **av, int ac)
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
	i = fc_execute_command(-1, *command);
	ft_strdel(command);
	return (i);
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
		return (handle_error(FC_NO_HISTORY));
	if (!(command = ft_strnew(ft_strlen(g_shell->history->data[to]) + 1)))
		return (handle_error(FC_MALLOC_ERR));
	ft_strcpy(command, g_shell->history->data[to]);
	command[ft_strlen(g_shell->history->data[to])] = '\n';
	i = b - 1;
	return (fc_replace(b, &command, av, ac));
}

int						fc_no_editor(int ac, char **av)
{
	int index;
	int max;
	int i;

	index = 0;
	max = 0;
	if (ac == 2)
		return (fc_execute_command(g_shell->history->len - 2, NULL));
	i = 1;
	while (i < ac && !~ft_indexof(av[i], '='))
		i++;
	if (i == ac || i > 2)
	{
		arg_to_number(av[2], NULL, &index, &max);
		return (fc_execute_command(index, NULL));
	}
	return (fc_replace_in_command(ac, i, av));
}
