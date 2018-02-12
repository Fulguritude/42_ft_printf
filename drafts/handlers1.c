#include "ft_printf.h"


#include <stdio.h>


/*
	t_u8			flags;
	int				width;
	int				prec;
	t_len_flag		len_flag;
	t_types			type;
*/

/*
** http://blog.aaronballman.com/2012/06/how-variable-argument-lists-work-in-c/
*/

/*
In the absence of a prototype the compiler performs default promotions
of certain arguments to functions:

1.  Signed integer types smaller than int (signed char, signed short),
are promoted to signed int.

2.  Unsigned integer types smaller than int (unsigned char, unsigned
short) are promoted to signed int, if signed int can hold all the
entire range of values of the smaller unsigned type, or to unsigned
int.

3.  Plain char (defined without signed or unsigned) is promoted to
either signed or unsigned int depending on whether plain char is
signed or unsigned for that particular compiler, according to rule 1
or 2.

4.  Floating point arguments of type float are promoted to type
double.

Other argument types, signed or unsigned int, long, or long long,
floating point types double and long double, and pointer types are not
promoted at all but are passed to the function as is. 
*/

/*
** The precision field does not apply to numeric types, only floats and strings.
*/

t_str			build_int_str(t_format info, intmax_t n)
{
	char	*str;
	char	*tmp;
	int		digits;
	t_str	result;

	str = info.type == int_dec ? ft_itoa_base(n, DECIM): NULL;
	str = info.type == int_udec ? ft_uitoa_base(n, DECIM): str;
	str = info.type == int_uoct ? ft_uitoa_base(n, OCTAL): str;
	str = info.type == int_uhex_l ? ft_uitoa_base(n, HXLOW): str;
	str = info.type == int_uhex_u ? ft_uitoa_base(n, HXUPP): str;
////printf("\tbuild_int_str str: %s\n", str);
//the following line find out the number of symbols before width
//Add two digits for a hash, remove one if the hash is an octal;
//      add one digit for a signed value with appropriate flag;
	digits = ft_strlen(str) - (info.type == int_uoct)
		+ 2 * ((info.flags & FL_HASH) && (info.type != int_dec))
		+ (info.type == int_dec && (info.flags & (FL_SPACE | FL_PLUS)));
//printf("\tbuild_int_str digits: %d\n", digits);
//highest priority is FL_MINUS that cancels FL_ZERO
//then prepend 0s if FL_ZERO, then apply FL_HASH
//if no FL_ZERO, first FL_HASH then prepend sign/spaces
	if ((info.flags & FL_ZERO) && info.width > digits)
		str = (info.flags & FL_MINUS) ? ft_strpad_right(str, ' ', info.width - digits) :
										ft_strpad_left(str, '0', info.width - digits);
	tmp = info.type == int_uoct && (info.flags & FL_HASH) ? "0" : "";
	tmp = info.type == int_uhex_l && (info.flags & FL_HASH) ? "0x" : tmp;
	tmp = info.type == int_uhex_u && (info.flags & FL_HASH) ? "0X" : tmp;
	tmp = info.type == int_dec && n > 0 && (info.flags & FL_SPACE) ? " " : tmp;
	tmp = info.type == int_dec && n > 0 && (info.flags & FL_PLUS) ? "+" : tmp;
	tmp = ft_strprepend(tmp, &str);
////printf("\tbuild_int_str tmp: %s\n", tmp);
	if (!(info.flags & FL_ZERO) && info.width > digits)
	{
		str = (info.flags & FL_MINUS) ? ft_strpad_right(tmp, ' ', info.width - digits) :
										ft_strpad_left(tmp, ' ', info.width - digits);
		free(tmp);
	}
////printf("\tbuild_int_str str: %s\n", str);
	result.data = str;
	result.len = info.width > digits ? info.width : digits;
////printf("\tbuild_int_str result: data = %s ; len = %lu\n", result.data, result.len);
	return (result);
}

