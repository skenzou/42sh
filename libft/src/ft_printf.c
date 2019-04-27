/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 08:43:19 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/02 22:57:06 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_ype g_type[] = {
	{'c', &handle_char},
	{'%', &handle_char},
	{'s', &handle_string},
	{'p', &handle_number},
	{'P', &handle_number},
	{'f', &handle_number},
	{'F', &handle_number},
	{'d', &handle_number},
	{'D', &handle_number},
	{'i', &handle_number},
	{'I', &handle_number},
	{'o', &handle_number},
	{'O', &handle_number},
	{'u', &handle_number},
	{'U', &handle_number},
	{'X', &handle_number},
	{'x', &handle_number},
	{'b', &handle_number},
	{'B', &handle_number},
	{'v', &handle_array},
	{'r', &handle_array}
};

static int		check_flag(char **str)
{
	while (**str && !~ft_indexof(TYPES, **str))
	{
		if (!~ft_indexof("-+ #0lLhzj*.", **str) && !ft_isdigit(**str))
			return (0);
		(*str)++;
	}
	if (!(**str))
		return (0);
	(*str)++;
	return (1);
}

static int		parse(int fd, char *str, va_list ap)
{
	int		j;
	t_fmt	*fmt;
	int		l;

	l = 0;
	while (*str && (j = -1))
	{
		if (*str == '%')
		{
			fmt = get_options(++str, ap);
			if (check_flag(&str))
			{
				while (g_type[++j].type)
					if (g_type[j].type == fmt->type)
					{
						l += g_type[j].function(fd, ap, fmt);
						break ;
					}
				free(fmt);
			}
		}
		else
			write(1, str++, 1) && (l++);
	}
	return (l);
}

int				ft_dprintf(int fd, const char *restrict format, ...)
{
	int		length;
	va_list	ap;

	va_start(ap, format);
	length = parse(fd, (char *)format, ap);
	va_end(ap);
	return (length);
}

int				ft_printf(const char *restrict format, ...)
{
	int		length;
	va_list	ap;

	va_start(ap, format);
	length = parse(1, (char*)format, ap);
	va_end(ap);
	return (length);
}
