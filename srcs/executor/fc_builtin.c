/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 02:02:47 by aben-azz          #+#    #+#             */
/*   Updated: 2019/09/28 06:24:41 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*

fc -e vim
- ouvre la derniere commande dans un fichier temporaire avec vim. Quand on quitte en sauvegardant sur vim, la commande est executée.

fc -e vim X
- X est un nombre, ouvre la commande avec lindex X dans l'historique et fait pareil que fc -e vim

fc -e vim X Y
- ouvre les commandes dans lhistorique des index x a y pareil que fc -e vim X

fc -re vim X Y
- pareil quen haut sauf que cest inverse

fc -l
- liste les 16 derniere commandes dans lhistorique

fc -l X Y

- liste les commandes dans lhistorique aux index X a Y

fc -nl
- retire les index dans la liste
fc -lr X Y
- pareil en reverse

fc X=NaN
- cherche la derniere commande commencant par X;
fc -l X=NaN
- affiche depuis la derniere commande commencant par X

fc -l chien chat
- affiche une liste des commandes a partir dune commande commencant par chien jusqua lindex dune commande commencant par chat


DEUX COMMANDES FC PAREILLES


"fc -lr bite 10807" == "fc -l 10807 bite"
"fc -e - X Y" == "fc -s X Y"

r e n s l

R:
	doit etre avec l ou sans rien
E:
	peut etre seul
N:
	doit etre avec L
L:
	peut pas etre avec E
	peut etre avec R et/ou N
S:
	doit etre seul

*/


#define FC_OPTIONS "erlns"
#define FC_EDITOR (1 << 0)
#define FC_REVERSE (1 << 1)
#define FC_LIST (1 << 2)
#define FC_NO_NUMBER (1 << 3)
#define FC_NO_EDITOR (1 << 4)




int		get_param(int argc, char **argv)
{
	int param;
	int i;
	int j;
	int index;

	i = 0;
	param = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1])
		{
			j = 0;
			while (argv[i][++j])
			{
				if (~(index = ft_indexof(FC_OPTIONS, argv[i][j])))
					param |= (1 << index);
				else
					return (-1);
			}
		}
		return (argv[i][0] == '-' && !argv[i][1] ? -1: param);
	}
	return (param);
}

int		check_compatibility(int p)
{
	if (p & FC_EDITOR)
		return (!(p & FC_LIST || p & FC_NO_EDITOR || p & FC_NO_NUMBER) - 1);
	else if (p & FC_LIST)
		return (!(p & FC_EDITOR || p & FC_NO_EDITOR) - 1);
	else if (p & FC_NO_EDITOR)
		return (!(p & FC_LIST || p & FC_EDITOR || p & FC_NO_NUMBER ||
														p & FC_REVERSE) - 1);
	return (1);
}


int	debug_param(int param)
{
	if (!param) return ft_printf("Aucune option\n");
	ft_printf("-");
	if (param & FC_EDITOR) ft_printf("E");
	if (param & FC_REVERSE) ft_printf("R");
	if (param & FC_LIST) ft_printf("L");
	if (param & FC_NO_NUMBER) ft_printf("N");
	if (param & FC_NO_EDITOR) ft_printf("S");
	ft_printf("\n");
	return (1);
}

int	get_history_index(int x, int y, int p)
{
	int			index;
	int			max;
	int			tmp;
	t_history	*history;

	history = g_shell->history;
	max = ~y ? ft_max(0, x) : history->len - 1;
	index = ~y ? ft_max(0, y) : x;
	if (max >= history->len || index >= history->len)
		return (-2);
	else if (!x || !y)
		return (-3);
	if (p & FC_REVERSE)
	{
		tmp = max;
		max = index;
		index = tmp;
	}
	if (max > index)
	{
		while (max >= index)
		{
			if (!(p & FC_NO_NUMBER))
				ft_printf("%d	", max);
			ft_printf("%s\n", history->data[max]);
			max--;
		}
		return (0);
	}
	while (max <= index)
	{
		if (!(p & FC_NO_NUMBER))
			ft_printf("%d	", max);
		ft_printf("%s\n", history->data[max]);
		max++;
	}
	return (0);
}

int find_first_occurrence(char *string)
{
	int			i;
	t_history	*history;

	history = g_shell->history;
	i = history->len -1;
	while (i--)
		if (!ft_strncmp(string, history->data[i], ft_strlen(string)))
			return (i);
	return (-1);
}

