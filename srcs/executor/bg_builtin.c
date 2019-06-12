/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 10:57:28 by tlechien          #+#    #+#             */
/*   Updated: 2019/06/11 18:11:35 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Builtin that resumes interruped processus.
**  Needs protection on already finished process ??
*/

static	int	bg_all(void)
{
	t_child	**node;

	node = NULL;
	search_status(node, ID_SUSP);
	if (node )
		return (bg_resume(node));
	err_display("bg: no current job\n", NULL, NULL);
	return (1);
}

int			bg_builtin(int ac, char **cmd)
{
	t_child	*node;
	int		i;
	int		ret;

	(void)ac;
	ret = 0;
	node = NULL;
	if ((i = 1) && !cmd[i])
		return (bg_all());
	while (cmd[i] && *cmd[i] == '%')
	{
		if ((*cmd[i] == '%' && !(!search_pid(&node, cmd[i] + 1, 0) ||
		!search_process(&node, cmd[i] + 1) || !search_index(&node, cmd[i] + 1))))
			return (err_display("bg : job not found: ", cmd[i] + 1, "\n"));
		else if (*cmd[i] != '%' && search_process(&node, cmd[i]))
			return (err_display("bg : job not found: ", cmd[i], "\n"));;
		if ((ret = bg_resume(&node)))
			break ;
		i++;
	}
	if (!node && (ret = 1))
		err_display("bg: ", cmd[i],": no such job\n");
	else if (ret)
		err_display("bg: job already in background", NULL, NULL);
	return (ret);
}

int			bg_resume(t_child **node)
{
	if (!node || (*node)->status != ID_SUSP || kill((*node)->pid, SIGCONT))
		return (1);
	(*node)->priority = 0;
	(*node)->status = ID_RUN;
	return (0);
}
