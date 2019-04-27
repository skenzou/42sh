/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 18:48:05 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/12 13:36:34 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(intmax_t n, int base, int uppercase)
{
	char *str;
	char *temp;

	str = ft_utoa_base(ABS(n), base, uppercase);
	if (n < 0)
	{
		temp = str;
		str = ft_strjoin("-", str);
		ft_strdel(&temp);
	}
	return (str);
}
