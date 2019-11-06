/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_no_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:44:06 by tlechien          #+#    #+#             */
/*   Updated: 2019/11/06 18:11:54 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** fc_editor(int argc, char **argv, int param)
** fc -e fcedit oui oui
*/

int		fc_no_param(int argc, char **av, int param)
{
	int i;
	char *fcedit;
	char **av_custom;

	if (!(fcedit = get_all_key_value("FCEDIT", g_shell->env_tmp)))
		if (!(fcedit = ft_strdup("vim")))
			return (shell_exit(MALLOC_ERR));
	if (!(av_custom = malloc(sizeof(char *) * 6)))
		return (shell_exit(MALLOC_ERR));
	av_custom[0] = NULL;
	av_custom[1] = ft_strdup("-e");
	av_custom[2] = fcedit;
	av_custom[3] = argc > 2 && av[argc - 2] ? ft_strdup(av[argc - 2]) : NULL;
	av_custom[4] = argc > 3 && av[argc - 1] ? ft_strdup(av[argc - 1]) : NULL;
	av_custom[5] = NULL;
	dprintf(debug(), "fc no param {%s, %s, %s, %s, %s, %s}\n",)

	return 1;
}