t_str			handle_format(t_format info, char const *fmt, va_list args)
{
	//return result.len == (size_t)-1 in case of incoherent format
	//return result.len == (size_t)-2 in case of unicode error
	t_str	result;
	t_data	argdata;

	if (info.type == percent && info.flags == 0 && info.width == -1 &&
		info.prec == -1 && info.len_flag == no_len_flag)
		return (str_to_t_str("%"));
	if (info.type == percent || info.type == no_type_error ||
		info.len_flag == incoherent_len_flag)
		return (str_to_t_str(fmt));
	if (int_dec <= info.type && info.type <= uchar)
	{
		if (info.len_flag == fl_l && info.type != uchar)
		{
			argdata.l = (long)va_arg(args, long);
			result = build_int_str(info, argdata.l);
		}
		else if (info.type == uchar)
		{
			if (info.len_flag == fl_l)
			{
				argdata.wc = (wchar_t)va_arg(args, wchar_t);
				result.data = encode_unicodepoint_to_utf8(argdata.wc);
				wchar_t c = argdata.wc;
				result.len = 1 + (c > 0x7F) + (c > 0x7FF) + (c > 0xFFFF);
			}
			else
			{
				result.data = ft_strnew(1);
				result.data[0] = (char)va_arg(args, int);
				result.len = 1;
			}
		}
		else if (info.len_flag == fl_ll)
		{
			argdata.ll = (long long)va_arg(args, long long);
			result = build_int_str(info, argdata.ll);
		}		
		else if (info.len_flag == fl_j)
		{
			argdata.im = (intmax_t)va_arg(args, intmax_t);
			result = build_int_str(info, argdata.im);
		}
		else if (info.len_flag == fl_hh)
		{
			argdata.c = (char)va_arg(args, int);
			result = build_int_str(info, argdata.c);
		}
		else if (info.len_flag == fl_h)
		{
			argdata.sh = (short)va_arg(args, int);
			result = build_int_str(info, argdata.sh);
		}
		else if (info.len_flag == fl_z)
		{
			argdata.si = (size_t)va_arg(args, size_t);
			result = build_int_str(info, argdata.si);
		}
		else
		{
			argdata.i = (int)va_arg(args, int);
			result = build_int_str(info, argdata.i);
		}
	}
	else if (info.type == string && info.len_flag != fl_l)
	{
		char	*str;

//FL_ZERO doesn't apply to strings
		str = ft_strdup((char*)va_arg(args, char*));
printf("\tbuild_pcs_str : %s\n", str);
		if (info.prec != -1 && info.prec < (int)ft_strlen(str))
			str[info.prec] = '\0';
		if (info.width != -1 && info.width > (int)ft_strlen(str))
		{
			result.data = (info.flags & FL_MINUS) ? ft_strpad_right(str, ' ', info.width - ft_strlen(str)) :
										ft_strpad_left(str, ' ', info.width - ft_strlen(str));
			free(str);
		}
		else
			result.data = str;
		result.len = ft_strlen(result.data);
	}
	else if (info.type == string && info.len_flag == fl_l)
	{
		char	*str;

		argdata.ws = (wchar_t*)va_arg(args, wchar_t*);
		str = build_utf8(argdata.ws);
		if (info.prec != -1 && info.prec < (int)ft_strlen(str))
		{
			while (str[info.prec] >> 6 == 0x2)
				--info.prec;
			str[info.prec] = '\0';
		}
		if (info.width != -1 && info.width > (int)ft_strlen(str) && (info.flags & FL_MINUS))
			result.data = ft_strpad_right(str, ' ', info.width - ft_strlen(str));
		else if (info.width != -1 && info.width > (int)ft_strlen(str))
			result.data = ft_strpad_left(str, ' ', info.width - ft_strlen(str));
		else
			result.data = ft_strdup(str);
		free(str);
		result.len = ft_strlen(result.data);
	}


/*
	int_dec,
	int_uoct,
	int_udec,
	int_uhex_l,
	int_uhex_u,
	uchar,
	string,
*/

printf("handler result: data = %s ; len = %lu\n", result.data, result.len);

	return (result);
}