void	arg_to_number(char *str, char *str2, int *index, int *max)
{
	int a;
	int b;

	a = ft_atoi(str);
	b = str2 ? ft_atoi(str2) : -1;
	if (index)
		*index = a ? a : find_first_occurrence(str);
	if (max)
		*max = b ? b : find_first_occurrence(str2);
}

int		fc_list(int ac, char **av, int param)
{
	int index;
	int max;
	int i;

	index = 0;
	max = 0;
	if (ac == 2)
		return get_history_index(g_shell->history->len - 17,
	g_shell->history->len - 1, param);
	i = 1;
	while (i < ac && (av[i][0] == '-' && (av[i][1] && !ft_isdigit(av[i][1]))))
		i++;
	if (i == ac - 1 || i == ac - 2)
	{
		arg_to_number(av[i], i == ac - 2 ? av[i + 1] : NULL, &index, &max);
		if (~index && ~max)
			return get_history_index(index, max, param);
		else
			ft_printf("occurrence non trouvee\n");
	}
	else
		return ft_printf("So many argument frr\n");
	return (0);
}

void	fc_execute_command(int index, char *string)
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
		//ft_printf("On va execute direct: '%s'\n", string);
		lex_del_list(&g_shell->lexer);
		if (add_cmd_to_history(string, history) == -1)
			return ;
		handler(string);
	}
}

int		fc_replace_command(int ac, int b, char **av)
{
	int		i;
	int		index;
	char	*replace;
	char	*command;
	int		to;

	index = -1;
	i = b;
	while (i < ac && ~(index = ft_indexof(av[i], '=')))
		i++;

	i == ac ? to = ft_max(g_shell->history->len - 2, 0) :
									arg_to_number(av[i], NULL, &to, NULL);
	//ft_printf("ac: %d, i: %d, b: %d, to: %d\n", ac, i, b, to);
	if (!~to || to > g_shell->history->len - 1 || !g_shell->history->len)
		return (1);
	if (!(command = ft_strnew(ft_strlen(g_shell->history->data[to]) + 1)))
		return (1);
	ft_strcpy(command, g_shell->history->data[to]);
	command[ft_strlen(g_shell->history->data[to])] = '\n';
	//ft_printf("to vaut '%s' %d\n", command, to);
	i = b - 1;
	//ft_printf("on a un replace, notre mot est {%s}, %d/%d\n", av[i], i, ac);
	while (++i < ac && ~(index = ft_indexof(av[i], '=')))
	{
		char *with = ft_strdup(av[i] + index + 1);
		char *orig = ft_strnew(index);
		ft_strncpy(orig, av[i], index);
		replace = ft_strreplace2(command, orig, with);
		//ft_printf("{%s} replace '%s' par '%s' == {%s}\n", command, orig, with, replace);
		ft_strdel(&command);
		command = ft_strdup(replace);
		ft_strdel(&replace);
	}
	fc_execute_command(-1, command);
	ft_strdel(&command);
	return (0);
}

int		fc_no_editor(int ac, char **av)
{
	int index;
	int max;
	int i;

	index = 0;
	max = 0;
	//ft_printf("ac: %d\n", ac);
	if (ac == 2)
		fc_execute_command(g_shell->history->len - 2, NULL);// run last command
	else
	{
		i = 1;
		while (i < ac && !~ft_indexof(av[i], '='))
			i++;
		if (i == ac || i > 2)
		{
			arg_to_number(av[2], NULL, &index, &max);
			fc_execute_command(index, NULL);//1 argument: cmd
		}
		else
			fc_replace_command(ac, i, av);//2argument
	}
	return (0);
}

int		handle_error(int code)
{
	(void)code;

	return (code);
}

int		fc_builtin(int argc, char **argv)
{
	int param;

	if (!~(param = get_param(argc, argv)) || !~check_compatibility(param))
	{
		ft_printf("%s\n%s\n%s\n%s\n",
			"Error: invalid options.",
			"Usage: fc [-r] [-e editor] [first [last]]",
			"fc -l [-nr] [first [last]]",
			"fc -s [old=new] [first]");
		return (1);
	}
	debug_param(param);
	if (param & FC_LIST)
		return (handle_error(fc_list(argc, argv, param)));
	else if (param & FC_NO_EDITOR)
		return (handle_error(fc_no_editor(argc, argv)));
	return (0);
}

/*
	echo test oui
		// test oui
	fc -s oui=non echo
		// test non
*/
