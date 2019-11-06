/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:22:20 by tlechien          #+#    #+#             */
/*   Updated: 2019/10/28 17:22:22 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_rand(long long n)
{
	char		*string;
	long long	a;

	if (!(string = malloc(0)))
		return (0);
	a = ft_max((unsigned int)(&string) / 200 % n, 0);
	ft_strdel(&string);
	return (a);
}
