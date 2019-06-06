/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 06:02:13 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/05 06:12:12 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_copy(t_cap *tcap)
{
	int i;

	i = tcap->cursy * (tcap->cursx_max + 1) + (tcap->cursx) - tcap->prompt_len;
	t_cc *copy_cut;
	copy_cut = g_shell->copy_cut;
	if (copy_cut->state)
	{
		copy_cut->to = i;
		if (copy_cut->to > copy_cut->from)
		{
			ft_bzero(copy_cut->copied, BUFFSIZE);
			ft_strncpy(copy_cut->copied, tcap->command + copy_cut->from, copy_cut->to - copy_cut->from);
		}
		copy_cut->state = 0;
	}
	else
	{
		copy_cut->from = i;
		copy_cut->state = 1;
	}
	return (1);
}


int		ft_cut(t_cap *tcap)
{
	int i;

	i = tcap->cursy * (tcap->cursx_max + 1) + (tcap->cursx) - tcap->prompt_len;
	t_cc *copy_cut;
	int a = -1;
	copy_cut = g_shell->copy_cut;
	if (copy_cut->state)
	{
		copy_cut->to = i;
		if (copy_cut->to > copy_cut->from)
		{
			ft_bzero(copy_cut->copied, BUFFSIZE);
			ft_strncpy(copy_cut->copied, tcap->command + copy_cut->from, copy_cut->to - copy_cut->from);
			while (++a < (int)ft_strlen(copy_cut->copied))
				ft_delete_back(tcap);
		}
		copy_cut->state = 0;
	}
	else
	{
		copy_cut->from = i;
		copy_cut->state = 1;
	}
	return (1);
}

int		ft_paste(t_cap *tcap)
{
	return (ft_insert(g_shell->copy_cut->copied, tcap));
}
