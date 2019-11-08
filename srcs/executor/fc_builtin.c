/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 02:02:47 by aben-azz          #+#    #+#             */
/*   Updated: 2019/11/08 11:58:32 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		debug_param(int param)
{
	if (!param)
	{
		ft_printf("Aucune option\n");
		return (0);
	}
	ft_printf("-");
	if (param & FC_EDITOR)
		ft_printf("E");
	if (param & FC_REVERSE)
		ft_printf("R");
	if (param & FC_LIST)
		ft_printf("L");
	if (param & FC_NO_NUMBER)
		ft_printf("N");
	if (param & FC_NO_EDITOR)
		ft_printf("S");
	ft_printf("\n");
	return (1);
}

int		handle_error(int code)
{
	(void)code;
	return (code);
}

int		fc_no_param(int argc, char **av, int param)
{
	int		i;
	char	*fcedit;
	char	*av_custom[6];
	int		j;

	j = 1;
	i = 3;
	if (!(fcedit = get_all_key_value("FCEDIT", g_shell->env_tmp)))
		if (!(fcedit = ft_strdup("vim")))
			return (shell_exit(MALLOC_ERR));

	av_custom[0] = NULL;
	av_custom[1] = "-e";
	av_custom[2] = fcedit;
	if (argc == 1)
		av_custom[i++] = "noarg";
	while (argc > 1 && j < argc && i < 5)
	{
		if (av[j] && av[j][0] != '-')
			if (!(av_custom[i++] = av[j]))
				return (shell_exit(MALLOC_ERR));
		j++;
	}
	av_custom[i] = NULL;
	return (fc_editor(i, av_custom, param));
}

int		fc_builtin(int argc, char **argv)
{
	int param;

	if (!~(param = get_param(argc, argv)) || !~check_compatibility(param))
	{
		ft_printf("%s\n%s\n%s\n%s\n",
			"Error: invalid options.",
			"Usage: fc [-r] [-e editor] [first [last]]",
			"fc -l [-nr] [first [last]]",
			"fc -s [old=new] [first]");
		return (1);
	}
	debug_param(param);
	if (param & FC_LIST)
		return (fc_list(argc, argv, param));
	else if (param & FC_NO_EDITOR)
		return (fc_no_editor(argc, argv));
	else if (param & FC_EDITOR)
		return (fc_editor(argc, argv, param));
	else
		return (fc_no_param(argc, argv, param));
	return (0);
}
