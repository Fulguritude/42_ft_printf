/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 15:52:29 by tduquesn          #+#    #+#             */
/*   Updated: 2018/02/20 21:38:36 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_PRINTF
# define __FT_PRINTF

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <locale.h>
# include <inttypes.h>
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
# define TYPES "pdDibBoOuUxXcCsS%" //eE, fF, gG, aA, n
# define LGTHS "hljz" //L, t

# define ALL_SYMBOLS "#0- +pdDibBoOuUxXcCsS%.0123456789hljz"

# define BINAR "01"
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
# define FL_NONE 0x40
# define FL_ERROR 0x80

typedef enum	e_types
{
	percent,
	int_dec,
	int_uoct,
	int_udec,
	int_uhex_l,
	int_uhex_u,
	int_ubin_l,
	int_ubin_u,
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


/*
typedef union	u_data
{
	t_u8			c;
	short			sh;
	int				i;
	long			l;
	long long		ll;
	char			*st;
	size_t			si;
	wchar_t			wc;
	wchar_t			*ws;
	intmax_t		im;
}				t_data;
*/

/*
** ft_printf.c
*/

int				ft_printf(const char *format, ...);
int				ft_printf_fd(int fd, const char *format, ...);
int				ft_vprintf_fd(int fd, const char *format, va_list args);
int				ft_asprintf(char **res, const char *format, ...);
int				ft_vasprintf(char **res, const char *format, va_list args);

/*
** converters.c
*/

char			**format_to_strls(char const *format);
void			convert_str(char *fmt_part, t_list **a_lststr, va_list args);

/*
** handlers.c
**
** static t_str		handle_uchar_type(t_len_flag len_flag, va_list args);
** static t_str		handle_str_type(t_format info, va_list args);
*/

t_str			handle_format(t_format info, char const *fmt, va_list args);

/*
** utils_int_handler.c
**
** static char  *val_to_str(t_types type, t_u8 flags, intmax_t n, int *digits)
** static char  *flag_prepend(t_types type, t_u8 flags, intmax_t n, char **a_s)
** static t_str	build_int_str(t_format info, intmax_t n)
*/

t_str			handle_int_type(t_format info, va_list args);

/*
** unicode.c
*/

char			*encode_unicodepoint_to_utf8(wchar_t c);
char			*build_utf8(wchar_t *unicode_str);

/*
** utils_format_string.c
*/
 
t_u8			read_format_flags(char const *fmt_part, int *i);
int				read_format_width(char const *fmt_part, int *i);
int				read_format_prec(char const *fmt_part, int *i);
t_len_flag		read_format_len_flag(char const *fmt_part, int *i);
t_types			read_format_type(char const *fmt_part, t_format *info, int i);
t_format		read_format(char const *fmt_part);

/*
** utils_t_str.c
*/

t_str	to_single_t_str(t_list *lststr);
//static void	t_str_append(t_str *acc, t_str *next);
t_str	str_to_t_str(char const *str);

#endif
