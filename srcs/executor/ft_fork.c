/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:53:49 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/17 10:41:31 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/shell.h"

int		ft_waitprocess(pid_t pid, char **cmd)
{
	int       status;
  t_child   *node;

	waitpid(pid, &status, WUNTRACED);
  if (WIFEXITED(status))
		return (0);
  else if (WIFSIGNALED(status))
		kill(pid, SIGTERM); // proteccc ? err = -1
  else if (WSTOPSIG(status))
  {
    update_pid_table(pid, cmd, S_SUSP);
    search_pid(&node, NULL, pid);
    display_pid_status(node->index, ' ', S_SUSP, &(node->exec));
		kill(pid, SIGINT); // idem ?
  }
	return (1);
}

int		ft_fork_amper(char **cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, sighandler);
	if (!pid)
		execve(cmd[0], cmd, env);
	if (pid < 0)
		return (FAILFORK); // fork
  if (!waitpid(pid, &pid, WNOHANG))
    return(update_pid_table(pid, cmd, S_RUN));
	return (0);
}

int		ft_fork(char **cmd, char **env)
{
	pid_t pid;

	if (!ft_strcmp(cmd[ft_split_count(cmd) - 1], "&"))
		return(ft_fork_amper(cmd, env));
	pid = fork();
	//signal(SIGINT, sighandler);
	if (pid == 0)
	{
		execve(cmd[0], cmd, env);
		exit(1);
	}
	else if (pid < 0)
		return (FAILFORK);
	return (ft_waitprocess(pid, cmd));
}
