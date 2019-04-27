/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 13:48:17 by aben-azz          #+#    #+#             */
/*   Updated: 2018/11/14 10:54:53 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	size;
	int		i;
	char	*concatened;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(concatened = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		concatened[i] = s1[i];
		i++;
	}
	concatened[i] = '\0';
	ft_strcat(concatened, s2);
	return (concatened);
}
