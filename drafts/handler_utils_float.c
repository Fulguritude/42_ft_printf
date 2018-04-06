#include "ft_printf.h"


//TODO REMOVE
#include <stdio.h>
#if 0
static void round_up(char **a_res, char const *tmp, int dig_ind, char exp_c)
{
	char	maxdigit;
	t_u8	no_rounding;
	char	*base;

	base = exp_c == 'p' ? HXLOW : DECIM;
	maxdigit = base[ft_strlen(base) - 1];
	no_rounding = (maxdigit != '9') ? (ft_in_base(tmp[dig_ind], OCTAL) >= 0) :
								('0' <= tmp[dig_ind] && tmp[dig_ind] <= '4'); //TODO verify printf rounding rules for 5 in DECIM and 8 HXUPP; or maybe it's just that they find digits 1 by 1 for exp by handing precision to lftoa ?
ft_printf("\t\t{magenta}unrounded %s\n", *a_res);
ft_printf("\t\t{magenta}      tmp %s ; dig_ind %d{eoc}\n", tmp, dig_ind);
	if (!no_rounding)
	{
		while ((tmp[--dig_ind] == maxdigit || tmp[dig_ind] == '.'))// && (tmp[0] == maxdigit !tmp[dig_ind] != '9')
		{
ft_printf("dig_ind = %d; tmp[dig_ind] = %c\n", dig_ind, tmp[dig_ind]);
			if (tmp[dig_ind] == '.')
				continue ;
			if (dig_ind == 0)
			{
				ft_strprepend("0", a_res);
				++dig_ind;
			}
			(*a_res)[dig_ind] = '0'; //  - ((*a_res)[dig_int] == '.')
		}
		(*a_res)[dig_ind] = base[ft_in_base((*a_res)[dig_ind], base) + 1];
	}
//ft_printf("\t\t{magenta}  rounded %s\n", *a_res);
}

static void	apply_float_prec(t_format info, char **a_flstr, char exp_c)
{
	char	*result;
	char	*tmp;
	int		newlen;
	int		trulen;

	tmp = ft_strcdup(*a_flstr, exp_c);
	if ((newlen = ft_in_base('.', tmp)) == -1)
		ft_putendl_fd("No dot found in flstr in apply_float_prec", 2);
	newlen += info.prec + 1; // info.prec + (info.prec != 0);
	result = ft_strnew(newlen);
	ft_strncpy(result, tmp, newlen);
ft_printf("before rounding : %s, tmp = %s\n", result, tmp);
	if ((trulen = ft_strlen(result)) < newlen)
		ft_strpad_right_inplace(&result, '0', newlen - trulen);
	else if (!ft_strequ(result, tmp))
		round_up(&result, tmp, newlen, exp_c);
ft_printf("after rounding : %s, tmp = %s\n", result, tmp);
	if (exp_c)
		ft_strappend(&result, ft_strchr(*a_flstr, exp_c));
	ft_strdel(&tmp);
	ft_strdel(a_flstr);
	*a_flstr = result;
	if (info.prec == 0)
		ft_strreplace_inplace(a_flstr, ".", "");
}
#endif
/*
**    0	   6	index for res
** 0       9    index for tmp
** 99999.999	ft_strlen(tmp) 		= 9
**    99.999	reslen 				= 6
**   9 	    	'start' digit index	= 2 = 9 - 6 - 1, then
**    09.999	'++i, start + i'
*/
static char	*round_up(char const *tmp, int reslen, char exp_c, int *status)
{
	char	*result;
	char	maxdigit;
	char	*base;
	int		start;
	int		i;

	base = exp_c == 'p' ? HXLOW : DECIM;
	maxdigit = base[ft_strlen(base) - 1];
	start = ft_strlen(tmp) - reslen - 1;
ft_printf("{cyan}{bold}unrounded: %s{eoc}\n", tmp + start);
	if ((maxdigit == '9') ? (ft_strfind("56789", tmp[start]) >= 0) :
							(ft_strfind("89abcdef", tmp[start]) >= 0))
	{
		result = ft_strnew(reslen + 1);
		result[0] = base[(ft_in_base(tmp[++start], base) + 1) % ft_strlen(base)];
		i = 0;
		while (result[i] == '0')
		{
			++i;
			if (tmp[start + i] == '.')
			{
				result[i] = '.';
				++i;
			}
			result[i] = base[(ft_in_base(tmp[start + i], base) + 1) % ft_strlen(base)];
			if (i + 1 == reslen && result[i] == '0')
				*status = 1;
			if (i == reslen && result[i] == '0')
				result[++i] = '1';
		}
		while (++i <= reslen)
			result[i] = tmp[start + i];
		ft_strrev_inplace(&result);
	}
	else
	{
		result = ft_strrev(tmp);
	}
ft_printf("{red}{bold}  rounded: %s{eoc}\n", result);
	result[reslen + (*status && !exp_c)] = '\0';
ft_printf("{red}{bold}  rounded: %s{eoc}\n", result);
	return (result);
}

