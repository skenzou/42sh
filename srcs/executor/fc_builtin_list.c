/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtin_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 07:28:50 by aben-azz          #+#    #+#             */
/*   Updated: 2019/11/08 01:50:34 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static inline void	print_history(int max, int index, int p)
{
	t_history	*history;

	history = g_shell->history;
	if (max > index)
	{
		while (max >= index)
		{
			if (!(p & FC_NO_NUMBER))
				ft_printf("%d	", max);
			ft_printf("%s\n", history->data[max]);
			max--;
		}
		return ;
	}
	while (max <= index)
	{
		if (!(p & FC_NO_NUMBER))
			ft_printf("%d	", max);
		ft_printf("%s\n", history->data[max]);
		max++;
	}
}

static int			get_history_index(int x, int y, int p, int list)
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
	if (list)
		print_history(max, index, p);
	return (0);
}

int					fc_process_list(int i, int ac, char **av, int param)
{
	int len;
	int index;
	int max;

	index = 0;
	max = 0;
	len = g_shell->history->len;
	(param & FC_REVERSE && i == ac) && i--;
	arg_to_number(av[i], i == ac - 2 ? av[i + 1] : NULL, &index, &max);
	if (index > len)
		return (err_display("no such event\n", NULL, NULL));
	if (~index)
		return (get_history_index(index, ~max ?
								ft_min(max, len - 1) : len - 1, param, 1));
	else
		ft_printf("occurrence non trouvee\n");
	return (0);
}

int					fc_list(int ac, char **av, int param)
{
	int i;
	int len;

	len = g_shell->history->len;
	i = 1;
	if (ac == 2)
		return (get_history_index(len - 17, len - 1, param, 1));
	while (i < ac && (av[i][0] == '-' && (av[i][1] && !ft_isdigit(av[i][1]))))
		i++;
	if (i == ac - 1 || i == ac - 2 || ((param & FC_REVERSE) && i == ac))
		return (fc_process_list(i, ac, av, param));
	else
		return (ft_printf("fc: so many argument\n"));
	return (0);
}
