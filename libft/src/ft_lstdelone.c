/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 20:01:33 by aben-azz          #+#    #+#             */
/*   Updated: 2018/10/15 21:19:49 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del) (void *, size_t))
{
	(alst && *alst) ? del((*alst)->content, (*alst)->content_size) : NULL;
	(alst && *alst) ? ft_memdel((void **)alst) : NULL;
}
