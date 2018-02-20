#include "ft_printf.h"


#include <stdio.h>


/*
** http://blog.aaronballman.com/2012/06/how-variable-argument-lists-work-in-c/
*/

/*
** In the absence of a prototype the compiler performs default promotions
** of certain arguments to functions:
** 
** 1.  Signed integer types smaller than int (signed char, signed short),
** are promoted to signed int.
** 
** 2.  Unsigned integer types smaller than int (unsigned char, unsigned
** short) are promoted to signed int, if signed int can hold all the
** entire range of values of the smaller unsigned type, or to unsigned
** int.
** 
** 3.  Plain char (defined without signed or unsigned) is promoted to
** either signed or unsigned int depending on whether plain char is
** signed or unsigned for that particular compiler, according to rule 1
** or 2.
** 
** 4.  Floating point arguments of type float are promoted to type
** double.
** 
** Other argument types, signed or unsigned int, long, or long long,
** floating point types double and long double, and pointer types are not
** promoted at all but are passed to the function as is. 
*/

/*
** FL_ZERO doesn't apply to strings
*/

static t_str	handle_str_type(t_format info, va_list args)
{
	char	*str;
	t_str	result;

	if (info.len_flag == fl_l)
		str = build_utf8((wchar_t*)va_arg(args, wchar_t*));
	else
		str = ft_strdup((char*)va_arg(args, char*));
////printf("\tbuild_pcs_str : %s\n", str);
	if (info.prec != -1 && info.prec < (int)ft_strlen(str))
	{
		if (info.len_flag == fl_l)
			while (str[info.prec] >> 6 == 0x2)
				--info.prec;
		str[info.prec] = '\0';
	}
	if (info.width != -1 && info.width > (int)ft_strlen(str))
		result.data = (info.flags & FL_MINUS) ?
			ft_strpad_right(str, ' ', info.width - ft_strlen(str)) :
			ft_strpad_left(str, ' ', info.width - ft_strlen(str));
	else
		result.data = ft_strdup(str);
	free(str);
	result.len = ft_strlen(result.data);
	return (result);
}

static t_str		handle_uchar_type(t_len_flag len_flag, va_list args)
{
	t_str	result;
	wchar_t wc;

	if (len_flag == fl_l)
	{
		wc = (wchar_t)va_arg(args, wchar_t);
		result.data = encode_unicodepoint_to_utf8(wc);
		result.len = 1 + (wc > 0x7F) + (wc > 0x7FF) + (wc > 0xFFFF);
	}
	else
	{
		result.data = ft_strnew(1);
		result.data[0] = (char)va_arg(args, int);
		result.len = 1;
	}
	return (result);
}

t_str				handle_format(t_format info, char const *fmt, va_list args)
{
	//return result.len == (size_t)-1 in case of incoherent format
	//return result.len == (size_t)-2 in case of unicode error
//printf("handler result: data = %s ; len = %lu\n", result.data, result.len);
	t_str	result;

	if (info.type == percent && info.flags == FL_NONE && info.width == -1 &&
		info.prec == -1 && info.len_flag == no_len_flag)
		return (str_to_t_str("%"));
	else if (info.type == percent || info.type == no_type_error ||
		info.len_flag == incoherent_len_flag)
		return (str_to_t_str(fmt));
	else if (int_dec <= info.type && info.type <= int_uhex_u)
		return (handle_int_type(info, args));
	else if (info.type == string)
		return (handle_str_type(info, args));
	else if (info.type == uchar)
		return (handle_uchar_type(info.len_flag, args));
	else
	{
		result.data = NULL;
		result.len = -1;
		return (result);
	}
}
