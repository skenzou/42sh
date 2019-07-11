/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 23:39:19 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/25 18:31:54 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			print_htable(void)
{
	t_list	*list;
	int		i;

	list = g_shell->hash_indexes;
	if (!list)
	{
		ft_printf("hash: hash table empty\n");
		return ;
	}
	ft_printf("hits    command\n");
	while (list)
	{
		i = *((int *)(list->content));
		ft_printf("%*d    %s\n", 4, g_shell->hash_table[i]->hit,
											g_shell->hash_table[i]->data);
		list = list->next;
	}
}

void				empty_table(void)
{
	t_list	*list;
	int		i;

	list = g_shell->hash_indexes;
	while (list)
	{
		i = *((int *)(list->content));
		ft_strdel((char **)&g_shell->hash_table[i]->data);
		ft_strdel((char **)&g_shell->hash_table[i]->key);
		ft_memdel((void **)&(g_shell->hash_table[i]));
		list = list->next;
	}
	ft_lstdestroy(&g_shell->hash_indexes);
}

static int			check_options(int ac, char **av)
{
	int i;

	if (ac > 1)
	{
		av++;
		if (**av == '-' && *((*av) + 1))
		{
			i = 0;
			while ((*av)[++i])
				if ((*av)[i] != 'r')
				{
					ft_putstr_fd("42sh: hash: -", 2);
					ft_putchar_fd((*av)[i], 2);
					ft_putendl_fd(": invalid option", 2);
					return (1);
				}
			empty_table();
		}
	}
	else
		print_htable();
	return (0);
}

static void			hash_err(char *str)
{
	ft_putstr_fd("42sh: hash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": not found", 2);
}

int					hash_builtin(int ac, char **av)
{
	int				ret;
	int				i;
	t_hash_entry	*item;

	if (check_options(ac, av))
		return (1);
	i = ft_strnequ(av[1], "-r", 2);
	ret = 0;
	while (++i < ac)
	{
		item = hash_search((unsigned char *)av[i]);
		if (item)
			item->hit = 0;
		else
		{
			if (!(item = hash_insert((unsigned char *)av[i], g_shell->env)))
			{
				ret++;
				hash_err(av[i]);
			}
			else
				item->hit = 0;
		}
	}
	return (ret > 0);
}
