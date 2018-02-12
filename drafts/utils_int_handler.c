#include "ft_printf.h"

/*
** The precision field does not apply to numeric types, only floats and strings.
**
** "digits" is used to find out the number of symbols before width
** => Add two digits for a hash, remove one if the hash is an octal;
**      add one digit for a signed value with appropriate flag;
*/

static char		*val_to_str(t_types type, t_u8 flags, intmax_t n, int *digits)
{
	char	*str;

	str = NULL;
	if (type == int_dec)
		str = ft_itoa_base(n, DECIM);
	else if (type == int_udec)
		str = ft_uitoa_base(n, DECIM);
	else if (type == int_uoct)
		str = ft_uitoa_base(n, OCTAL);
	else if (type == int_uhex_l)
		str = ft_uitoa_base(n, HXLOW);
	else if (type == int_uhex_u)
		str = ft_uitoa_base(n, HXUPP);
	*digits = ft_strlen(str) - (type == int_uoct)
		+ 2 * ((flags & FL_HASH) && (type != int_dec))
		+ (type == int_dec && (flags & (FL_SPACE | FL_PLUS)));
	return (str);
}

static char		*flag_prepend(t_types type, t_u8 flags, intmax_t n, char **a_s)
{
	char	*tmp;

	tmp = "";
	if (type == int_uoct && (flags & FL_HASH))
		tmp = "0";
	else if (type == int_uhex_l && (flags & FL_HASH))
		tmp = "0x";
	else if (type == int_uhex_u && (flags & FL_HASH))
		tmp = "0X";
	else if (type == int_dec && n > 0 && (flags & FL_SPACE))
		tmp = " ";
	else if (type == int_dec && n > 0 && (flags & FL_PLUS))
		tmp = "+";
	tmp = ft_strprepend(tmp, a_s);
	return (tmp);
}

/*
**  highest priority is FL_MINUS that cancels FL_ZERO
**  then, if FL_ZERO, prepend 0s, then apply FL_HASH
**  else, if no FL_ZERO, first FL_HASH then prepend sign/spaces
*/

static t_str	build_int_str(t_format info, intmax_t n)
{
	char	*str;
	char	*tmp;
	int		digits;
	t_str	result;

////printf("\tbuild_int_str str: %s\n", str);
	str = val_to_str(info.type, info.flags, n, &digits);
////printf("\tbuild_int_str digits: %d\n", digits);
	if ((info.flags & FL_ZERO) && info.width > digits)
	{
		tmp = (info.flags & FL_MINUS) ?
			ft_strpad_right(str, ' ', info.width - digits) :
			ft_strpad_left(str, '0', info.width - digits);
		free(str);
		str = tmp;
	}
	tmp = flag_prepend(info.type, info.flags, n, &str);
////printf("\tbuild_int_str tmp: %s\n", tmp);
	if (!(info.flags & FL_ZERO) && info.width > digits)
		result.data = (info.flags & FL_MINUS) ?
			ft_strpad_right(tmp, ' ', info.width - digits) :
			ft_strpad_left(tmp, ' ', info.width - digits);
////printf("\tbuild_int_str str: %s\n", str);
	else
		result.data = ft_strdup(tmp);
	free(tmp);
	result.len = info.width > digits ? info.width : digits;
////printf("\tbuild_int_str result: data = %s ; len = %lu\n", result.data, result.len);
	return (result);
}

t_str			handle_int_type(t_format info, va_list args)
{
	t_str	result;

	if (info.len_flag == fl_l)
		result = build_int_str(info, (long)va_arg(args, long));
	else if (info.len_flag == fl_ll)
		result = build_int_str(info, (long long)va_arg(args, long long));	
	else if (info.len_flag == fl_j)
		result = build_int_str(info, (intmax_t)va_arg(args, intmax_t));
	else if (info.len_flag == fl_hh)
		result = build_int_str(info, (char)va_arg(args, int));
	else if (info.len_flag == fl_h)
		result = build_int_str(info, (short)va_arg(args, int));
	else if (info.len_flag == fl_z)
		result = build_int_str(info, (size_t)va_arg(args, size_t));
	else
		result = build_int_str(info, (int)va_arg(args, int));
	return (result);
}
