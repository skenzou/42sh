/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 13:48:17 by aben-azz          #+#    #+#             */
/*   Updated: 2018/11/14 10:56:56 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!ft_strlen(needle))
		return (haystack);
	while (*haystack && i < len)
	{
		j = 0;
		while (haystack[j] == needle[j] && (j + i) < len)
		{
			j++;
			if (needle[j] == '\0')
				return (haystack);
		}
		i++;
		haystack++;
	}
	return (NULL);
}
