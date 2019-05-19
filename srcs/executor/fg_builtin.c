/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 05:04:02 by tlechien          #+#    #+#             */
/*   Updated: 2019/05/19 13:08:21 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Builtin that gives back focus to background processus.
**  Need protection on already finished process ??
*/

int	fg_builtin(char **cmd)
{
	t_child	**node;
	int		i;
	int		ret;

	ret = 0;
	node = NULL;
	if ((i = 1) && cmd[0] && !cmd[1])
	{
		search_priority(node);
		if (node)
			return (ft_waitprocess((*node)->pid, cmd));
		ft_putendl("fg: no current job\n");
		return (1);
	}
	while (cmd[i] && *cmd[i] == '%')
	{
		if (search_pid(node, ++cmd[i], 0) && search_process(node, cmd[i])
			&& search_index(node, cmd[i]))
			break ;
		if ((ret = ft_waitprocess((*node)->pid, cmd)))
			return (ret);
		i++;
	}
	return ((node) ? (ft_printf("fg: %s: no such job\n", cmd[i]) || 1) : 0);
}
