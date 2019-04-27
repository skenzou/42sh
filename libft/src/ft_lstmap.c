/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 20:01:25 by aben-azz          #+#    #+#             */
/*   Updated: 2018/10/15 20:39:02 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*temp;
	t_list	*begining;

	if (!(begining = (t_list *)malloc(sizeof(t_list))) || !lst || !f || !*f)
		return (NULL);
	begining = f(lst);
	lst = lst->next;
	temp = begining;
	while (lst)
	{
		temp->next = f(lst);
		temp = temp->next;
		lst = lst->next;
	}
	temp->next = NULL;
	return (begining);
}
