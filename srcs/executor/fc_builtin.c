/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 02:02:47 by aben-azz          #+#    #+#             */
/*   Updated: 2019/09/26 07:34:40 by aben-azz         ###   ########.fr       */
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
- pareil quen haut sauf que cest inversé

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
				{
					param |= (1 << index);
				}
				else
					return (-1);
			}
		}
		else if (argv[i][0] == '-' && !argv[i][1])
			return (-1);
		else
			return (param);
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
    if (!param)
        return ft_printf("Aucune option\n");
    ft_printf("-");
    if (param & FC_EDITOR) {
        ft_printf("E");
    }
    if (param & FC_REVERSE) {
        ft_printf("R");
    }
    if (param & FC_LIST) {
        ft_printf("L");
    }
    if (param & FC_NO_NUMBER) {
        ft_printf("N");
    }
    if (param & FC_NO_EDITOR)
        ft_printf("S");
    ft_printf("\n");
    return (1);
}

int	get_history_index(int x, int y)
{
	int		index;
	int		max;

	max = ~y ? ft_max(0, ft_max(x,y)) : g_shell->history->len - 1;
	index = ~y ? ft_max(0, ft_min(x,y)) : x;
	if (max >= g_shell->history->len || index >= g_shell->history->len)
		return (-2);
	else if (!x || !y)
	    return (-3);
    while (index <= max)
    {
        ft_printf("%d    %s\n", index, g_shell->history->data[index]);
        index++;
    }
	return (1);
}

int find_first_occurrence(char *string)
{
    int i;
    t_history *history;

    history = g_shell->history;
    i = history->len -1;
    while (i--)
    {
        if (!ft_strncmp(string, history->data[i], ft_strlen(string)))
            return (i);
    }
    return (-1);
}

void	arg_to_number(char *str, char *str2, int *index, int *max)
{
    int a;
    int b;

    a = ft_atoi(str);
    if (!str2)
        b = -1;
    else
        b = ft_atoi(str2);
    *index = a ? a : find_first_occurrence(str);
    *max = b ? b : find_first_occurrence(str2);
}

int		fc_list(int argc, char **argv, int param)
{
    (void)argv;
    (void)param;
    int index;
    int max;

    index = 0;
    max = 0;
    if (argc == 2)
        return get_history_index(g_shell->history->len - 17, g_shell->history->len - 1);
    int i;

    i = 1;
    while (i < argc && argv[i][0] == '-')
        i++;
    if (i == argc - 1 || i == argc - 2)
    {
        arg_to_number(argv[i], i == argc - 2 ? argv[i + 1] : NULL, &index, &max);
        if (~index && ~max)
            get_history_index(index, max);
        else
            ft_printf("occurrence non trouvée\n");
    }
    else
        return ft_printf("So many argument frr\n");
    ft_printf("plusieurs: ca commence a %d/%d: {%s}\nindex: %d, max: %d", i,argc, argv[i], index, max);
    return (1);
}

int		fc_builtin(int argc, char **argv)
{
	int param;

	if (!~(param = get_param(argc, argv)) || !~check_compatibility(param))
	{
		ft_printf("%s\n%s\n%s\n%s\n", "Error: invalid options.",
		"Usage: fc [-r][-e editor] [first[last]]",
		"fc -l[-nr] [first[last]]",
		"fc -s[old=new][first]");
		return (1);
	}
	debug_param(param);
	if (param & FC_LIST)
	{
        fc_list(argc, argv, param);
		//int a = get_history_index(argc > 2);
		//ft_printf("result: %d\n", a);
	}
	ft_printf("Fc builtin %d\n", argc);
	return (1);
}