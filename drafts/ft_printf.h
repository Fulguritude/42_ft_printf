/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 15:52:29 by tduquesn          #+#    #+#             */
/*   Updated: 2018/01/05 15:53:00 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_PRINTF
# define __FT_PRINTF

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <locale.h>
# include "libft/libft.h"

/*
** http://computer-programming-forum.com/47-c-language/e00ad32ae4b4b1d6.htm
*/

/*
** Printf format specifier: https://en.wikipedia.org/wiki/Printf_format_string
**    => "%[parameters][flags][width][.precision][length]type"
*/

/*
** 'n$' to call the n-th parameter
** '*' for a dynamic width or precision specifier (ie, goes to get the next
**     arg, or '*n$' to call the n-th arg after format_str.
**     NB : printf("%*d", width, num) <=> printf("%2$*1$d", width, num)
*/

# define FLAGS "#0- +" //'
# define TYPES "pdDioOuUxXcCsS%" //eE, fF, gG, aA, n, bB
# define LGTHS "hljz" //L, t

# define ALL_SYMBOLS "#0- +pdDioOuUxXcCsS%.0123456789hljz"

//# define BINAR "01"
# define OCTAL "01234567"
# define DECIM "0123456789"
# define HXLOW "0123456789abcdef"
# define HXUPP "0123456789ABCDEF"

# define FL_HASH 0x1
# define FL_PLUS 0x2
# define FL_MINUS 0x4
# define FL_SPACE 0x8
# define FL_ZERO 0x10
//# define FL_QUOTE 0x20
# define FL_ERROR 0x80

typedef enum	e_types
{
	percent,
	int_dec,
	int_uoct,
	int_udec,
	int_uhex_l,
	int_uhex_u,
	uchar,
	string,
//	float, longlong, etc
	no_type_error
}				t_types;

typedef enum	e_len_flag
{
	fl_h,
	fl_hh,
	fl_l,
	fl_ll,
	fl_j,
	fl_z,
	no_len_flag,
	incoherent_len_flag
}				t_len_flag;

typedef struct	s_str
{
	char			*data;
	size_t			len;
}				t_str;

typedef struct	s_format
{
	t_u8			flags;
	int				width;
	int				prec;
	t_len_flag		len_flag;
	t_types			type;
}				t_format;

int				ft_printf(const char *format, ...);
int				ft_printf_fd(int fd, const char *format, ...);
int				ft_vprintf_fd(int fd, const char *format, va_list args);
int				ft_asprintf(char **res, const char *format, ...);
int				ft_vasprintf(char **res, const char *format, va_list args);

#endif
