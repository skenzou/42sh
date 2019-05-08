/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:31:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/08 02:43:46 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int			read_buffer(char buffer[4], t_cap *tcap)
{
	char key;

	if (ft_isprint(buffer[0]) || wcharlen(buffer[0]) > 1)
	{
		ft_printf("%s", buffer);
	}
	if (is_arrow(buffer))
		return (read_arrow(buffer[2], tcap));
	else if ((key = is_shift_arrow(buffer)) != -1)
		return (read_arrow(key + 10, tcap));
	else if ((key = is_key(buffer)) != -1)
		return (read_key(key, tcap));
	else if (DEBUG_LOG)
		ft_printf("%c|%hhd", buffer[0], buffer[0]);
	return (1);
}