/*
** - tmp : absolute representation of the string with convention to always have
**			a single zero before
** - dotpos + cur_frac_digits == ft_strlen(tmp)
** - dotpos + info.prec + 1 = length of the result string
**
*/
static void	apply_float_prec(t_format info, char **a_flstr, char exp_c)
{
	char	*result;
	char	*tmp;
	int		dotpos;
	int		status;

	tmp = ft_strcdup(*a_flstr, exp_c);
	dotpos = ft_strfind(tmp, '.');	
	if ((status = dotpos + info.prec + 1 - ft_strlen(tmp)) > 0)
	{
		result = ft_strpad_right(tmp, '0', status);
		status = 0;
	}
	else if (status < 0)
	{
		status = 0;
		ft_strrev_inplace(&tmp); //tmp is reversed for ease of iteration
		result = round_up(tmp, dotpos + info.prec + 1, exp_c, &status); //status should return 1 if an extra digit has been added
		ft_strdel(&tmp);
		if (status && exp_c && result + 1 && result + 2)
		{
			ft_swap(result + 1, result + 2, 1);
			tmp = ft_itoa(ft_atoi(ft_strchr(*a_flstr, exp_c) + 2) + 1); //eventually replace by one-line asprintf ?
			ft_strinsert(&tmp, ft_strlen(tmp) - (tmp[0] == '-') < 2 ? "0" : "", tmp[0] == '-'); 
			ft_strprepend(ft_strfind((*a_flstr) + 1, '-') >= 0 ? "e-" : "e+", &tmp);
		}
		else if (info.prec == 0)
			result[dotpos + status] = '\0';
	}
	else
		result = ft_strdup(tmp);
	if (exp_c && status)
		ft_strappend(&result, tmp);
	else if (exp_c)
		ft_strappend(&result, ft_strchr(*a_flstr, exp_c));
	ft_strdel(&tmp);
	ft_strdel(a_flstr);
	*a_flstr = result;
	if (info.prec == 0)
		ft_strreplace_inplace(a_flstr, ".", "");
}

static void apply_float_width(t_format info, char **a_flstr)
{
	t_u32	start;
	int		size;

	if ((info.flags & (FL_SPACE | FL_PLUS)) && (*a_flstr)[0] != '-')
		ft_strprepend(info.flags & FL_SPACE ? " " : "+", a_flstr);
	size = ft_strlen(*a_flstr);
	start = ft_in_base('x', (*a_flstr)) + 1;
	if (info.width > size && (info.flags & FL_MINUS))
		ft_strpad_right_inplace(a_flstr, ' ', info.width - size);
	else if (info.width > size && !(info.flags & (FL_MINUS | FL_ZERO)))
		ft_strpad_left_inplace(a_flstr, ' ', info.width - size);
	else if (info.width > size)
		ft_strpad_insert_inplace(a_flstr, '0', start, info.width - size);
}
#if 0
static char *handle_f_type(t_format info, double lf)
{
	char	*result;

	result = ft_lftoa(lf, info.type_char);
	if (!ft_strequ(result, "inf") && !ft_strequ(result, "-inf") &&
		!ft_strequ(result, "nan") && !ft_strequ(result, "-nan"))
		apply_float_prec(info, &result, '\0');
	apply_float_width(info, &result);
	return (result);
}
#endif

static char	*handle_aef_type(t_format info, double lf)
{
	char	*result;
	char	exp_c;

	exp_c = info.type_char == 'e' || info.type_char == 'E' ? 'e' : 'p';
	exp_c = info.type_char == 'f' || info.type_char == 'F' ? '\0' : exp_c;
	result = ft_lftoa(lf, exp_c);
	if (!ft_strequ(result, "inf") && !ft_strequ(result, "-inf") &&
		!ft_strequ(result, "nan") && !ft_strequ(result, "-nan") &&
		info.prec != -1)
		apply_float_prec(info, &result, exp_c);
	apply_float_width(info, &result);
	ft_strreplace_inplace(&result, ".0p", "p");
	return (result);
}

