/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 06:11:23 by midrissi          #+#    #+#             */
/*   Updated: 2019/11/09 16:12:51 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static unsigned long		hashcode(const unsigned char *str)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return (hash % TABLE_SIZE & 0xFFFFFFFF);
}

t_hash_entry				*hash_search(unsigned char *key)
{
	int hashindex;

	hashindex = hashcode(key);
	while (g_shell->hash_table[hashindex] != NULL)
	{
		if (ft_strcmp((char*)g_shell->hash_table[hashindex]->key,
					(char*)key) == 0)
			return (g_shell->hash_table[hashindex]);
		++hashindex;
		hashindex %= TABLE_SIZE;
	}
	return (NULL);
}

static void					add_index(int hashindex)
{
	t_list *new;

	if (!(new = ft_lstnew((void *)&hashindex, sizeof(int))))
		shell_exit(MALLOC_ERR);
	ft_lstpushback(&g_shell->hash_indexes, new);
}

t_hash_entry				*hash_insert(unsigned char *key, char **env)
{
	char			*path;
	char			**bin;
	t_hash_entry	*item;
	int				hashindex;

	item = NULL;
	if (!(path = get_all_key_value("PATH", env)))
		return (NULL);
	if (!(item = (t_hash_entry*)ft_memalloc(sizeof(t_hash_entry)))
			|| !(item->key = (unsigned char *)ft_strdup((char *)key)))
		shell_exit(MALLOC_ERR);
	hashindex = hashcode(key);
	if (!(bin = ft_strsplit(path, ':')))
		shell_exit(MALLOC_ERR);
	if (!(key = add_path(bin, key)))
		return ((t_hash_entry*)free_duo(bin, &item));
	add_index(hashindex);
	item->data = key;
	while (g_shell->hash_table[hashindex] != NULL
			&& g_shell->hash_table[hashindex]->key != NULL)
		hashindex = (hashindex + 1) % TABLE_SIZE;
	item->hit = 1;
	g_shell->hash_table[hashindex] = item;
	ft_splitdel(bin);
	return (item);
}

int							hash_table(char **str, char **env)
{
	t_hash_entry	*item;
	char			*copy;

	copy = *str;
	if (!(item = hash_search((unsigned char *)copy)))
	{
		if ((item = hash_insert((unsigned char *)copy, env)))
		{
			item->hit = 1;
			*str = ft_strdup((char*)item->data);
			!(*str) ? shell_exit(MALLOC_ERR): 0;
			ft_strdel(&copy);
			return (check_file(*str));
		}
		else
			return (NOT_FOUND);
	}
	else
	{
		item->hit++;
		*str = ft_strdup((char *)item->data);
		!(*str) ? shell_exit(MALLOC_ERR): 0;
		ft_strdel(&copy);
		return (check_file(*str));
	}
}
