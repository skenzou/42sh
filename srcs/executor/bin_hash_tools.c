/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_hash_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghamelek <ghamelek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 01:42:31 by ghamelek          #+#    #+#             */
/*   Updated: 2019/06/23 15:51:40 by Mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char				*free_duo(char **s1, t_hash_entry **s2)
{
	ft_splitdel(s1);
	ft_strdel((char**)&(*s2)->key);
	free(*s2);
	*s2 = NULL;
	return (NULL);
}

char				*my_env(char **env)
{
	int i;

	i = -1;
	while (env[++i])
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return ((char*)env[i] + 5);
	return (NULL);
}

unsigned char		*add_path(char **bin, unsigned char *argv)
{
	int				i;
	char			*old_bin;
	unsigned char	*str;

	i = -1;
	while (bin && bin[++i])
	{
		old_bin = *(bin + i);
		if (!(bin[i] = ft_strjoin(bin[i], "/")))
			shell_exit(MALLOC_ERR);
		ft_strdel(&old_bin);
		if (!(str = (unsigned char *)ft_strjoin(bin[i], (char *)argv)))
			shell_exit(MALLOC_ERR);
		if (access((char *)str, R_OK) == 0)
			return (str);
		ft_strdel((char **)&str);
	}
	return (NULL);
}
