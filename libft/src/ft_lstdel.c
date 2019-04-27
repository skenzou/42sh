/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 20:01:39 by aben-azz          #+#    #+#             */
/*   Updated: 2018/10/15 20:38:59 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del) (void *, size_t))
{
	t_list *list;

	list = *alst;
	while (list)
	{
		*alst = list->next;
		del(list->content, list->content_size);
		free(list);
		list = *alst;
	}
	*alst = NULL;
}
