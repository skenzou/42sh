/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 23:56:22 by aben-azz          #+#    #+#             */
/*   Updated: 2019/05/09 00:23:45 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int		ft_add_n_char(char buff[4], int pos, int len, t_cap *tcap)
{
	char	*tmp;

	if (len > (int)ft_strlen(buff))
		len = ft_strlen(buff);
	if (!(tmp = ft_strdup(tcap->command)))
		return (-1);
	ft_bzero(tcap->command, BUFFSIZE);
	ft_strncpy(tcap->command, tmp, pos);
	ft_strncpy(tcap->command + pos, buff, len);
	ft_strcpy(tcap->command + pos + len, tmp + pos);
	tcap->char_len = tcap->char_len + len;
	ft_strdel(&tmp);
	return (1);
}

/*
** ft_insert
** Verifie si on est pas a la fin de la chaine, si c'est le cas, tc envoi un BIP
** Si on est pas a la fin de la chaine, mais qu'on est a la fin de la ligne,
** on remet x a 0 et on incremente y, on saute dune ligne apres avoir mi un \r
** sinon on avance simplement le curseur d'un cran vers la droite
*/

int		ft_insert(char buff[4], t_cap *tcap)
{
	int		position;
	int		i;
	int		len;

	ft_printf("%s", buff);
	if (tcap->char_len + ft_strlen(buff) >= BUFFSIZE - 2)
		tputs(tcap->sound, 1, ft_put_termcaps);
	else
	{
		i = -1;
		len = ft_strlen(buff);
		position = tcap->cursy * (tcap->cursx_max + 1) +
			tcap->cursx - tcap->prompt_len;
		ft_clear_all_lines(tcap);
		if (ft_add_n_char(buff, position, len, tcap) == -1)
			return (-1);
		ft_putstr(tcap->command);
		ft_replace_cursor(tcap);
		while (++i < len)
			ft_right(tcap);
	}
	return (1);
}

int		ft_delete_n_char(t_cap *tcap, int pos, int len)
{
	char	*tmp;

	if (!(tmp = ft_strdup(tcap->command)))
		return (-1);
	ft_bzero(tcap->command, BUFFSIZE);
	ft_strncpy(tcap->command, tmp, pos);
	ft_strcpy(tcap->command + pos, tmp + pos + len);
	ft_strdel(&tmp);
	tcap->char_len = tcap->char_len - len;
	return (1);
}

int		ft_delete_back(t_cap *tcap)
{
	int		pos;

	if (tcap->cursy == 0 && tcap->cursx == tcap->prompt_len)
	{
		tputs(tcap->sound, 1, ft_put_termcaps);
		return (1);
	}
	pos = tcap->cursy * (tcap->cursx_max + 1) + tcap->cursx - tcap->prompt_len;
	pos--;
	ft_clear_all_lines(tcap);
	if (ft_delete_n_char(tcap, pos, 1) == -1)
		return (-1);
	ft_putstr(tcap->command);
	ft_replace_cursor(tcap);
	ft_left(tcap);
	return (1);
}
