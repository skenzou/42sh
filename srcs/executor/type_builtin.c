/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 15:14:34 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/07 06:26:18 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#define IS_BUILTIN 1
#define IS_BIN 2
#define IS_ALIAS 3

static void		type_output(char *input, char *value, char type)
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

static int		find_name(char *str)
{
	char	*copy;
	int		ret;

	ret = 0;
	copy = NULL;
	if (is_alias(str) >= 0)
	{
		copy = get_alias(str);
		type_output(str, copy, IS_ALIAS);
	}
	else if (get_builtin(str))
		type_output(str, NULL, IS_BUILTIN);
	else
	{
		copy = ft_strdup(str);
		if (hash_table(&copy, g_shell->env_tmp) == 0)
			type_output(str, copy, IS_BIN);
		else
		{
			type_output(str, NULL, NOT_FOUND);
			ret = 1;
		}
	}
	ft_strdel(&copy);
	return (ret);
}

int				type_builtin(int ac, char **args)
{
	int		i;
	int		ret;

	i = 0;
	ret = ac < 2;
	while (++i < ac)
		ret = (find_name(args[i]) || ret == 1);
	return (ret);
}
