/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 02:02:47 by aben-azz          #+#    #+#             */
/*   Updated: 2019/11/10 18:38:12 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				handle_error(int code)
{
	if (code < 0)
		ft_putstr_fd("42sh: fc: ", 2);
	if (code == FC_MALLOC_ERR)
		ft_putstr_fd("Malloc error.\n", 2);
	else if (code == FC_CANT_OPEN)
		ft_putstr_fd("Cannot open file.\n", 2);
	else if (code == FC_NO_PATH)
		ft_putstr_fd("PATH env variable not set.\n", 2);
	else if (code == FC_NOT_FOUND)
		ft_putstr_fd("Event not found in history.\n", 2);
	else if (code == FC_BIN_NFOUND)
		ft_putstr_fd("Binary not found.\n", 2);
	else if (code == FC_NO_EVENT)
		ft_putstr_fd("No such event.\n", 2);
	else if (code == FC_TOO_MANY_ARGS)
		ft_putstr_fd("Too many arguments.\n", 2);
	else if (code == FC_ERR_PARAM)
		ft_putstr_fd("Parameters are not allowed after -e.\n", 2);
	else if (code == FC_NO_ARG_E)
		ft_putstr_fd("Editor not found.\n", 2);
	else if (code == FC_NO_HISTORY)
		ft_putstr_fd("Command not found in history.\n", 2);
	else
		ft_putstr_fd("Error.\n", 2);
	return (code);
}

static int		fc_no_param(int argc, char **av, int param)
{
	int		i;
	char	*fcedit;
	char	*av_custom[6];
	int		j;

	j = 1;
	i = 3;
	if (!(fcedit = get_all_key_value("FCEDIT", g_shell->env_tmp)))
		if (!(fcedit = ft_strdup("vim")))
			return (handle_error(FC_MALLOC_ERR));
	av_custom[0] = NULL;
	av_custom[1] = "-e";
	av_custom[2] = fcedit;
	if (argc == 1)
		av_custom[i++] = NULL;
	while (argc > 1 && j < argc && i < 5)
	{
		if (av[j] && av[j][0] != '-')
			if (!(av_custom[i++] = av[j]))
				return (handle_error(FC_MALLOC_ERR));
		j++;
	}
	av_custom[i] = NULL;
	return (fc_editor(i, av_custom, param));
}

int				fc_builtin(int argc, char **argv)
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
