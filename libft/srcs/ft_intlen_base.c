/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:31:04 by aben-azz          #+#    #+#             */
/*   Updated: 2019/04/09 06:34:20 by Mohamed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_intlen_base(uintmax_t nbr, int base)
{
	int digits;

	digits = !nbr;
	while (nbr)
	{
		digits++;
		nbr /= base;
	}
	return (digits);
}
