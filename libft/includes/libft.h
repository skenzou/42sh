/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 11:36:13 by aben-azz          #+#    #+#             */
/*   Updated: 2019/04/21 11:26:21 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# define MAX OPEN_MAX
# define BUFF_SIZE 32
# define ABS(x) ((x < 0) ? -x : x)

# define TYPES    "cspPfFdDiIoOuUXxbvr%"
# define LENGTH   "lhLzj"
# define HASH    (1 << 0)
# define ZERO    (1 << 1)
# define SUB     (1 << 2)
# define L_      (1 << 1) + 1
# define LL_     (1 << 1)
# define H_      (1 << 2) + 1
# define HH_     (1 << 2)
# define LU_     (1 << 3) + 1
# define Z_      (1 << 4) + 1
# define J_      (1 << 5) + 1

typedef struct	s_fmt
{
	int				prec;
	int				length;
	int				type;
	int				field;
	int				opt;
	int				signe;
	int				prefixe;
}				t_fmt;
typedef struct	s_ype
{
	int				type;
	int				(*function)(int fd, va_list list, t_fmt *fmt);
}				t_ype;
typedef struct	s_gnl
{
	int			i;
	int			i_read;
	char		buff[BUFF_SIZE + 1];
	char		*ptr_leak;
	char		*s[MAX];
}				t_gnl;
typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;
typedef	unsigned short int	t_bits;
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, void *src, size_t n);
void			*ft_memccpy(void *dst, void *src, int c, size_t n);
void			*ft_memmove(void *dst, void *src, size_t len);
void			*ft_memchr(void *s, int c, size_t n);
int				ft_memcmp(void *s1, void *s2, size_t n);
size_t			ft_strlen(char *s);
char			*ft_strdup(char *s1);
char			*ft_strcpy(char *dst, char *src);
char			*ft_strncpy(char *dst, char *src, size_t len);
char			*ft_strcat(char *s1, char *s2);
char			*ft_strncat(char *s1, char *s2, size_t n);
size_t			ft_strlcat(char *dst, char *src, size_t size);
char			*ft_strchr(char *s, int c);
char			*ft_strrchr(char *s, int c);
char			*ft_strstr(char *haystack, char *needle);
char			*ft_strnstr(char *haystack, char *needle, size_t len);
int				ft_intlen(long long len);
int				ft_intlen_base(uintmax_t nbr, int base);
int				ft_strcmp(char *s1, char *s2);
int				ft_strncmp(char *s1, char *s2, size_t n);
int				ft_atoi(char *str);
char			*ft_ftoa(long double n, int precision);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_islower(int c);
int				ft_isupper(int c);
int				ft_is_space(int c);
int				ft_indexof(char *source, char c);
int				ft_lastindexof(char *source, char c);
int				ft_count(char *source, char c);
int				ft_repeat_char(int fd, char source, int c);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
int				ft_count_words(char const *s, char c);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char *s, char (*f)(char));
char			*ft_strmapi(char *s, char (*f)(unsigned int, char));
int				ft_strequ(char *s1, char *s2);
int				ft_strnequ(char *s1, char *s2, size_t n);
char			*ft_strsub(char *s, unsigned int start, size_t len);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strtrim(char *s);
char			**ft_strsplit(char *s, char c);
char			*ft_itoa(int n);
size_t			ft_putchar(char c);
size_t			ft_putstr(char *s);
size_t			ft_putendl(char *s);
void			ft_putnbr(long long n);
size_t			ft_putchar_fd(char c, int fd);
size_t			ft_putstr_fd(char *s, int fd);
size_t			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(long long n, int fd);
char			*ft_itoa_base(intmax_t n, int base, int islower);
char			*ft_utoa_base(uintmax_t nb, int base, int uppercase);
long long		ft_pow(int base, int i);
long double		ft_round(long double fl, long precision);
int				min(int a, int b);
int				max(int a, int b);

t_list			*ft_lstnew(void *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstrev(t_list **alst);
int				ft_lstdestroy(t_list **lst);
int				get_next_line(int fd, char **line, char separator);
int				is_even(int number);
int				abs(int n);
int				ft_counti(char *string, char c, int i);
t_bits			get_bit(t_bits i, t_bits n);
t_bits			rev_bit(t_bits i, t_bits n);
t_bits			up_bit(t_bits i, t_bits n);
t_bits			down_bits(t_bits i, t_bits n);
int				handle_char(int fd, va_list list, t_fmt *fmt);
int				handle_string(int fd, va_list list, t_fmt *fmt);
int				handle_array(int fd, va_list list, t_fmt *fmt);
int				print_numbers(int fd, t_fmt *fmt, char *str, int len);
int				handle_number(int fd, va_list ap, t_fmt *fmt);
t_fmt			*get_options(char *s, va_list ap);
char			*get_s(t_fmt *fmt, va_list ap);
int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);
unsigned long	rgb2dec(int r, int g, int b);
double			ft_percent(int start, int end, int curr);
int				ft_get_color_from_percent(int color1, double percentage);
long long		ft_rand(long long n);
int				ft_strendswith(char *s1, char *s2);
int				ft_strstartswith(char *s1, char *s2);
char			*ft_strreplace(char *orig, char *rep, char *with);
char			**ft_strsplitwhitespace(char *orig);
char*			ft_substr(char *src, int m, int n);
#endif
