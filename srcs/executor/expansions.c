/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:30:30 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/29 17:14:16 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"



void		ft_expand(char **args)
{
	int i;

	i = -1;
	while(args[++i])
	{
		tilde_expansion(&args[i]);
		// param_expansion(&args[i]);
		remove_quote(&args[i]);
	}
}
