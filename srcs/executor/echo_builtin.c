/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 15:44:19 by midrissi          #+#    #+#             */
/*   Updated: 2019/11/06 17:32:07 by tlechien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

# define CHS_LEN 		8

static long		ft_pow(int base, int pow)
{
	long long result;

	result = 1;
	while (pow-- > 0)
	{
		result *= base;
		if (result > LONG_MAX)
			return (0);
	}
	return (result);
}

static int		b_conv(char *str, int len, int base)
{
	int value;
	int	i;

	value = 0;
	i = 0;
	while (len--)
	{
		if (i == 0 && str[i] > 51)
			str[i] = str[i] - 4;
		value = value + ((str[i] - '0') *ft_pow(base, len));
		i++;
	}
	return (value);
}

static int		sub_char(char **line, int i, char c)
{
	char *str ;
	str = *line + i;

	ft_strncpy(str, str + 1, ft_strlen2(str));
	str[0] = c;
	return (0);
}

static int		sub_oct(char **line, int i)
{
	char	*str;
	int		len;
	int		conv;

	str = *line + i;
	len = 0;
	while (*(str + 2 + len) && ft_isdigit(*(str + 2 + len)) && str[2 + len] < 56 && len < 3)
		len++;
	conv = b_conv(str + 2, len, 8);
	if (len > 0)
		len--;
	ft_printf("str: %s \nlen : %d\nnum : %s\n", str, len, str +2);
	ft_strncpy(str, str + 2 + len, ft_strlen2(str));
	if (len > 0)
		str[0] = conv;
	return (0);
}

int		treat_spec(char **ptr)
{
	char	*line;
	int		i;
	int		y;
	char	charset_r[CHS_LEN] = {'a', 'b', 'c', 'f', 'n', 'r', 't', 'v'};
	char	charset_w[CHS_LEN] = {'\a', '\b', '\0', '\f', '\n', '\r', '\t', '\v'};

	line = *ptr;
	i = -1;
	while (line[++i])
	{
		if (line[i] == 92 && line[i + 1] != '0')
		{
			y = -1;
			while ((++y) < CHS_LEN)
			{
				if (line[i + 1] == charset_r[y])
				{
					sub_char(&line, i, charset_w[y]);
					if (y == 2)
						return (1);
					break;
				}
			}
		}
		else if (line[i] == 92 && line[i + 1] == '0')
			sub_oct(&line, i);
	}
	return (0);
}

int			echo_builtin(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc > 1 && !ft_strcmp(argv[1], "-n"))
		i++;
	if (argc == 1 && i == 0)
		ft_putchar('\n');
	if (argc > 1)
		while (++i < argc)
		{
			if (treat_spec(&argv[i]) || i < argc - 1)
				ft_printf("%s ", argv[i]);
			else
				ft_printf("%s\n", argv[i]);
		}
	return (0);
}
