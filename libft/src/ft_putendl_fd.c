/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 15:02:14 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/01 20:08:57 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putendl_fd(char *s, int fd)
{
	if (!s || !fd)
		return (0);
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
	return (ft_strlen(s) + 1);
}
