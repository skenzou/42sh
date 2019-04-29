/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 19:09:23 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/29 23:37:52 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_prompt(void)
{
	ft_printf(ANSI_BLUE "-> " ANSI_RESET);
	ft_printf(ANSI_CYAN "%s" ANSI_RESET, "42sh");
	ft_printf(ANSI_BLUE "> "ANSI_RESET);
}

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		print_prompt();
		signal(SIGINT, sighandler);
	}
}
