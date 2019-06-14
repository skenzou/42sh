/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 06:11:23 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/05 09:08:00 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "shell.h"

static char	*my_env(char **env)
{
	int i;

	i = -1;
	while (env[++i])
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return ((char*)env[i] + 5);
	return (NULL);
}

static unsigned char *add_path(char **bin,unsigned char *argv)
{
	int		i;
	char	*old_bin;
	unsigned char *str;

	i = -1;
	while (bin && bin[++i])
	{
		old_bin = *(bin + i);
		if (!(bin[i] = ft_strjoin(bin[i], "/")))
			ft_exit("Malloc failed in add_path");
		ft_strdel(&old_bin);
		if (!(str = (unsigned char *)ft_strjoin(bin[i], (char *)argv)))
			ft_exit("Malloc failed in add_path");
		if (access((char *)str, R_OK) == 0)
			return str;
	}
	return (NULL);
}


static unsigned long hashCode(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;

	return (hash % TABLE_SIZE & 0xFFFFFFFF);
}

t_hash_entry *hash_search(unsigned char* key) {
	int hashIndex = hashCode(key);

	while(g_shell->hash_table[hashIndex] != NULL)
	{
		if(ft_strcmp((char*)g_shell->hash_table[hashIndex]->key,
															(char*)key) == 0)
			return (g_shell->hash_table[hashIndex]);
		++hashIndex;
		hashIndex %= TABLE_SIZE;
	}
	return (NULL);
}

static void		add_index(int hashindex)
{
	t_list *new;

	if (!(new = ft_lstnew((void *)&hashindex, sizeof(int))))
		ft_exit("Malloc failed");
	ft_lstpushback(&g_shell->hash_indexes, new);
}

t_hash_entry *hash_insert(unsigned char *key, char **env)
{
	char	*path;
	char	**bin;
	t_hash_entry *item;

	if (!(item = (t_hash_entry*)ft_memalloc(sizeof(t_hash_entry))))
		ft_exit("Malloc failed in hash_insert");
	item->key = key;
	if (!(item->key = (unsigned char *)ft_strdup((char *)key)))
		ft_exit("Malloc failed in hash_insert");
	int hashIndex = hashCode(key);
	path = my_env(env);
	if (!path)
		return (NULL);
	if (!(bin = ft_strsplit(path, ':')))
		ft_exit("Malloc failed in hash_insert");
	key = add_path(bin, key);
	if(!key)
		return (NULL) ;
	add_index(hashIndex);
	item->data = key;
	while(g_shell->hash_table[hashIndex] != NULL
								&& g_shell->hash_table[hashIndex]->key != NULL)
	{
		++hashIndex;
		hashIndex %= TABLE_SIZE;
	}
	item->hit = 1;
	g_shell->hash_table[hashIndex] = item;
	ft_splitdel(bin);
	return (item);
}


int		hash_table(char **str, char **env)
{
	t_hash_entry *item;
	char *copy;

	item = NULL;
	copy = *str;
	if(!(item = hash_search((unsigned char *)copy)))
	{
		if((item = hash_insert((unsigned char *)copy,env)))
		{
			item->hit = 1;
			*str = ft_strdup((char*)item->data);
			!(*str) ? ft_exit("Malloc failed in hash_table") : 0;
			free(copy);
			return (check_file(*str));
		}
		else
			return (NOT_FOUND);
	}
	else
	{
		item->hit++;
		*str = ft_strdup((char *)item->data);
		!(*str) ? ft_exit("Malloc failed in hash_table") : 0;
		free(copy);
		return (check_file(*str));
	}
}
