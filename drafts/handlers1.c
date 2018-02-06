#include "ft_printf.h"

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


t_str			build_t_str(t_format info, va_list args)
{

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
			char	*str;

			argdata.l = (long)va_arg(args, long);
			str = info.type == int_dec ? ft_itoa_base(argdata.l, DECIM): NULL;
			str = info.type == int_udec ? ft_uitoa_base(argdata.l, DECIM): str;
			str = info.type == int_uoct ? ft_uitoa_base(argdata.l, OCTAL): str;
			str = info.type == int_uhex_l ? ft_uitoa_base(argdata.l, HXLOW): str;
			str = info.type == int_uhex_u ? ft_uitoa_base(argdata.l, HXUPP): str;
		}
		else if (info.len_flag == fl_l && info.type == uchar)
		{
			char	*str;

			argdata.wc = (wchar_t)va_arg(args, wchar_t);
			str = encode_unicodepoint_to_utf8(argdata.wc);
		}
		else if (info.len_flag == fl_ll)
		{
			char	*str;

			argdata.ll = (long long)va_arg(args, long long);
			str = info.type == int_dec ? ft_itoa_base(argdata.ll, DECIM): NULL;
			str = info.type == int_udec ? ft_uitoa_base(argdata.ll, DECIM): str;
			str = info.type == int_uoct ? ft_uitoa_base(argdata.ll, OCTAL): str;
			str = info.type == int_uhex_l ? ft_uitoa_base(argdata.ll, HXLOW): str;
			str = info.type == int_uhex_u ? ft_uitoa_base(argdata.ll, HXUPP): str;
		}		
		else if (info.len_flag == fl_j)
		{
			char	*str;

			argdata.im = (intmax_t)va_arg(args, intmax_t);
			str = info.type == int_dec ? ft_itoa_base(argdata.im, DECIM): NULL;
			str = info.type == int_udec ? ft_uitoa_base(argdata.im, DECIM): str;
			str = info.type == int_uoct ? ft_uitoa_base(argdata.im, OCTAL): str;
			str = info.type == int_uhex_l ? ft_uitoa_base(argdata.im, HXLOW): str;
			str = info.type == int_uhex_u ? ft_uitoa_base(argdata.im, HXUPP): str;
		}
		else if (info.len_flag == fl_hh)
		{
			char	*str;

			argdata.c = (char)va_arg(args, int);
			str = info.type == int_dec ? ft_itoa_base(argdata.c, DECIM): NULL;
			str = info.type == int_udec ? ft_uitoa_base(argdata.c, DECIM): str;
			str = info.type == int_uoct ? ft_uitoa_base(argdata.c, OCTAL): str;
			str = info.type == int_uhex_l ? ft_uitoa_base(argdata.c, HXLOW): str;
			str = info.type == int_uhex_u ? ft_uitoa_base(argdata.c, HXUPP): str;
		}
		else if (info.len_flag == fl_h)
		{
			char	*str;

			argdata.sh = (short)va_arg(args, int);
			str = info.type == int_dec ? ft_itoa_base(argdata.sh, DECIM): NULL;
			str = info.type == int_udec ? ft_uitoa_base(argdata.sh, DECIM): str;
			str = info.type == int_uoct ? ft_uitoa_base(argdata.sh, OCTAL): str;
			str = info.type == int_uhex_l ? ft_uitoa_base(argdata.sh, HXLOW): str;
			str = info.type == int_uhex_u ? ft_uitoa_base(argdata.sh, HXUPP): str;
		}
		else if (info.len_flag == fl_z)
		{
			char	*str;

			argdata.si = (size_t)va_arg(args, size_t);
			str = info.type == int_dec ? ft_itoa_base(argdata.si, DECIM): NULL;
			str = info.type == int_udec ? ft_uitoa_base(argdata.si, DECIM): str;
			str = info.type == int_uoct ? ft_uitoa_base(argdata.si, OCTAL): str;
			str = info.type == int_uhex_l ? ft_uitoa_base(argdata.si, HXLOW): str;
			str = info.type == int_uhex_u ? ft_uitoa_base(argdata.si, HXUPP): str;
		}
	}
	if (info.type == string && info.len_flag != fl_l)
	{
		char	*str;

		str = (char*)va_arg(args, char*);
	}
	if (info.type == string && info.len_flag == fl_l)
	{
		char	*str;

		argdata.ws = (wchar_t*)va_arg(args, wchar_t*);
		str = build_utf8(argdata.ws);
	}


//TODO the objective is now to have the data in argdata be transformed into a first string, then have that string be altered, appended etc appropriately. 

/*
	int_dec,
	int_uoct,
	int_udec,
	int_uhex_l,
	int_uhex_u,
	uchar,
	string,
*/
	result.data = (char*)fmt;
	result.len = 0;
	return (result);
}
