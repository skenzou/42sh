/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 06:02:13 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/25 00:43:52 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		init_autocomp(int *count, t_ab *autocomp, char **string)
{
	int max_offset;

	(void)count;
	max_offset = 23;
	autocomp->row = g_shell->tcap->cursx_max / max(max_offset, 1);
	autocomp->len = ft_split_count(string);
	autocomp->col = autocomp->len / max(autocomp->row, 1);
	autocomp->carry = autocomp->len % max(autocomp->row, 1);
	return (max_offset);
}

int		ft_tab(t_cap *tcap, t_ab *autocomp)
{
	(void)tcap;
	char *string[] = {"oui", "jsp", "gros", "delire", "jpp de ouf",
		"ta kiff", "xdd", "ta kiffer ou quoi negro", "jm la vi", "jm la mort", NULL};
	int max_offset;
	int len;
	int count;

	(void)len;
	max_offset = init_autocomp(&count, autocomp, string);
	ft_putchar('\n');

	return (1);
}
