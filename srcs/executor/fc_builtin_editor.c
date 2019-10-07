/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtin_editor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:37:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/07 17:12:31 by aben-azz         ###   ########.fr       */
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
	int i = 1;
	while (i < argc && argv[i][0] == '-' && !~ft_indexof(argv[i], 'e'))
		i++;
	while (i < argc && argv[i + 1] && argv[i + 1][0] == '-' && argv[i + 1][1] == 'e')
		i++;
	ft_printf("%d/%d\n", i, argc);
	if (argc - 1 > i && argv[i + 1][0] == '-')
	{
			ft_printf("erreur param apres -e\n");
			return 1;

	}
	if (i == argc - 1)
		ft_printf("0 argv\n");
	else
	{
		i++;
		ft_printf("ac: %d i: %d, arg: |%s| fcedit: %s\n", argc, i, argv[i], fcedit);
		if (argc - 1 > i)
			ft_printf("ya d args supp : {%s, %s}\n", argv[i + 1], argc - 1 - i == 2 ? argv[i + 2] : NULL);
		else
			ft_printf("ya pa darg supp\n");
	}
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
