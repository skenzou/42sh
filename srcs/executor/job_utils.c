/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 04:40:55 by tlechien          #+#    #+#             */
/*   Updated: 2019/06/17 21:56:18 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int	init_pid(void)
{
	if (!(g_pid_table = (t_child*)ft_memalloc(sizeof(t_child))))
		return (1);
		//free leaks
	return (0);
}

int	kill_pids(void)
{
	while (ID_PID != 0)
	{
		//ft_printf("bg PID :%d is being killed.\n", ID_PID);
		if (!kill(ID_PID, SIGHUP))
			ID_STATUS = SIGHUP;
		else if (!kill(ID_PID, SIGTERM))
			ID_STATUS = SIGTERM;
		else
		{
			err_display(ANSI_RED"42sh: can't kill process: ", ID_EXEC,
			": pid >");
			ft_putnbr_fd(ID_PID, 2);
			ft_putendl_fd(ANSI_RESET, 2);
		}
		display_pid_long(g_pid_table, 2);
		remove_pid(g_pid_table);
	}
	return (0);
}

/*
** Updates statuses in pid_table.
*/

int	update_priority(int first)
{
	t_child *tmp_f;
	t_child *tmp_s;
	t_child *save;

	save = g_pid_table;
	tmp_f = NULL;
	tmp_s = NULL;
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
		/*ft_printf("debug  :[%d] %d %d %-10s    \n", ID_INDEX, ID_PID, ID_PRIORITY, ID_EXEC);
		(tmp_f)?ft_printf("debug_f:[%d] %d %d %-10s    \n", tmp_f->index, tmp_f->pid,tmp_f->priority, tmp_f->exec):0;
		(tmp_s)?ft_printf("debug_s:[%d] %d %d %-10s    \n", tmp_s->index, tmp_s->pid,tmp_s->priority, tmp_s->exec):0;*/
		g_pid_table = ID_PREV;

	}
	g_pid_table = save;
	(tmp_s && tmp_s->priority != -1) ? tmp_s->priority = 1 : 0;
	(tmp_f && tmp_f->priority != -1) ? tmp_f->priority = 2 : 0;
	return (0);
}

int	remove_pid(t_child *node)
{
	t_child *curr;

	curr = (node->left)? node->left : node->prev;
	(node->prev) ? (node->prev)->left = node->left : 0;
	(node->left) ? (node->left)->prev = node->prev : 0;
	ft_strdel(&node->exec);
	if (g_pid_table == node)
		g_pid_table = curr;
	free (node);
	return (0);
}

static char	*full_cmd(char **cmd)
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

/*
** Adds a new node to the pid_table.
*/

int	add_pid(int pid, char **command, int status)
{
	t_child *new;
	while (ID_PREV)
		g_pid_table = ID_PREV;
	while (ID_LEFT && ID_LEFT->index == ID_INDEX + 1)
		g_pid_table = ID_LEFT;
	if (!(new = (t_child*)malloc(sizeof(t_child))))
		exit(FAILFORK); //TODO malloc erroc
	new->index = ID_INDEX + 1;
	new->pid = pid;
	new->status = status;
	new->priority = 0;
	new->exec = full_cmd(command);  //TODO dup_env() + proteccc
	new->left = ID_LEFT;
	new->right = NULL;
	new->prev = g_pid_table;
	(new->left) ? new->left->prev = new : 0;
	ID_LEFT = new;
	while (ID_LEFT)
		g_pid_table = ID_LEFT;
	setpgid(pid, 0);
	update_priority(new->index);
	ft_printf("[%d] %d\n", new->index, new->pid);
	return (0);
}

int add_amperpipe(int pid_origin, int pid, char **cmd, int status)
{
	t_child *new;
	t_child	*origin;

	search_pid(&origin, NULL, pid_origin);
	if (!(new = (t_child*)malloc(sizeof(t_child))))
		exit(FAILFORK); //TODO malloc erroc
	new->index = origin->index;
	new->pid = pid;
	new->status = status;
	new->priority = 0;
	new->exec = full_cmd(cmd);  //TODO dup_env() + proteccc
	new->right = NULL;
	new->left = NULL;
	new->prev = origin;
	origin->right = new;
	setpgid(pid, 0);
	ft_printf("%*s %d\n", new->index, "    ", new->pid);
	return(0);
}
