/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:30:30 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/03 23:22:54 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"



void		ft_expand(char **args)
{
	int i;
	int count;
	int j;

	if (!args || !*args)
		return ;
	i = -1;
	count = ft_split_count(args);
	while(args[++i])
	{
		tilde_expansion(&args[i]);
		param_expansion(&args[i]);
		remove_quote(&args[i]);
	}
	i = -1;
	while (++i < count)
		if (args[i] == NULL)
		{
			j = i - 1;
			while (++j < count - 1)
				args[j] = args[j + 1];
			args[j] = NULL;
		}
}
