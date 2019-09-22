/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 01:14:21 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/20 19:02:28 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**dup_tab(char **old, size_t size)
{
	char	**new;
	size_t	i;

	size = ft_split_count((const char**)old);
	new = (char **)ft_memalloc(sizeof(char *) * (size + 1));
	!new ? ft_exit("Failed to allocate a new char** in realloc_new_tab") : 0;
	i = 0;
	while (i < size)
	{
		if (!(new[i] = ft_strdup(old[i])))
			ft_exit("Malloc failed in dup_tab");
		i++;
	}
	new[i] = NULL;
	return (new);
}

void		remove_n_first_entries(char **args, int n)
{
	int		i;
	int		count;
	int		j;

	if (!n)
		return ;
	i = 0;
	j = n;
	count = ft_split_count((const char**)args);
	while (j <= count)
	{
		if (i < n)
			ft_strdel(&args[i]);
		args[i++] = args[j++];
	}
	while (i <= count)
		args[i++] = NULL;
}

char		**join_2tab(char **curr, char **next, size_t curr_size,
															size_t next_size)
{
	char	**new;
	size_t	i;
	size_t	j;

	new = (char **)ft_memalloc(sizeof(char *) * (curr_size + next_size + 1));
	!new ? ft_exit("Failed to allocate a new char** in realloc_new_tab") : 0;
	i = 0;
	while (i < curr_size)
	{
		if (!(new[i] = ft_strdup(curr[i])))
			ft_exit("Malloc failed in join_2tab");
		i++;
	}
	j = 0;
	while (j < next_size)
		if (!(new[i++] = ft_strdup(next[j++])))
			ft_exit("Malloc failed in join_2tab");
	new[i] = NULL;
	return (new);
}

char		**realloc_new_tab(char *needle, char **old, size_t size)
{
	char	**new;
	size_t	i;

	size = ft_split_count((const char**)old);
	new = (char **)ft_memalloc(sizeof(char *) * (size + 2));
	!new ? ft_exit("Failed to allocate a new char** in realloc_new_tab") : 0;
	i = 0;
	while (i < size)
	{
		new[i] = old[i];
		i++;
	}
	new[i] = needle;
	new[i + 1] = NULL;
	free(old);
	return (new);
}
