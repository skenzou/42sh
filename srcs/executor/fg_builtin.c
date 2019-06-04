/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 05:04:02 by tlechien          #+#    #+#             */
/*   Updated: 2019/06/04 22:20:37 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Builtin that gives back focus to background processus.
**  Needs protection on already finished process ??
*/

int	fg_builtin(int ac, char **cmd)
{
	t_child	**node;
	int		i;
	int		ret;

	(void)ac;
	ret = 0;
	node = NULL;
	if ((i = 1) && cmd[0] && !cmd[1])
	{
		search_priority(node);
		if (node)
			return (ft_waitprocess((*node)->pid, cmd));
		err_display("fg: no current job\n", NULL, NULL);
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
	return ((node) ? (err_display("fg: ", cmd[i], ": no such job\n")) : 0);
}
