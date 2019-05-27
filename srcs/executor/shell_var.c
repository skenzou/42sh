/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:17:30 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/27 20:34:01 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	check_intern_var(char *needle)
{
	int i;
	char *key;

	i = 0;
	while(needle[i] && needle[i] != '=')
		i++;
	if (!(key = ft_strsub(needle, 0, i)))
		ft_exit("Malloc in check_intern_var failed");
	if (get_indexof_key(key, g_shell->env) >= 0)
		ft_setenv(key, needle + i + 1, &g_shell->env);
	else
		ft_setenv(key, needle + i + 1, &g_shell->intern);
	ft_strdel(&key);
}

int		is_var(char *needle)
{
	if (!ft_isalpha(*(needle++)))
		return (0);
	while (*needle && *needle != '=')
	{
		if (!ft_isalnum(*needle))
			return (0);
		needle++;
	}
	return (*needle);
}

void		handle_intern_var(char **args)
{
	int i;

	i = 0;
	while (args[i] && is_var(args[i]))
		check_intern_var(args[i++]);
	if (i > 0)
		remove_n_first_entries(args, i);
}
