/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_cut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 06:02:13 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/26 00:19:55 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int					ft_copy(t_cap *tc)
{
	int		i;
	t_cc	*copy;

	i = tc->cursy * (tc->cursx_max + 1) + (tc->cursx) - tc->prompt_len;
	copy = g_shell->copy_cut;
	if (copy->type != 0 && ~copy->type)
		return (1);
	if (copy->state)
	{
		copy->to = i;
		if ((copy->type = -1) && copy->to > copy->from)
		{
			ft_bzero(copy->copied, BUFFSIZE);
			ft_strncpy(copy->copied, tc->command + copy->from,
														copy->to - copy->from);
		}
		copy->state = 0;
	}
	else
	{
		copy->from = i;
		copy->state = 1;
		copy->type = 0;
	}
	return (1);
}

static inline void	ft_exec_cut(t_cap *tc, t_cc *copy)
{
	int a;

	a = -1;
	ft_bzero(copy->copied, BUFFSIZE);
	ft_strncpy(copy->copied, tc->command + copy->from,
												copy->to - copy->from);
	while (++a < (int)ft_strlen(copy->copied))
		ft_delete_back(tc);
}

int					ft_cut(t_cap *tc)
{
	int		i;
	t_cc	*copy;

	i = tc->cursy * (tc->cursx_max + 1) + (tc->cursx) - tc->prompt_len;
	copy = g_shell->copy_cut;
	if (copy->type != 1 && ~copy->type)
		return (1);
	else if (copy->state)
	{
		copy->to = i;
		copy->type = -1;
		if (copy->to > copy->from)
			ft_exec_cut(tc, copy);
		copy->state = 0;
	}
	else
	{
		copy->from = i;
		copy->state = 1;
		copy->type = 1;
	}
	return (1);
}

int					ft_paste(t_cap *tc)
{
	return (ft_insert(g_shell->copy_cut->copied, tc));
}
