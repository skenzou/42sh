/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelcurr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 19:49:17 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/05 20:28:39 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdelcurr(t_list *prev, t_list *curr, t_list **head)
{
	if (!curr || !head)
		return ;
	if (!prev)
	{
		*head = curr->next;
		ft_memdel((void **)&curr->content);
		ft_memdel((void **)&curr);
	}
	else
	{
		prev->next = curr->next;
		ft_memdel((void **)&curr->content);
		ft_memdel((void **)&curr);
	}
}
