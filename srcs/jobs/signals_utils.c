/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 13:41:37 by tlechien          #+#    #+#             */
/*   Updated: 2019/06/26 07:13:18 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	get_nb_len(long long nb)
{
	int i;

	i = 1;
	while ((nb /= 10) > 1)
		i++;
	return (1);
}

int	waitabit(int min, int nsec)
{
	struct timespec	slp;

	slp.tv_sec = min;
	slp.tv_nsec = nsec;
	nanosleep(&slp, NULL);
	return (0);
}
