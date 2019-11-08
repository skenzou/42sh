/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 07:33:58 by aben-azz          #+#    #+#             */
/*   Updated: 2019/11/08 01:51:20 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	find_first_occurrence(char *string)
{
	int			i;
	t_history	*history;

	history = g_shell->history;
	i = history->len - 1;
	while (i--)
		if (!ft_strncmp(string, history->data[i], ft_strlen(string)))
			return (i);
	return (-1);
}

char		*randomize_path(char *path)
{
	char	*ret;
	char	*random;

	if ((random = ft_itoa(ft_rand(10000))))
	{
		ret = ft_strcjoin(path, random, '/');
		ft_strdel(&random);
		random = ret;
	}
	return (random);
}

void		arg_to_number(char *str, char *str2, int *index, int *max)
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

int			get_param(int argc, char **argv)
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
		else
			return (argv[i][0] == '-' && !argv[i][1] ? -1 : param);
	}
	return (param);
}

int			check_compatibility(int p)
{
	if (p & FC_EDITOR)
		return (!(p & FC_LIST || p & FC_NO_EDITOR || p & FC_NO_NUMBER) - 1);
	else if (p & FC_LIST)
		return (!(p & FC_EDITOR || p & FC_NO_EDITOR) - 1);
	else if (p & FC_NO_EDITOR)
		return (!(p & FC_LIST || p & FC_EDITOR || p & FC_NO_NUMBER
													|| p & FC_REVERSE) - 1);
		return (1);
}
