/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 15:24:52 by aben-azz          #+#    #+#             */
/*   Updated: 2019/01/26 19:19:21 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char *str)
{
	int					signe;
	unsigned long long	result;

	result = 0;
	signe = 1;
	while (*str == '\n' || *str == '\t' || *str == '\r' || *str == '\v'
		|| *str == '\f' || *str == ' ')
		(void)*str++;
	(*str == '-' || *str == '+') && (signe = *str++ == '-' ? -signe : signe);
	while (*str && ft_isdigit(*str))
	{
		if (result > 9223372036854775807)
			return (signe == -1 ? 0 : -1);
		result *= 10;
		result += *str++ - '0';
	}
	return ((int)(result * signe));
}
