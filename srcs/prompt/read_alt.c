/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_alt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 17:30:02 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/25 23:50:47 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_alt(char *key)
{
	if (key[0] == -61 && key[1] == -89 && key[2] == 0)
	{
		return (ft_copy(g_shell->tcap));
	}
	else if (key[0] == -30 && key[1] == -119 &&
		key[2] == -120)
	{
		return (ft_cut(g_shell->tcap));
	}
	else if (key[0] == -30 && key[1] == -120 &&
		key[2] == -102)
	{
		return (ft_paste(g_shell->tcap));
	}
	return (-1);
}
