/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 00:50:21 by aben-azz          #+#    #+#             */
/*   Updated: 2019/02/12 14:40:26 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

long double	ft_round(long double d, long precision)
{
	long double		diviseur;

	diviseur = 5;
	if (!precision)
		return (d + (d > 0.0 ? 0.5 : -0.5));
	while (precision-- >= 0)
		diviseur /= 10;
	return (d + (d > 0.0 ? diviseur : -diviseur));
}
