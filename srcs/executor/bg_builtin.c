/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 10:57:28 by tlechien          #+#    #+#             */
/*   Updated: 2019/05/19 13:39:06 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Builtin that resume interruped processus.
**  Need protection on already finished process ??
*/

static	int	bg_all(void)
{
	t_child	**node;

	node = NULL;
	search_status(node, S_SUSP);
	if (node)
		return (bg_resume(node));
	ft_putendl("bg: no current job\n");
	return (1);
}

int			bg_builtin(char **cmd)
{
	t_child	**node;
	int		i;
	int		ret;

	ret = 0;
	node = NULL;
	if ((i = 1) && cmd[0] && !cmd[1])
		return (bg_all());
	while (cmd[i] && *cmd[i] == '%')
	{
		if (search_pid(node, ++cmd[i], 0) && search_process(node, cmd[i])
			&& search_index(node, cmd[i]))
			break ;
		if ((ret = bg_resume(node)))
			break ;
		i++;
	}
	if (!node && (ret = 1))
		ft_printf("bg: %s: no such job\n", cmd[i]);
	else if (ret)
		ft_printf("bg: job already in background");
	return (ret);
}

int			bg_resume(t_child **node)
{
	if (!node || (*node)->status != S_SUSP || kill((*node)->pid, SIGCONT))
		return (1);
	(*node)->priority = 0;
	(*node)->status = S_RUN;
	return (0);
}
