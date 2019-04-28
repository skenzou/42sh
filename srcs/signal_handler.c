/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:31:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/04/28 16:28:35 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		signal(SIGINT, sig_handler);
		ft_printf("on quitte\n");
		exit(0);
	}
}
