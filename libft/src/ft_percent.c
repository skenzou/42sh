/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:20:52 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/13 14:24:43 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double			ft_percent(int start, int end, int curr)
{
	double placement;
	double distance;

	placement = curr - start;
	distance = end - start;
	return (!distance ? 1.0 : (placement / distance));
}
