/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 05:04:02 by tlechien          #+#    #+#             */
/*   Updated: 2019/06/04 22:42:00 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Builtin that gives back focus to background processus.
**  Needs protection on already finished process ??
*/

int	fg_builtin(int ac, char **cmd)
{
	t_child	*node;
	int		i;
	int		ret;

	(void)ac;
	ret = 0;
	node = NULL;
	if ((i = 1) && !cmd[i])
	{
		search_priority(&node);
		if (node && node->status != S_TERM)
			return (ft_waitprocess(node->pid, cmd));
		err_display("fg: no current job\n", NULL, NULL);
		return (1);
	}
	while (cmd[i] && *cmd[i] == '%')
	{
		if ((*cmd[i] == '%' && !(!search_pid(&node, cmd[i] + 1, 0) ||
		!search_process(&node, cmd[i] + 1) || !search_index(&node, cmd[i] + 1))))
			return (err_display("fg : job not found: ", cmd[i] + 1, "\n"));
		else if (*cmd[i] != '%' && search_process(&node, cmd[i]))
			return (err_display("fg : job not found: ", cmd[i], "\n"));;
		if ((ret = ft_waitprocess(node->pid, cmd)))
			return (ret);
		i++;
	}
	return (0);
}
