/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 19:59:51 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/26 17:56:43 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		print_prompt();
		signal(SIGINT, sighandler);
	}
}

void	sigfork(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		signal(SIGINT, sigfork);
	}
}