static char	*handle_g_type(t_format info, double lf)
{
	char	*result;
	double	mant_b2;
	int		exp_b2;
	int		exp_b10;
	int		boolexp;

	exp_b2 = (((*(t_u64*)(&lf)) << 1) >> 53) - 1023;
	mant_b2 = ((((*(t_u64*)(&lf)) << 12) >> 12) - 1023) | 
			((exp_b2 != -1023) * 0x10000000000000);
	mant_b2 = 1.0 * mant_b2 / ft_ipowi(2.0, ft_digits_base(mant_b2, 2) - 1);
	exp_b10 = ft_floor(LN2_DIV_LN10 * ABS(exp_b2) + ft_logn(mant_b2, 10));
	exp_b10 = (exp_b10 + (exp_b2 < 0)) * (-1 + 2 * (exp_b2 >= 0));
	boolexp = (exp_b10 < -4 || (info.prec != -1 && info.prec <= exp_b10)) && lf != 0;
	result = ft_lftoa(lf, boolexp ? 'e' : '\0');
	info.prec = info.prec - 1 - ((!boolexp) * exp_b10);
	if (!ft_strequ(result, "inf") && !ft_strequ(result, "-inf") &&
		!ft_strequ(result, "nan") && !ft_strequ(result, "-nan"))
		apply_float_prec(info, &result, boolexp ? 'e' : '\0');
	if (!(info.flags & FL_HASH))
		ft_strctrim_right_inplace(&result, '0');
	apply_float_width(info, &result);
	if (result[ft_strlen(result) - 1] == '.')
		result[ft_strlen(result) - 1] = '\0';
	return (result);
}

t_str		*handle_float_type(t_format info, va_list args)
{
	double		lf;
	char		*tmp;
	int			exp;
	t_str		*result;
	t_u64		extract;

	lf = 0;
//if (info.len_flag == fl_l || info.len_flad == fl_ll)
	lf = va_arg(args, double);
	extract = 0;
	ft_memcpy(&extract, &lf, 8);;
printf("\tlf u64: %#lx\n", extract);
printf("\tlf hex: %la\n", lf);
printf("\tlf exp: %le\n", lf);
printf("\tlf dot: %.5lf\n", lf);
	exp = (int)((((extract) << 1) >> 53) - 1023);
printf("\texp: %d\n", exp);
	t_u8	minus;
	t_u64	mantissa;

	minus = extract >> 63;
	exp = ((extract << 1) >> 53) - 1023;
	mantissa = ((extract << 12) >> 12) | 0x10000000000000;
printf("\tminus = %hhd\n\texp2 = %d\n\tmantissa = %lx\n", minus, exp, mantissa);

	char arr[8];
	ft_memcpy(arr, &lf, 8);
printf("\n\tarr = %#lx\n", *((unsigned long *)arr));
	char * str = ft_memhex(arr, 8);
printf("\tarr = %s ; style = %c\n", str, info.type_char);
ft_strdel(&str);

	if (ft_strfind("aAeEfF", info.type_char) >= 0)
		tmp = handle_aef_type(info, lf);
	else if (info.type_char == 'g' || info.type_char == 'G')
		tmp = handle_g_type(info, lf);
	else
		tmp = ft_strdup("(float_handler_error)");
	if (ft_strfind("AFEG", info.type_char) >= 0)
		ft_str_toupper(tmp);
	result = str_to_t_str(tmp);
	free(tmp);
	return (result);
}


/*
** Our double: 
** in hex_fp : -0x1.123456789abcdp+1010
** in memory :	cdab8967452311ff (little endian)
** in hex:		ff1123456789abcd
** in binary : 1111111100010001001000110100010101100111100010011010101111001101
**	where:
** 		sign =	1
** 		exp =	11111110001 (1010 + 1023 is 11111110001 in binary; 11 b)
**			 	7F1 (hex)
** 		mantissa = 0001001000110100010101100111100010011010101111001101 (52 b)
**				   123456789ABCD
*/




