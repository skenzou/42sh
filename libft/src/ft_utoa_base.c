/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 23:46:55 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/12 13:36:40 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_utoa_base(uintmax_t nb, int base, int uppercase)
{
	int			len;
	uintmax_t	tmp;
	char		*str;

	len = 1;
	tmp = nb;
	while (tmp >= (uintmax_t)base && ++len)
		tmp /= base;
	if (!(str = ft_strnew(len)))
		return (NULL);
	tmp = uppercase ? 55 : 87;
	while (len--)
	{
		str[len] = (nb % base) +
			(nb % base > 9 ? "aA"[uppercase] - 10 : '0');
		nb /= base;
	}
	return (str);
}
