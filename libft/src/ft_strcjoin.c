/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:56:22 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/15 00:23:10 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcjoin(char *s1, char *s2, char c)
{
	size_t	size;
	int		i;
	char	*fresh;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 2;
	fresh = (char *)malloc(sizeof(char) * size);
	if (!fresh)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		fresh[i] = s1[i];
		i++;
	}
	fresh[i] = c;
	fresh[i + 1] = '\0';
	ft_strcat(fresh, s2);
	return (fresh);
}
