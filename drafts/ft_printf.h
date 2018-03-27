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

//TODO remove fsanitize from makefile

#ifndef __FT_PRINTF
# define __FT_PRINTF

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <locale.h>
# include <inttypes.h>
# include "libft/hdr/libft.h"

/*
** http://computer-programming-forum.com/47-c-language/e00ad32ae4b4b1d6.htm
** http://steve.hollasch.net/cgindex/coding/ieeefloat.html
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
# define TYPES "pdDibBoOuUxXcCsSeEfFgGaAr%" //n
# define LGTHS "hljz" //L, t

# define ALL_SYMBOLS "#0- +pdDibBoOuUxXcCsSeEfFgGaAr%.0123456789hljz"

# ifndef __BASES__
#  define __BASES__
#  define BINAR "01"
#  define OCTAL "01234567"
#  define DECIM "0123456789"
#  define HXLOW "0123456789abcdef"
#  define HXUPP "0123456789ABCDEF"
# endif

# ifndef __ANSI_CODES__
#  define __ANSI_CODES__
#  define BOLD			"\x1b[1m"
#  define UNDERLINE		"\x1b[4m"
#  define C_BLACK		"\x1b[30m"
#  define C_RED			"\x1b[31m"
#  define C_GREEN		"\x1b[32m"
#  define C_YELLOW		"\x1b[33m"
#  define C_BLUE		"\x1b[34m"
#  define C_MAGENTA		"\x1b[35m"
#  define C_CYAN		"\x1b[36m"
#  define C_WHITE		"\x1b[37m"
#  define BG_BLACK		"\x1b[40m"
#  define BG_RED		"\x1b[41m"
#  define BG_GREEN		"\x1b[42m"
#  define BG_YELLOW		"\x1b[43m"
#  define BG_BLUE		"\x1b[44m"
#  define BG_MAGENTA	"\x1b[45m"
#  define BG_CYAN		"\x1b[46m"
#  define BG_WHITE		"\x1b[47m"
#  define RESET			"\x1b[0m"
# endif

# ifndef __FT_PRINTF_ANSI_STRINGS__
#  define __FT_PRINTF_ANSI_STRINGS__
#  define STR_BOLD			"{bold}"
#  define STR_UNDERLINE		"{uline}"
#  define STR_BLACK			"{black}"
#  define STR_RED			"{red}"
#  define STR_GREEN			"{green}"
#  define STR_YELLOW		"{yellow}"
#  define STR_BLUE			"{blue}"
#  define STR_MAGENTA		"{magenta}"
#  define STR_CYAN			"{cyan}"
#  define STR_WHITE			"{white}"
#  define STR_BG_BLACK		"{black_bg}"
#  define STR_BG_RED		"{red_bg}"
#  define STR_BG_GREEN		"{green_bg}"
#  define STR_BG_YELLOW		"{yellow_bg}"
#  define STR_BG_BLUE		"{blue_bg}"
#  define STR_BG_MAGENTA	"{magenta_bg}"
#  define STR_BG_CYAN		"{cyan_bg}"
#  define STR_BG_WHITE		"{white_bg}"
#  define STR_RESET			"{eoc}"
# endif

# define FL_HASH	0x1
# define FL_PLUS	0x2
# define FL_MINUS	0x4
# define FL_SPACE	0x8
# define FL_ZERO	0x10
/*
** # define FL_QUOTE 0x20 //add "\'" to flags
*/
# define FL_NONE 0x40
# define FL_ERROR 0x80

/*
** Section to edit platform dependent primitive type byte lengths.
*/
# define BYTELEN_CHAR		1
# define BYTELEN_SHORT		2
# define BYTELEN_INT		4
# define BYTELEN_LONG		8
# define BYTELEN_LONGLONG	8
# define BYTELEN_IMAX		8
# define BYTELEN_SIZET		8
# define BYTELEN_FLOAT		4
# define BYTELEN_DOUBLE		8

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
	float_pt,
	no_type_error
}				t_types;

typedef enum	e_len_flag
{
	fl_hh,
	fl_h,
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
	int				len;
}				t_str;

typedef struct	s_format
{
	t_u8			flags;
	int				width;
	int				prec;
	t_len_flag		len_flag;
	t_types			type;
	char			type_char;
}				t_format;

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
void			convert_str(char const *fmt_part, t_list **a_lststr,
							va_list args);
t_format		read_format(char const *fmt_part);

/*
** converter_utils_rdfmt.c
**
** TODO, when out of norminette, put in the same file as read_format as static
*/
t_u8			read_format_flags(char const *fmt_part, int *i);
int				read_format_width(char const *fmt_part, int *i);
int				read_format_prec(char const *fmt_part, int *i);
t_len_flag		read_format_len_flag(char const *fmt_part, int *i);
t_types			read_format_type(char const *fmt_part, t_format *info, int i);

/*
** handlers.c
*/
t_str			*handle_format(t_format info, char const *fmt, va_list args);

/*
** handler_utils_int.c
**
** static char  *val_to_str(t_types type, t_u8 flags, intmax_t n, int *digits)
** static char  *flag_prepend(t_types type, t_u8 flags, intmax_t n, char **a_s)
** static t_str	build_int_str(t_format info, intmax_t n)
*/
t_str			*handle_int_type(t_format info, va_list args);

/*
** handler_utils_float.c
*/
t_str			*handle_float_type(t_format info, va_list args);

/*
** handler_utils_str.c
**
** static char			*encode_unicodepoint_to_utf8(wchar_t c);
** static char			*build_utf8(wchar_t *unicode_str);
*/
t_str			*handle_uchar_type(t_len_flag len_flag, va_list args);
t_str			*handle_str_type(t_format info, va_list args);

/*
** utils_t_str.c
**
** static void	t_str_append(t_str *acc, t_str *next);
*/
void			del_t_str(void *content, size_t content_size);
t_str			to_single_t_str(t_list *lststr); //handlers?
t_str			*str_to_t_str(char const *str); //converters? 

#endif
