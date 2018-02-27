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
**		filled with ones rather than zeros in a few cases, and the called 
**		variable should be of the right "signed" or "unsigned" type when it is
**		called.
*/

char			*ft_ivartoa_base(intmax_t n, char const *base, t_u8 bytes,
									t_u8 has_sign)
{
	t_varint	varint;
	char		*res;

	varint.sl = 0;
	if (bytes == 1)
	{
		varint.sc = (char)n;
		res = has_sign ? ft_imaxtoa_base(varint.sc, base) :
						ft_uimaxtoa_base(varint.uc, base);
	}
	else if (bytes == 2)
	{
		varint.ss = (short)n;
		res = has_sign ? ft_imaxtoa_base(varint.ss, base) :
						ft_uimaxtoa_base(varint.us, base);
	}
	else if (bytes == 4)
	{
		varint.si = (int)n;
		res = has_sign ? ft_imaxtoa_base(varint.si, base) :
						ft_uimaxtoa_base(varint.ui, base);
	}
	else if (bytes == 8)
	{
		varint.sl = (long)n;
		res = has_sign ? ft_imaxtoa_base(varint.sl, base) :
						ft_uimaxtoa_base(varint.ul, base);
	}
	else
		return (NULL);
//printf("varint.l : %ld ou %lx ; imaxtoa %s\n\t\t\t", varint.sl, varint.sl, res);
	return (res);
}

static char		*val_to_str(t_format info, intmax_t n, int *digits, t_u8 bytes)
{
	char	*str;
	t_u32	prec;

	str = NULL;
	prec = info.prec <= 0 ? 0 :
		(t_u32)info.prec - (info.type == int_uoct && (info.flags & FL_HASH));
	if (n == 0)
		str = ft_strnew(0);
	else if (info.type == int_dec)
		str = ft_ivartoa_base(n, DECIM, bytes, 1);
	else if (info.type == int_udec)
		str = ft_ivartoa_base(n, DECIM, bytes, 0);
	else if (info.type == int_uoct)
		str = ft_ivartoa_base(n, OCTAL, bytes, 0);
	else if (info.type == int_uhex_l)
		str = ft_ivartoa_base(n, HXLOW, bytes, 0);
	else if (info.type == int_uhex_u)
		str = ft_ivartoa_base(n, HXUPP, bytes, 0);
	else if (info.type == int_ubin_l || info.type == int_ubin_u)
		str = ft_ivartoa_base(n, BINAR, bytes, 0);
	*digits = MAX(ft_strlen(str), prec + (str[0] == '-'))
		+ 2 * ((info.flags & FL_HASH) && n != 0 &&
			(int_uhex_l <= info.type) && (info.type <= int_ubin_u))
		+ (info.type == int_uoct && (info.flags & FL_HASH))
		+ (info.type == int_dec && (info.flags & (FL_SPACE | FL_PLUS)) && n >= 0);
	return (str);
}

static void		flag_prepend(t_types type, t_u8 flags, intmax_t n, char **a_s)
{
	char	*prefix;

	prefix = "";
	if (type == int_uoct && (flags & FL_HASH))
		prefix = "0";
	else if (type == int_uhex_l && (flags & FL_HASH) && n != 0)
		prefix = "0x";
	else if (type == int_uhex_u && (flags & FL_HASH) && n != 0)
		prefix = "0X";
	else if (type == int_ubin_l && (flags & FL_HASH) && n != 0)
		prefix = "0b";
	else if (type == int_ubin_u && (flags & FL_HASH) && n != 0)
		prefix = "0B";
	else if (type == int_dec && (flags & FL_SPACE) && n >= 0)
		prefix = " ";
	else if (type == int_dec && (flags & FL_PLUS) && n >= 0)
		prefix = "+";
	ft_strprepend(prefix, a_s);
}

static void		handle_int_prec_n_flzero(char **a_str, t_format info,
										int digits)
{
	int		added_prec;
	char	*tmp;

	tmp = NULL;
	if (0 <= info.prec && (t_u32)info.prec > ft_strlen(*a_str) - (**a_str == '-'))
	{
		added_prec = info.prec - ft_strlen(*a_str) + ((*a_str)[0] == '-')
			- (info.type == int_uoct && (info.flags & FL_HASH));
		tmp = ft_strcnew(added_prec, '0');
		ft_strinsert(a_str, tmp, ((*a_str)[0] == '-'));
		free(tmp);
	}
	else if (((info.flags & FL_ZERO) && info.width > digits))
	{
		if (info.flags & FL_MINUS)
			ft_strpad_right_inplace(a_str, ' ', info.width - digits);
		else if ((*a_str)[0] != '-')
			ft_strpad_left_inplace(a_str, '0', info.width - digits);
		else
		{
			tmp = ft_strcnew(info.width - digits, '0');
			ft_strinsert(a_str, tmp, 1);
			free(tmp);
		}
	}
}

/*
**	Concerning width:
**  - highest priority is FL_MINUS that cancels FL_ZERO
**  - then, if FL_ZERO, prepend 0s, then apply FL_HASH or FL_SPACE or FL_PLUS
**  - else, if no FL_ZERO, first FL_HASH then prepend sign/spaces
**  - if FL_SPACE or FL_PLUS, and no FL_MINUS, append ZEROS first
*/

static t_str	build_int_str(t_format info, intmax_t n, t_u8 bytes)
{
	char	*str;
	int		digits;
	t_str	result;

//printf("val_to_str arg n is: %lx\n\t\t\t", n);
	str = val_to_str(info, n, &digits, bytes);
printf("build_int_str str: %s\n", str); //\t\t\t
//printf("\t\t\tbuild_int_str digits: %d\n", digits);
	handle_int_prec_n_flzero(&str, info, digits);
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
//printf("\t\t\tinfo.width : %d; digits : %d\n", info.width, digits);
	result.len = MAX(info.width, digits);
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
