/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 05:04:02 by tlechien          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/05/20 13:06:16 by tlechien         ###   ########.fr       */
=======
/*   Updated: 2019/06/04 22:20:37 by tlechien         ###   ########.fr       */
>>>>>>> tlechien
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Builtin that gives back focus to background processus.
**  Needs protection on already finished process ??
*/

<<<<<<< HEAD
int	fg_builtin(char **cmd)
=======
int	fg_builtin(int ac, char **cmd)
>>>>>>> tlechien
{
	t_child	**node;
	int		i;
	int		ret;

<<<<<<< HEAD
=======
	(void)ac;
>>>>>>> tlechien
	ret = 0;
	node = NULL;
	if ((i = 1) && cmd[0] && !cmd[1])
	{
		search_priority(node);
		if (node)
			return (ft_waitprocess((*node)->pid, cmd));
<<<<<<< HEAD
		ft_putendl("fg: no current job\n");
=======
		err_display("fg: no current job\n", NULL, NULL);
>>>>>>> tlechien
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
<<<<<<< HEAD
	return ((node) ? (ft_printf("fg: %s: no such job\n", cmd[i]) || 1) : 0);
=======
	return ((node) ? (err_display("fg: ", cmd[i], ": no such job\n")) : 0);
>>>>>>> tlechien
}
