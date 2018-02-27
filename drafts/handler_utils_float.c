static char	*ft_ftoa_varfloat(t_varfloat varf, char const *base,
								t_u8 style, t_u8 is_dbl)
{
	
}

static char	*handle_g_type(t_format info, varfloat_t varf, t_u8 is_dbl)
{
	char	*result;
	char	*tmp;
	t_u32	i;

	if (exp < -4 || info.prec <= exp))
		tmp = ft_ftoa_varfloat(f, DECIM, '\0', is_dbl);
	else
		tmp = ft_ftoa_varfloat(f, DECIM,
									info.type_char == 'g' ? 'e' : 'E', is_dbl);
	i = 0;
	while ((ft_isdigit(tmp[i]) || tmp[i] == '-' || tmp[i] == '.') &&
			i < info.prec + (tmp[0] == '-') + 1)
		++i;
	result = ft_strsub(tmp, 0, i);
	while (tmp[i - 1] == '0')
		if (tmp[--i] == '.')
		{
			--i;
			break ;
		}
	result[i] = '\0';
	info.type_char == 'g' ? ft_strappend(&result, tmp + ft_strchr(tmp, 'e')) :
							ft_strappend(&result, tmp + ft_strchr(tmp, 'E'));
//TODO WIDTH ??
	free(tmp);
	return (result);
}

t_str		handle_float_type(t_format info, va_list args)
{
	t_varfloat	varf;
	t_u8		is_dbl;
	char		*res;
	int			exp;

	is_dbl = (info.len_flag == fl_l || info.len_flag == fl_ll) ? 1 : 0;
	varf.d = 0;
	if (is_dbl)
		varf.d = va_arg(args, double);
	else
		varf.f = va_arg(args, float);
	exp = (int)(is_dbl ? ((varf.d << 1) >> 52) - 1023 :
						((varf.d << 33) >> 56) - 127);
	if (info.type_char == 'e')
		res = ft_ftoa_varfloat(f, DECIM, 'e', is_dbl);
	else if (info.type_char == 'E')
		res = ft_ftoa_varfloat(f, DECIM, 'E', is_dbl);
	else if (info.type_char == 'a')
		res = ft_strprepend("0x", ft_ftoa_varfloat(f, HXLOW, 'p', is_dbl));
	else if (info.type_char == 'A')
		res = ft_strprepend("0X", ft_ftoa_varfloat(f, HXUPP, 'P', is_dbl));
	else if (info.type_char == 'f' || info.type_char == 'F')
	{
		res = ft_ftoa_varfloat(f, DECIM, '\0', is_dbl);
		


	}
	else if (info.type_char == 'g' || info.type_char == 'G')
		res = handle_g_type(info, f, is_dbl);
	else
		res = ft_strdup("float_handler_error");
	return (str_to_t_str(res));
}

/*

			For a, A, e, E, f, F, g, and G conversions, the result will  always  contain  a  decimal
              point, even if no digits follow it (normally, a decimal point appears in the results of those
              conversions only if a digit follows).  For g  and  G  conversions,  trailing  zeros  are  not
              removed  from  the  result  as they would otherwise be.  For other conversions, the result is
              undefined.



 Precision
       An  optional precision, in the form of a period ('.')  followed by an optional decimal digit string.
       Instead of a decimal digit string one may write "*" or "*m$" (for some decimal integer m) to specify
       that  the precision is given in the next argument, or in the m-th argument, respectively, which must
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
       next argument, or in the m-th argument, respectively, which must be of type int.
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

              (SUSv2  does not know about F and says that character string representations for infinity and
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
			if ((info.type == 'g' || info.type == 'G') && info.prec == 0)
				info.prec = 1;

       a, A   (C99; not in SUSv2, but added in SUSv3) For a conversion, the double argument is converted to
              hexadecimal notation (using the letters abcdef) in the style [-]0xh.hhhhp±; for A  conversion
              the  prefix 0X, the letters ABCDEF, and the exponent separator P is used.  There is one hexa‐
              decimal digit before the decimal point, and the number of digits after it  is  equal  to  the
              precision.   The  default  precision  suffices for an exact representation of the value if an
              exact representation in base 2 exists and otherwise is sufficiently large to distinguish val‐
              ues of type double.  The digit before the decimal point is unspecified for nonnormalized num‐
              bers, and nonzero but otherwise unspecified for normalized numbers.


%m ?

*/
