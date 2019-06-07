/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 00:57:44 by midrissi          #+#    #+#             */
/*   Updated: 2019/06/07 06:16:05 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		remove_escape(char **str, int *start)
{
	char *tmp;
	char is_newline;

	is_newline = (*str)[*start + 1] == '\n';
	tmp = *str;
	if (!(*str = ft_strnew(ft_strlen(*str) - (1 - is_newline))))
		ft_exit("Malloc failed in remove_escape");
	ft_strncpy(*str, tmp, *start);
	ft_strcpy(*str + *start, tmp + *start + 1 + is_newline);
	free(tmp);
	(*start) += !is_newline;
}

static void		realloc_without_quotes(char **str, int start, int end)
{
	char *tmp;

	tmp = *str;
	if (!(*str = ft_strnew(ft_strlen(*str) - 2)))
		ft_exit("Malloc failed in realloc_without_quotes");
	ft_strncpy(*str, tmp, start);
	ft_strncpy((*str) + start, tmp + start + 1, end - start - 1);
	ft_strcpy((*str) + end - 1, tmp + end + 1);
	free(tmp);
}

static void		remove_double(char **str, int *i)
{
	int start;

	start = *i;
	(*i)++;
	while ((*str)[*i] && (*str)[*i] != '"')
	{
		if ((*str)[*i] == '\\' && is_special_char((*str)[*i + 1]))
			remove_escape(str, i);
		else
			(*i)++;
	}
	realloc_without_quotes(str, start, *i);
	(*i)--;
}

static void		remove_single(char **str, int *i)
{
	int start;

	start = *i;
	(*i)++;
	while ((*str)[*i] && (*str)[*i] != '\'')
		(*i)++;
	realloc_without_quotes(str, start, *i);
	(*i)--;
}

void			remove_quote(char **str)
{
	int i;

	if (!*str)
		return ;
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\' && (*str)[i + 1])
			remove_escape(str, &i);
		else if ((*str)[i] == '\'')
			remove_single(str, &i);
		else if ((*str)[i] == '"')
			remove_double(str, &i);
		else
			i++;
	}
}
