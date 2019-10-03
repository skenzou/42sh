/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtin_editor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:37:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/03 20:36:45 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
//
// int		exec_command(char *)

int		fc_editor(int argc, char **argv, int param)
{
	(void)argc;
	(void)argv;
	char *command[] = {"atom", "--wait", "~/.42sh_history", NULL};
	ft_fork_amper(command, g_shell->env_tmp);
	//execve(command[0], command, g_shell->env_tmp);
	// int pid;
	//
	// pid = fork();
	//
	// if (!pid)
	// {
	// 	execvp(command[0], command);
	// }
	// else
	// {
	// 	wait(&pid);
	// 	ft_printf("c fini\n");
	// }
	ft_printf("editor actif reverse :%d\n", (param & FC_REVERSE) > 0);
	return (0);
}
