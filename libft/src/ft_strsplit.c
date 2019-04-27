/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 13:48:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/01/26 19:21:36 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count(char *s, char c)
{
	int		compteur;
	int		present_chaine;

	present_chaine = 0;
	compteur = 0;
	while (*s != '\0')
	{
		present_chaine == 1 && *s == c && (present_chaine = 0);
		present_chaine == 0 && *s != c && compteur++;
		present_chaine == 0 && *s != c && (present_chaine = 1);
		s++;
	}
	return (compteur);
}

static int		ft_wlen(char *s, char c)
{
	int		len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char			**ft_strsplit(char *s, char c)
{
	char	**t;
	int		nb_word;
	int		index;

	if (!s)
		return (NULL);
	index = 0;
	nb_word = count(s, c);
	t = (char **)malloc(sizeof(*t) * (count(s, c) + 1));
	if (t == NULL)
		return (NULL);
	while (nb_word--)
	{
		while (*s == c && *s != '\0')
			s++;
		t[index] = ft_strsub(s, 0, ft_wlen(s, c));
		if (t[index] == NULL)
			return (NULL);
		s += ft_wlen(s, c);
		index++;
	}
	t[index] = NULL;
	return (t);
}
