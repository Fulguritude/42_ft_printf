#include "ft_printf.h"


//TODO REMOVE
#include <stdio.h>



/*
** The precision field does not apply to numeric types, only floats and strings.
**
** "digits" is used to find out the number of symbols before width
** => Add two digits for a hash, remove one if the hash is an octal;
**      add one digit for a signed value with appropriate flag;
** => For precision, 0 flag is ignored, and precision is applied before width
**
** => ft_ivartoa_base was coded to force integer casting; memory would be 
**		filled with ones rather than zeros in a few cases.
*/

static char		*ft_ivartoa_base(intmax_t n, char const *base, t_u8 bytes,
									t_u8 has_sign)
{
	t_varint	varint;

	varint.l = 0;
	if (bytes == 1)
		varint.c = (char)n;
	else if (bytes == 2)
		varint.s = (short)n;
	else if (bytes == 4)
		varint.i = (int)n;
	else if (bytes == 8)
		varint.l = (long)n;
	else
		return (NULL);
//printf("varint.l : %lx\n\t\t\t", varint.l);
	if (has_sign == 's')
		return (ft_imaxtoa_base(varint.l, base));
	else if (sign == 'u')
		return (ft_uimaxtoa_base(varint.l, base));
	else
		return (NULL);
}

static char		*val_to_str(t_format info, intmax_t n, int *digits, t_u8 bytes)
{
	char	*str;
	t_u32	prec;

	str = NULL;
	prec = info.prec <= 0 ? 0 :
		(t_u32)info.prec - (info.type == int_uoct && (info.flags & FL_HASH));
	if (info.type == int_dec)
		str = ft_ivartoa_base(n, DECIM, bytes, 's');
	else if (info.type == int_udec)
		str = ft_ivartoa_base(n, DECIM, bytes, 'u');
	else if (info.type == int_uoct)
		str = ft_ivartoa_base(n, OCTAL, bytes, 'u');
	else if (info.type == int_uhex_l)
		str = ft_ivartoa_base(n, HXLOW, bytes, 'u');
	else if (info.type == int_uhex_u)
		str = ft_ivartoa_base(n, HXUPP, bytes, 'u');
	else if (info.type == int_ubin_l || info.type == int_ubin_u)
		str = ft_ivartoa_base(n, BINAR, bytes, 'u');
	*digits = (ft_strlen(str) > prec ? ft_strlen(str) : prec)
		+ 2 * ((info.flags & FL_HASH) &&
			(int_uoct <= info.type) && (info.type <= int_ubin_u))
		- (info.type == int_uoct && (info.flags & FL_HASH))
		+ (info.type == int_dec && (info.flags & (FL_SPACE | FL_PLUS)));
	return (str);
}

static void		flag_prepend(t_types type, t_u8 flags, intmax_t n, char **a_s)
{
	char	*prefix;

	prefix = "";
	if (type == int_uoct && (flags & FL_HASH))
		prefix = "0";
	else if (type == int_uhex_l && (flags & FL_HASH))
		prefix = "0x";
	else if (type == int_uhex_u && (flags & FL_HASH))
		prefix = "0X";
	else if (type == int_ubin_l && (flags & FL_HASH))
		prefix = "0b";
	else if (type == int_ubin_u && (flags & FL_HASH))
		prefix = "0B";
	else if (type == int_dec && n > 0 && (flags & FL_SPACE))
		prefix = " ";
	else if (type == int_dec && n > 0 && (flags & FL_PLUS))
		prefix = "+";
	ft_strprepend(prefix, a_s);
}

/*
**  highest priority is FL_MINUS that cancels FL_ZERO
**  then, if FL_ZERO, prepend 0s, then apply FL_HASH or FL_SPACE or FL_PLUS
**  else, if no FL_ZERO, first FL_HASH then prepend sign/spaces
**  if FL_SPACE or FL_PLUS, and no FL_MINUS, append ZEROS first
*/

static t_str	build_int_str(t_format info, intmax_t n, t_u8 bytes)
{
	char	*str;
	int		digits;
	t_str	result;

printf("val_to_str arg n is: %lx\n\t\t\t", n);
	str = val_to_str(info, n, &digits, bytes);
//printf("build_int_str str: %s\n", str); //\t\t\t
//printf("\t\t\tbuild_int_str digits: %d\n", digits);
	if (info.prec >= 0 && ft_strlen(str) < (t_u32)info.prec)
		ft_strpad_left_inplace(&str, '0', info.prec - ft_strlen(str)
					- (info.type == int_uoct && (info.flags & FL_HASH)));	
	else if (((info.flags & FL_ZERO) && info.width > digits))
		(info.flags & FL_MINUS) ?
			ft_strpad_right_inplace(&str, ' ', info.width - digits) :
			ft_strpad_left_inplace(&str, '0', info.width - digits);
//printf("\t\t\tbuild_int_str prec or zero with width: %s\n", str);
	flag_prepend(info.type, info.flags, n, &str);
//printf("\t\t\tbuild_int_str flag prepend: %s\n", str);
	if (!(info.flags & FL_ZERO) && info.width > digits)
		(info.flags & FL_MINUS) ?
			ft_strpad_right_inplace(&str, ' ', info.width - digits) :
			ft_strpad_left_inplace(&str, ' ', info.width - digits);
//printf("\t\t\tbuild_int_str str: %s\n", str);
	result.data = ft_strdup(str);
	free(str);
	result.len = info.width > digits ? info.width : digits;
//printf("\t\t\tbuild_int_str result: data = %s ; len = %lu\n", result.data, result.len);
	return (result);
}

t_str			handle_int_type(t_format info, va_list args)
{
	t_str	result;

	if (info.len_flag == fl_hh)
		result = build_int_str(info, (char)va_arg(args, int), BYTELEN_CHAR);
	else if (info.len_flag == fl_h)
		result = build_int_str(info, (short)va_arg(args, int), BYTELEN_SHORT);
	else if (info.len_flag == fl_l)
		result = build_int_str(info, (long)va_arg(args, long), BYTELEN_LONG);
	else if (info.len_flag == fl_ll)
		result = build_int_str(info, (long long)va_arg(args, long long),
								BYTELEN_LONGLONG);	
	else if (info.len_flag == fl_j)
		result = build_int_str(info, (intmax_t)va_arg(args, intmax_t),
								BYTELEN_IMAX);
	else if (info.len_flag == fl_z)
		result = build_int_str(info, (size_t)va_arg(args, size_t),
								BYTELEN_SIZET);
	else
		result = build_int_str(info, (int)va_arg(args, int), BYTELEN_INT);
	return (result);
}
