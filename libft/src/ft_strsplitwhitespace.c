/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitwhitespace.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:06:16 by aben-azz          #+#    #+#             */
/*   Updated: 2019/04/01 10:12:27 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count(char *s)
{
	int		compteur;
	int		present_chaine;

	present_chaine = 0;
	compteur = 0;
	while (*s != '\0')
	{
		present_chaine == 1 && ft_is_space(*s) && (present_chaine = 0);
		present_chaine == 0 && !ft_is_space(*s) && compteur++;
		present_chaine == 0 && !ft_is_space(*s) && (present_chaine = 1);
		s++;
	}
	return (compteur);
}

static int		ft_wlen(char *s)
{
	int		len;

	len = 0;
	while (!ft_is_space(*s) && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char			**ft_strsplitwhitespace(char *s)
{
	char	**t;
	int		nb_word;
	int		index;

	if (!s)
		return (NULL);
	index = 0;
	nb_word = count(s);
	t = (char **)malloc(sizeof(*t) * (count(s) + 1));
	if (t == NULL)
		return (NULL);
	while (nb_word--)
	{
		while (ft_is_space(*s) && *s != '\0')
			s++;
		t[index] = ft_strsub(s, 0, ft_wlen(s));
		if (t[index] == NULL)
			return (NULL);
		s += ft_wlen(s);
		index++;
	}
	t[index] = NULL;
	return (t);
}
