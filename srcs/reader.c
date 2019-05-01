/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 15:31:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/01 20:01:25 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int			read_buffer(char buffer[5], t_curs *curseur, char *cmd, int unicode)
{
	char key;

	if (is_arrow(buffer))
		return (read_arrow(buffer[2], curseur));
	else if ((key = is_shift_arrow(buffer)) != -1)
		return (read_arrow(key + 10, curseur));
	else if ((key = is_key(buffer)) != -1)
		return (read_key(key, curseur, cmd));
	else if (ft_isprint(buffer[0]) || unicode)
	{
		cmd[curseur->x++] = buffer[0];
		ft_printf("%s", buffer);
		return (1);
	}
	else if (DEBUG_LOG)
		ft_printf("%c|%hhd", buffer[0], buffer[0]);
	return (1);
}
