/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtin_editor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:37:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/05 18:13:06 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
//
// int		exec_command(char *)

int		fc_editor(int argc, char **argv, int param)
{
	(void)argc;
	(void)argv;
	char *fcedit;
	//char *string;

	fcedit = get_key_value("FCEDIT", g_shell->env);
	ft_printf("ac: %d editor: %s, fcedit: %s\n", argc, NULL, fcedit);
	//char *command[] = {"atom", "--wait", "~/.42sh_history", NULL};
	// int pid;
	// pid = fork();
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
