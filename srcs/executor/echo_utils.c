/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 19:23:18 by tlechien          #+#    #+#             */
/*   Updated: 2019/11/06 19:34:22 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

long		ft_pow(int base, int pow)
{
	long long result;

	result = 1;
	while (pow-- > 0)
	{
		result *= base;
		if (result > LONG_MAX)
			return (0);
	}
	return (result);
}

int			b_conv(char *str, int len, int base)
{
	int value;
	int	i;

	value = 0;
	i = 0;
	while (len--)
	{
		if (i == 0 && str[i] > 51)
			str[i] = str[i] - 4;
		value = value + ((str[i] - '0') * ft_pow(base, len));
		i++;
	}
	return (value);
}
