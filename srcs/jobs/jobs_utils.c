/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 04:40:55 by tlechien          #+#    #+#             */
/*   Updated: 2019/10/03 19:58:46 by tlechien         ###   ########.fr       */
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
		dprintf(debug(),"here %d\n", ID_PID);
		while (branch)
		{
			tmp = branch;
			branch = branch->right;
			kill(tmp->pid, SIGTERM);
			tmp->status = SIGTERM;
		}
		kill(ID_PID, SIGTERM);
		if (ID_STATUS != SIGTERM && !ID_PIPE)
		{
			err_display(ANSI_RED"42sh: can't kill process: ", ID_EXEC,
			": pid >");
			ft_putnbr_fd(ID_PID, 2);
			ft_putendl_fd(ANSI_RESET, 2);
		}
		remove_pid(g_pid_table);
	}
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
