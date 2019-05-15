/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 06:02:13 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/15 07:58:23 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		print_files(char *string, int max_offset, int i, t_ab *autocomp)
{
	int offset;
	int len;

	len = 0;
	offset = max((max_offset + 2) - ft_strlen(string), 2);
	if (i == autocomp->pos)
	{
		//ft_insert(string, g_shell->tcap);
		//tputs(g_shell->tcap->restore, 1, ft_put_termcaps);
		//ft_replace_cursor(g_shell->tcap);
		len += ft_printf("\x1b[7m%-s\x1b[0m%-*0s", string, offset, "");
	}
	else
		len += ft_printf("%-s%-*0s", string, offset, "");
	return (len);
}

int		init_autocomp(int *count, t_ab *autocomp, int *i, char **string)
{
	int max_offset;

	max_offset = 23;
	autocomp->row = g_shell->tcap->cursx_max / max(max_offset, 1);
	autocomp->len = ft_split_count(string);
	autocomp->col = autocomp->len / max(autocomp->row, 1);
	autocomp->carry = autocomp->len % max(autocomp->row, 1);
	i[0] = 0;
	i[2] = 0;
	*count = 0;
	return (max_offset);
}

int		ft_tab(t_cap *tcap, t_ab *autocomp)
{
	char *string[] = {"oui", "jsp", "gros", "delire", "jpp de ouf",
		"ta kiff", "xdd", "ta kiffer ou quoi negro", "jm la vi", "jm la mort", NULL};
	int max_offset;
	int len;
	int count;
	int i[3];

	max_offset = init_autocomp(&count, autocomp, i, string);
	ft_putchar('\n');
	while (i[2] < autocomp->col)
	{
		i[1] = 0;
		len = 0;
		while (i[1] < autocomp->row)
		{
			tputs(tcap->save, 1, ft_put_termcaps);
			len += print_files(string[i[0]], max_offset, i[0], autocomp);
			i[1]++;
			i[0]++;
		}
		len > tcap->cursx_max + 1 && (count++);
		ft_putchar('\n');
		i[2]++;
	}
	i[1] = -1;
	if (i[0] != autocomp->len)
		while (++i[1] < autocomp->carry)
			print_files(string[i[0]], max_offset, i[0], autocomp) && i[0]++;
	ft_replace_cursor(tcap);
	ft_dprintf(debug(), "count %d\n", count);
	i[0] = -1 - (count <= 1 ? 0 : count);
	while (i[0]++ < autocomp->col)
		tputs(tcap->up, 1, ft_put_termcaps);
	return (1);
}
