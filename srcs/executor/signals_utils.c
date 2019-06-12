/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlechien <tlechien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 13:41:37 by tlechien          #+#    #+#             */
/*   Updated: 2019/06/12 13:44:22 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int waitabit(int time)
{
	struct timespec	slp;

	slp.tv_sec = 0;
	slp.tv_nsec = time;
	nanosleep(&slp, NULL);
	return (0);
}
