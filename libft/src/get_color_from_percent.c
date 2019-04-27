/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_from_percent.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:21:50 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/13 14:24:34 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int				ft_get_color_from_percent(int color1, double percentage)
{
	int		red;
	int		green;
	int		blue;

	red = get_light((color1 >> 16) & 0xFF,
			(0x000000 >> 16) & 0xFF, percentage);
	green = get_light((color1 >> 8) & 0xFF,
			(0x000000 >> 8) & 0xFF, percentage);
	blue = get_light(color1 & 0xFF, 0x000000 & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}
