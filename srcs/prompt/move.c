/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 00:03:36 by aben-azz          #+#    #+#             */
/*   Updated: 2019/06/22 20:30:52 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_replace_cursor(t_cap *tcap)
{
	int		i;
	int		remainder;

	i = (tcap->char_len + tcap->prompt_len) / (tcap->cursx_max + 1);
	remainder = (tcap->char_len + tcap->prompt_len) % (tcap->cursx_max + 1);
	if (remainder == 0)
		i--;
	ft_move(tcap, "up", i);
	ft_move(tcap, "down", tcap->cursy);
	tputs(tcap->carriage, 1, ft_put_termcaps);
	ft_move(tcap, "!right", tcap->cursx);
}

void	ft_go_to_eol(t_cap *tcap)
{
	ft_move(tcap, "!right", tcap->cursx_max - (tcap->cursx));
	tcap->cursx = tcap->cursx_max;
}

/*
** ft_left
** Verifie si on est pas au debut du prompt, et au y 0, sinon tc envoi un BIP
** Si on est pas sur la premiere ligne et que le curseur est au tout debut de la
** ligne on monte a la ligne superieur et on decremente cursy
** sinon on avance simplement le curseur d'un cran vers la gauche
*/

int		ft_left(t_cap *tcap)
{
	if (tcap->cursy == 0 && tcap->cursx == tcap->prompt_len)
		tputs(tcap->sound, 1, ft_put_termcaps);
	else if (tcap->cursx == 0)
	{
		tputs(tcap->up, 1, ft_put_termcaps);
		tcap->cursy--;
		ft_go_to_eol(tcap);
	}
	else if (tcap->cursx != 0)
	{
		tputs(tcap->left, 1, ft_put_termcaps);
		tcap->cursx--;
	}
	return (1);
}

/*
** ft_right
** Verifie si on est pas a la fin de la chaine, si c'est le cas, tc envoi un BIP
** Si on est pas a la fin de la chaine, mais qu'on est a la fin de la ligne,
** on remet x a 0 et on incremente y, on saute dune ligne apres avoir mi un \r
** sinon on avance simplement le curseur d'un cran vers la droite
*/

int		ft_right(t_cap *tcap)
{
	if (tcap->cursy * (tcap->cursx_max + 1) + tcap->cursx + 1
		== tcap->char_len + tcap->prompt_len + 1)
		tputs(tcap->sound, 1, ft_put_termcaps);
	else if (tcap->cursx == tcap->cursx_max)
	{
		tputs(tcap->down, 1, ft_put_termcaps);
		tputs(tcap->carriage, 1, ft_put_termcaps);
		tcap->cursy++;
		tcap->cursx = 0;
	}
	else
	{
		tputs(tcap->right, 1, ft_put_termcaps);
		tcap->cursx++;
	}
	return (1);
}

int		ft_move(t_cap *tcap, char *string, int n)
{
	while (n--)
	{
		if (!ft_strcmp(string, "right"))
			ft_right(tcap);
		else if (!ft_strcmp(string, "down"))
			tputs(tcap->down, 1, ft_put_termcaps);
		else if (!ft_strcmp(string, "left"))
			ft_left(tcap);
		else if (!ft_strcmp(string, "!left"))
			tputs(tcap->left, 1, ft_put_termcaps);
		else if (!ft_strcmp(string, "!right"))
			tputs(tcap->right, 1, ft_put_termcaps);
		else if (!ft_strcmp(string, "up"))
			tputs(tcap->up, 1, ft_put_termcaps);
	}
	return (1);
}
