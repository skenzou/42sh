/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 01:46:22 by tlechien          #+#    #+#             */
/*   Updated: 2019/09/18 05:24:25 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_child *get_head(t_child *node)
{
	t_child *head;

	head = node;
	while (head->is_pipe < 3)
		head = head->prev;
	return (head);
}

static int	check_branch(t_child *branch, int *finished)
{
	int		out;
	int		action;

	while (branch)
	{
		if (s_get_values(branch->status, &action, NULL, NULL) ||
		action == S_STOP || action == S_CONT)
			*finished = 0;
		if (!branch->right)
			break ;
		branch = branch->right;
	}
	(*finished && ID_PIPE) ? display_amperpipe(g_pid_table, 1) : 0;
	while (*finished && ID_PIPE && branch != g_pid_table && (out = 1))
	{
		(branch->exec) ? ft_strdel(&branch->exec): 0;
		branch = branch->prev;
		free(branch->right);
		branch->right = NULL;
	}
	return (0);
}

int			check_remove_pids(void)
{
	int		finished;
	int		action;

	while (ID_PID != 0 && (finished = 1))
	{
		check_branch(g_pid_table, &finished);
		if (finished && !s_get_values(ID_STATUS, &action, NULL, NULL) &&
			(action == S_TERM || action == S_ABN))
			remove_pid(g_pid_table);
		if (!ID_PREV)
			break ;
		else
			g_pid_table = ID_PREV;
	}
	while (ID_LEFT)
		g_pid_table = ID_LEFT;
	return (0);
}

int			update_amperpipe(t_child *pipe)
{
	int		status;
	int		action;

	while (pipe)
	{
		(s_get_values(pipe->status, &action, NULL, NULL)) ? action = S_CONT : 0;
		if (action == S_ABN || action == S_TERM ||
			!waitpid(pipe->pid, &status, WNOHANG | WUNTRACED | WCONTINUED))
			;
		else if (WIFCONTINUED(status))
			pipe->status = ID_RUN;
		else if (WIFEXITED(status))
		{
			if (action != S_ABN && action != S_TERM)
				pipe->status = ID_DONE;
		}
		else if (WIFSIGNALED(status))
			s_child_handler(WTERMSIG(status), pipe);
		else if (WIFSTOPPED(status))
			s_child_handler(WSTOPSIG(status), pipe);
		if (!pipe->right)
			break ;
		pipe = pipe->right;
	}
	return (0);
}

int			display_amperpipe(t_child *node, char option)
{
	char	*stat;
	char	current;

	(void)option;
	while (node)
	{
		(s_get_values(node->status, NULL, NULL, &stat)) ? stat = "running" : 0;
		(node->status == SIGHUP) ? stat = "done" : 0;
		current = (node->priority < 1) ? ' ' : '-';
		(node->priority == 2) ? current = '+' : 0;
		if (node->is_pipe > 2 && option & OPT_L)
			ft_printf("[%d] %c %d %-28s %s | \n", node->index, current,
			node->pid, stat, node->exec);
		else if (node->is_pipe < 2 && option & OPT_L)
			ft_printf("%*c %d %-28s %s%s\n", get_nb_len(node->index) + 4, ' ',
			node->pid, stat, node->exec, (node->right) ? " | " : "");
		else if (node->is_pipe > 2 && option & OPT_P)
			ft_printf("%d\n", node->pid);
		else if (node->is_pipe > 2 && !option)
			ft_printf("[%d] %c %-28s %s | \n", node->index, current,
			stat, node->exec);
		else if (node->is_pipe < 2 && !option)
			ft_printf("%*c %-28s %s%s\n", get_nb_len(node->index) + 4, ' ',
			stat, node->exec, (node->right) ? " | " : "");
		node = node->right;
	}
	return (0);
}
