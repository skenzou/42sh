/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 06:45:33 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/14 06:35:23 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	remove_escape(char **str, int *start)
{
	char *tmp;
	char is_newline;

	is_newline = (*str)[*start + 1] == '\n';
	tmp = *str;
	*str = ft_strnew(ft_strlen(*str) - (1 - is_newline));
	ft_strncpy(*str, tmp, *start);
	ft_strcpy(*str + *start, tmp + *start + 1 + is_newline);
	free(tmp);
	(*start) += !is_newline;
}

static void realloc_without_quotes(char **str, int start, int end)
{
	char *tmp;

	tmp = *str;
	*str = ft_strnew(ft_strlen(*str) - 2);
	ft_strncpy(*str, tmp, start);
	ft_strncpy((*str) + start, tmp + start + 1, end - start - 1);
	ft_strcpy((*str) + end - 1, tmp + end + 1);
	free(tmp);
}

static int	is_special_char(char c)
{
	return (c == '$' || c == '\\' || c == '"' || c == '`' || c == '\n');
}

static void	remove_double(char **str, int *i)
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

static void	remove_single(char **str, int *i)
{
	int start;

	start = *i;
	(*i)++;
	while ((*str)[*i] && (*str)[*i] != '\'')
		(*i)++;
	realloc_without_quotes(str, start, *i);
	(*i)--;
}

void 		remove_quote(char **str)
{
	int i;

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

void 	redir_delone(void *data, size_t size)
{
	t_redir *redir;

	(void)size;
  if (data)
  {
    redir = ((t_redir *)(data));
    ft_splitdel(redir->dest);
	free(data);
  }
}

char	 **dup_tab(char **old, size_t size)
{
	char **new;
	size_t i;

	new = (char **)ft_memalloc(sizeof(char *) * (size + 1));
	!new ? ft_exit("Failed to allocate a new char** in realloc_new_tab"): 0;
	i = 0;
	while (i < size)
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

char		**join_2tab(char **curr, char **next, size_t curr_size, size_t next_size)
{
	char **new;
	size_t i;
	size_t j;

	new = (char **)ft_memalloc(sizeof(char *) * (curr_size + next_size + 1));
	!new ? ft_exit("Failed to allocate a new char** in realloc_new_tab") : 0;
	i = 0;
	while (i < curr_size)
	{
		new[i] = curr[i];
		i++;
	}
	j = 0;
	while (j < next_size)
		new[i++] = ft_strdup(next[j++]);
	free(curr);
	new[i] = NULL;
	return (new);
}

char		**realloc_new_tab(char *needle, char **old, size_t size)
{
	char **new;
	size_t i;

	new = (char **)ft_memalloc(sizeof(char *) * (size + 2));
	!new ? ft_exit("Failed to allocate a new char** in realloc_new_tab") : 0;
	i = 0;
	while (i < size)
	{
		new[i] = old[i];
		i++;
	}
	new[i] = needle;
	new[i + 1] = NULL;
	free(old);
	return (new);
}
