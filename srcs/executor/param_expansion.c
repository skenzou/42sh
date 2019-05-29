/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 17:34:20 by midrissi          #+#    #+#             */
/*   Updated: 2019/05/29 20:12:05 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*goto_closing_brace(char *str)
{
	while (*str && *str != '}')
		str++;
	if (*str)
		return (str);
	else
		return (NULL);
}

char		*dollar_curly(char *old, char *ptr, int *i)
{
	char	*str;
	char	*key;
	char	*value;
	int		len_after_brace;

	str = goto_closing_brace(ptr) + 1;
	if (!(key = ft_strsub(ptr, 2, str - ptr - 3)))
		ft_exit("Malloc failed in reform_string");
	value = get_key_value(key, g_shell->env);
	if (!value)
		value = get_key_value(key, g_shell->intern);
	if (!value)
		value = "";
	len_after_brace = ft_strlen(str);
	if (!(ptr = ft_strnew(*i + ft_strlen(value) + len_after_brace)))
		ft_exit("Malloc failed in dollar_curly");
	ft_strncpy(ptr, old, *i);
	ft_strcat(ptr, value);
	ft_strcat(ptr, str);
	*i = *i + ft_strlen(value) - 1;
	free(key);
	free(old);
	return (ptr);
}

int			len_to_next_dollar(char *str)
{
	int len;

	len = 0;
	while (str[len] && str[len] != '$')
		len++;
	return (len);
}

char		*simple_dollar(char *old, char *ptr, int *i)
{
	char	*key;
	char	*value;
	char	*ptr_after_exp;
	int		len_after_exp;
	int		exp_len;

	exp_len = len_to_next_dollar(ptr + 1);
	ptr_after_exp = ptr + 1 + exp_len;
	if (!(key = ft_strsub(ptr, 1, exp_len)))
		ft_exit("Malloc failed in reform_string");
	value = get_key_value(key, g_shell->env);
	if (!value)
		value = get_key_value(key, g_shell->intern);
	if (!value)
		value = "";
	len_after_exp = ft_strlen(ptr_after_exp);
	if (!(ptr = ft_strnew(len_after_exp + ft_strlen(value) + *i)))
		ft_exit("Malloc failed in simple_dollar");
	ft_strncpy(ptr, old, *i);
	ft_strcat(ptr, value);
	ft_strcat(ptr, ptr_after_exp);
	*i = *i + ft_strlen(value) - 1;
	free(old);
	free(key);
	return (ptr);

}

void		param_expansion(char **ptr)
{
	char *str;
	int i;

	str = *ptr;
	i = 0;
	while (str[i])
	{
		if (str[i] == BSLASH && str[i + 1])
			i++;
		else if (str[i] == '$' && str [i+ 1] == '{')
		{
			if (!goto_closing_brace(str + i + 2))
				return ;
			str = dollar_curly(str, str + i, &i);
		}
		else if (str[i] == '$')
		{
			str = simple_dollar(str, str + i, &i);
		}
		i++;
	}
	if (ft_strlen(str) == 0)
		ft_strdel(&str);
	*ptr = str;
}
