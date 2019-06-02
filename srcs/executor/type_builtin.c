/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:14:34 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/30 19:44:58 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#define	IS_BUILTIN 1
#define	IS_BIN 2
#define	IS_ALIAS 3

void	type_output(char *input, char *value, char type)
{
	if (type == IS_BUILTIN)
		ft_printf("%s is a shell builtin\n", input);
	if (type == IS_ALIAS)
		ft_printf("%s is an alias for %s\n", input, value);
	if (type == IS_BIN)
		ft_printf("%s is %s\n", input, value);
	if (type == NOT_FOUND)
		ft_printf("%s not found\n", input);
}

int		type_builtin(int ac, char **args)
{
	char *copy;
	int i;

	i = 0;
	copy = NULL;
	while (++i < ac)
	{
		if (is_alias(args[i]) >= 0)
		{
			copy = get_alias(args[i]);
			type_output(args[i], copy, IS_ALIAS);
		}
		else if (get_builtin(args[i]) > 0)
			type_output(args[i], NULL, IS_BUILTIN);
		else
		{
			copy = ft_strdup(args[i]);
			if (hash_table(&copy, g_shell->env_tmp) == 0)
				type_output(args[i], copy, IS_BIN);
			else
				type_output(args[i], NULL, NOT_FOUND);
		}
		ft_strdel(&copy);
	}
	return (0);
}
