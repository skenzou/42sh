/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 02:02:47 by aben-azz          #+#    #+#             */
/*   Updated: 2019/10/02 17:38:59 by aben-azz         ###   ########.fr       */
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
		return (handle_error(fc_list(argc, argv, param)));
	else if (param & FC_NO_EDITOR)
		return (handle_error(fc_no_editor(argc, argv)));
	return (0);
}