/*

			For a, A, e, E, f, F, g, and G conversions, the result will  always  contain  a  decimal
              point, even if no digits follow it (normally, a decimal point appears in the results of those
              conversions only if a digit follows).  For g  and  G  conversions,  trailing  zeros  are  not
              removed  from  the  result  as they would otherwise be.  For other conversions, the result is
              undefined.



 Precision
       An  optional precision, in the form of a period ('.')  followed by an optional decimal digit string.
       Instead of a decimal digit string one may write "*" or "*m$" (for some decimal integer m) to specify
       that  the precision is given in the next argument, or in the m-th argument, resultpectively, which must
       be of type int.  
		-If the precision is given as just '.', the precision is taken to be zero. (CHECK)
		-A  negative  precision  is taken as if the precision were omitted. This gives the minimum number of digits
       to appear for d, i, o, u, x, and X conversions, (CHECK)
		- the number of digits to appear after the radix character  for  a,  A,  e, E, f, and F conversions, the 
		maximum number of significant digits for g and G conversions, 
		- the maximum number of characters to be printed from a string for  s  and  S  conversions. (CHECK)




Field width
       An optional decimal digit string (with nonzero first digit) specifying a minimum  field  width.   If
       the  converted value has fewer characters than the field width, it will be padded with spaces on the
       left (or right, if the left-adjustment flag has been given).  Instead of a decimal digit string  one
       may  write "*" or "*m$" (for some decimal integer m) to specify that the field width is given in the
       next argument, or in the m-th argument, resultpectively, which must be of type int.
		- A  negative  field width  is  taken as a '-' flag followed by a positive field width. 
		- In no case does a nonexistent or small field width cause truncation of a field; 
		- if the result of a conversion is wider than the field width, the field is expanded to contain the 
		conversion result.



       e, E   The double argument is rounded and converted in the style [-]d.ddde±dd  where  there  is  one
              digit  before  the  decimal-point character and the number of digits after it is equal to the
              precision; if the precision is missing, it is taken as 6; if the precision is zero, no  deci‐
              mal-point  character appears.  An E conversion uses the letter E (rather than e) to introduce
              the exponent.  The exponent always contains at least two digits; if the value  is  zero,  the
              exponent is 00.

       f, F   The  double  argument  is  rounded and converted to decimal notation in the style [-]ddd.ddd,
              where the number of digits after the decimal-point character is equal to the precision speci‐
              fication.   If  the  precision  is  missing, it is taken as 6; if the precision is explicitly
              zero, no decimal-point character appears.  If a decimal point appears,  at  least  one  digit
              appears before it.

              (SUSv2  does not know about F and says that character string represultentations for infinity and
              NaN may be made available.  SUSv3 adds a specification for F.   The  C99  standard  specifies
              "[-]inf" or "[-]infinity" for infinity, and a string starting with "nan" for NaN, in the case
              of f conversion, and "[-]INF" or "[-]INFINITY" or "NAN*" in the case of F conversion.)

       g, G   The double argument is converted in style f or e (or F or E for G conversions).   The  preci‐
              sion  specifies  the number of significant digits.  If the precision is missing, 6 digits are
              given; if the precision is zero, it is treated as 1.  Style e is used if  the  exponent  from
              its conversion is less than -4 or greater than or equal to the precision.  Trailing zeros are
              removed from the fractional part of the result; a decimal point appears only if  it  is  fol‐
              lowed by at least one digit.


			if ((info.type_char == 'g' || info.type_char == 'G') &&
				(info.width >= info.prec || exp < -4))
				style = 'e';

       a, A   (C99; not in SUSv2, but added in SUSv3) For a conversion, the double argument is converted to
              hexadecimal notation (using the letters abcdef) in the style [-]0xh.hhhhp±; for A  conversion
              the  prefix 0X, the letters ABCDEF, and the exponent separator P is used.  There is one hexa‐
              decimal digit before the decimal point, and the number of digits after it  is  equal  to  the
              precision.   The  default  precision  suffices for an exact representation of the value if an
              exact representation in base 2 exists and otherwise is sufficiently large to distinguish val‐
              ues of type double.  The digit before the decimal point is unspecified for nonnormalized num‐
              bers, and nonzero but otherwise unspecified for normalized numbers.
		=> hexadecimal floating-point constant http://www.exploringbinary.com/hexadecimal-floating-point-constants/
			=> TODO code this hex_fp_cst format in lftoa
		=> digits after p represent a power of 2 written in base 10, neither are base sixteen. I suppose 
				they picked the letter p because of "power".  

%m ?

*/
