/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 13:48:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/01/26 19:20:49 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	char *ptr;

	ptr = NULL;
	while (*s)
	{
		*s == (char)c && (ptr = (char*)s);
		s++;
	}
	*s == (char)c && (ptr = (char*)s);
	return (ptr);
}
