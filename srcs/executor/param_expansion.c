/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:34:20 by midrissi          #+#    #+#             */
/*   Updated: 2019/11/06 19:47:46 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			*goto_closing_brace(char *str)
{
	while (*str && *str != '}')
		str++;
	if (*str)
		return (str);
	else
		return (NULL);
}

static char			*dollar_curly(char *old, char *ptr, int *i)
{
	char	*str;
	char	*key;
	char	*value;
	int		len_after_brace;

	str = goto_closing_brace(ptr) + 1;
	if (!(key = ft_strsub(ptr, 2, str - ptr - 3)))
		shell_exit(MALLOC_ERR);
	value = get_all_key_value(key, g_shell->env);
	if (!value)
		value = "";
	len_after_brace = ft_strlen2(str);
	if (!(ptr = ft_strnew(*i + ft_strlen2(value) + len_after_brace)))
		shell_exit(MALLOC_ERR);
	ft_strncpy(ptr, old, *i);
	ft_strcat(ptr, value);
	ft_strcat(ptr, str);
	*i = *i + ft_strlen2(value) - 1;
	free(key);
	free(old);
	return (ptr);
}

static int			len_to_next_dollar(char *str)
{
	int len;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}

static char			*simple_dollar(char *old, char *ptr, int *i)
{
	char	*key;
	char	*value;
	char	*ptr_after_exp;
	int		len_after_exp;
	int		exp_len;

	exp_len = len_to_next_dollar(ptr + 1);
	ptr_after_exp = ptr + 1 + exp_len;
	if (!(key = ft_strsub(ptr, 1, exp_len)))
		shell_exit(MALLOC_ERR);
	value = get_all_key_value(key, g_shell->env);
	if (!value)
		value = "";
	len_after_exp = ft_strlen2(ptr_after_exp);
	if (!(ptr = ft_strnew(len_after_exp + ft_strlen2(value) + *i)))
		shell_exit(MALLOC_ERR);
	ft_strncpy(ptr, old, *i);
	ft_strcat(ptr, value);
	ft_strcat(ptr, ptr_after_exp);
	*i = *i + ft_strlen2(value) - 1;
	free(old);
	free(key);
	return (ptr);
}

void				param_expansion(char **ptr)
{
	char	*str;
	int		i;

	if (!*ptr || ft_strlen2(*ptr) == 0)
		return ;
	str = *ptr;
	i = 0;
	while (str[i])
	{
		if (str[i] == BSLASH && str[i + 1])
			i++;
		else if (str[i] == '$' && str[i + 1] == '{')
		{
			if (!goto_closing_brace(str + i + 2))
				return ;
			str = dollar_curly(str, str + i, &i);
		}
		else if (str[i] == '$')
			str = simple_dollar(str, str + i, &i);
		i++;
	}
	if (ft_strlen2(str) == 0)
		ft_strdel(&str);
	*ptr = str;
}
