/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 08:00:33 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/12 13:52:16 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static	char			*full_num(long double save,
							char **decimal, int prec, int signe)
{
	char *str;
	char *integer;

	integer = ft_itoa((long long)save);
	if (signe && integer && integer[0] != '-')
	{
		str = integer;
		integer = ft_strjoin("-", integer);
		ft_strdel(&str);
	}
	if (prec == -2)
	{
		ft_strdel(decimal);
		return (integer);
	}
	str = ft_strjoin(integer, *decimal);
	ft_strdel(&integer);
	ft_strdel(decimal);
	return (str);
}

char					*ft_ftoa(long double d, int precision)
{
	int					i;
	long double			save;
	char				*str;
	int					signe;

	signe = (d < 0 && d > -1);
	d = ft_round(d, precision);
	save = d;
	d -= (long long)d;
	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * (precision + 2))))
		return (NULL);
	str[precision + 1] = '\0';
	str[i++] = '.';
	d = d < 0 ? -d : d;
	precision = !precision ? -1 : precision;
	while (precision-- > 0)
	{
		d *= 10.0;
		str[i++] = (long long)d + 48;
		d -= (long long)d;
	}
	return (full_num(save, &str, precision, signe));
}
