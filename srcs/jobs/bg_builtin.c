/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 10:57:28 by tlechien          #+#    #+#             */
/*   Updated: 2019/09/22 00:56:32 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

/*
** Checks if the pipe is stopped.
*/

int		is_branch_stp(t_child *head)
{
	t_child *tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->status != ID_SUSP &&
		tmp->status != SIGSTOP && tmp->status != SIGTTIN &&
		tmp->status != SIGTTOU)
			return (1);
		tmp = tmp->right;
	}

	return (0);
}

/*
**	Resumes given process.
*/

int			bg_resume(t_child *node)
{
	t_child *branch;
	if (!node || (node->status != ID_SUSP &&
	node->status != SIGSTOP && node->status != SIGTTIN &&
	node->status != SIGTTOU))
		return (1);
	else if (node->is_pipe && is_branch_stp(node))
		return (1);
	branch = node;
	while (branch)
	{
		kill(branch->pid, SIGCONT);
		branch->priority = 0;
		branch->status = SIGCONT;
		if (!branch->right)
			break;
		branch = branch->right;
	}
	if (node->is_pipe)
		display_amperpipe(node, 1);
	else
		display_pid_status(node, 1);
	return (0);
}

/*
**	Resumes all processes.
*/

static	int	bg_all(t_child *node)
{
	int		job_done;

	job_done = 0;
	while (node->prev)
		node = node->prev;
	while (node)
	{
		if (node->pid && (node->status == ID_SUSP || node->status == SIGSTOP
		|| node->status == SIGTTIN || node->status == SIGTTOU))
			(!bg_resume(node)) ? job_done++: 0;
		node = node->left;
	}
	return ((job_done) ? 0 : err_display("bg: no current job\n", NULL, NULL));
}

/*
** Builtin that resumes interruped processes.
*/

int			bg_builtin(int ac, char **cmd)
{
	t_child	*node;
	int		i;
	int		ret;

	(void)ac;
	ret = 0;
	node = NULL;
	if ((i = 1) && !cmd[i])
		return (bg_all(g_pid_table));
	while (cmd[i] && *cmd[i])
	{
		if ((*cmd[i] == '%' && !(!search_pid(&node, cmd[i] + 1, 0) ||
	!search_process(&node, cmd[i] + 1) || !search_index(&node, cmd[i] + 1))))
			return (err_display("bg : job not found: ", cmd[i] + 1, "\n"));
		else if (*cmd[i] != '%' && search_process(&node, cmd[i]))
			return (err_display("bg : job not found: ", cmd[i], "\n"));
		if ((ret = bg_resume(node)))
			break ;
		i++;
	}
	if (!node && (ret = 1))
		err_display("bg: ", cmd[i], ": no such job\n");
	else if (ret)
		err_display("bg: job already in background\n", NULL, NULL);
	return (ret);
}
