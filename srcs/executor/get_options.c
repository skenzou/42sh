/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:33:33 by tlechien          #+#    #+#             */
/*   Updated: 2019/06/04 19:19:33 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
**	Bitwise stocking for flags
*/

int		ft_flags(char c, char *flags, char *opt)
{
	int				i;
	i = 0;
	while (opt[i])
	{
		if (c == opt[i])
		{
			*flags |= 1 << i;
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** Update the flags for every caracters in the string that is a valid option
** raise an error if the caracters isn't a valid flag.
*/

int		get_options(char *flags, char *opt, char *str, int (*usage)())
{
	int i;

	i = 1;
	while (str && str[i])
		if (!(ft_flags(str[i++], flags, opt)))
			return (usage(str[i - 1]));
	return (0);
}

/*
** Go through the parameters and register flags until it encounters
** a path or a '--'.
**
** return the iteration of the argument next to the flags.
*/

int		params(char **flags, int ac, char **av, int (*usage)())
{
	int i;

	i = 0;
	while (i < ac && av[i][0] == '-' && av[i][1] != '-' && av[i][1] != 0)
	{
		if (get_options(flags[0], flags[1], av[i++], usage))
			return (-1);
	}
	if (i < ac && av[i] && av[i][0] == '-' && av[i][1] == '-')
	{
		if (av[i][2])
			return (usage('-'));
		else
			i++;
	}
	return (i);
}
