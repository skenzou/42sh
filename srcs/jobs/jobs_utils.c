/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 04:40:55 by tlechien          #+#    #+#             */
/*   Updated: 2019/06/29 15:02:12 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Kills all the pids left.
*/

int		kill_pids(void)
{
	t_child *branch;
	t_child *tmp;

	while (ID_PID != 0)
	{
		branch = ID_RIGHT;
		while (branch)
		{
			tmp = branch;
			branch = branch->right;
			kill(tmp->pid, SIGTERM);
			tmp->status = SIGTERM;
		}
		if (!kill(ID_PID, SIGTERM))
			ID_STATUS = SIGTERM;
		else if (ID_STATUS != SIGTERM && !ID_PIPE)
		{
			err_display(ANSI_RED"42sh: can't kill process: ", ID_EXEC,
			": pid >");
			ft_putnbr_fd(ID_PID, 2);
			ft_putendl_fd(ANSI_RESET, 2);
			remove_pid(g_pid_table);
		}
	}
	return (0);
}

/*
** Updates statuses in pid_table.
** tmp_f && tmp_s are initalised at NULL.
*/

int		update_priority(int first, t_child *tmp_f, t_child *tmp_s)
{
	t_child *save;

	save = g_pid_table;
	while (ID_PREV && ID_INDEX)
	{
		if (first)
		{
			(ID_PRIORITY == 1) ? ID_PRIORITY = 0 : 0;
			(ID_PRIORITY == 2) ? ID_PRIORITY = 1 : 0;
			(ID_INDEX == first) ? ID_PRIORITY = 2 : 0;
		}
		if (!first && (!tmp_s || tmp_f == tmp_s) && (ID_PRIORITY == 1 ||
			!ID_PRIORITY))
			tmp_s = g_pid_table;
		if (!first && (!tmp_f || tmp_f->priority < ID_PRIORITY))
		{
			(tmp_f && tmp_f->priority != -1) ? tmp_s = tmp_f : 0;
			tmp_f = g_pid_table;
		}
		g_pid_table = ID_PREV;
	}
	g_pid_table = save;
	(tmp_s && tmp_s->priority != -1) ? tmp_s->priority = 1 : 0;
	(tmp_f && tmp_f->priority != -1) ? tmp_f->priority = 2 : 0;
	return (0);
}

/*
** Removes a node from the pid_table and point on the next one if possible,
** on the previous if not.
*/

int		remove_pid(t_child *node)
{
	t_child *curr;

	curr = (node->left) ? node->left : node->prev;
	(node->prev) ? (node->prev)->left = node->left : 0;
	(node->left) ? (node->left)->prev = node->prev : 0;
	if (node->exec)
		ft_strdel(&node->exec);
	if (g_pid_table == node)
		g_pid_table = curr;
	free(node);
	return (0);
}

/*
** Makes a single cmd line out of the lexer split.
*/

char	*full_cmd(char **cmd)
{
	int		i;
	int		len;
	char	*ret;

	i = -1;
	len = 0;
	while (cmd[++i])
		len += ft_strlen2(cmd[i]) + 1;
	ret = (char*)ft_memalloc(len);
	i = 0;
	ret = ft_strcat(ret, cmd[i]);
	while (cmd[++i])
	{
		ret = ft_strcat(ret, " ");
		ret = ft_strcat(ret, cmd[i]);
	}
	return (ret);
}
