/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lftoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 19:14:43 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/28 19:15:01 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
** https://stackoverflow.com/questions/3215235/how-do-you-print-the-exact
** 											-value-of-a-floating-point-number
*/
#include "libft.h"

static char	**float_info_to_float_binstrs(int exp_b2, t_u64 mantissa)
{
	char	**result;
	char	*tmp;

	tmp = ft_uitoa_base(mantissa, BINAR);
	ft_strpad_left_inplace(&tmp, '0', 53 - ft_strlen(tmp));
//ft_printf("{red}{bold}binstrs\n\ttmp begin = %s\n\texp_b2 = %d\n", tmp, exp_b2);
	if (0 <= exp_b2 && exp_b2 < 52)
	{
		ft_strinsert(&tmp, ".", exp_b2 + 1);
		ft_strctrim_right_inplace(&tmp, '0');
		if (tmp[ft_strlen(tmp) - 1] == '.')
			ft_strappend(&tmp, "0");
	}
	else if (exp_b2 < 0)
	{
		ft_strpad_left_inplace(&tmp, '0', -exp_b2 - 1);
//ft_printf("BEFORE : %s\n", tmp);
		ft_strctrim_right_inplace(&tmp, '0');
//ft_printf("AFTER  : %s\n", tmp);
		ft_strprepend(ft_strequ(tmp, "") ? "0.0" : "0.", &tmp);
	}
	else
	{
		ft_strpad_right_inplace(&tmp, '0', exp_b2 - 52);
		ft_strappend(&tmp, ".0");
	}
	result = ft_split(tmp, ".");
//ft_printf("{red}{bold}binstrs\ntmp = %s\n\tfloor = %s\n\tfrac  = %s\n{eoc}", tmp, result[0], result[1]);
	ft_strdel(&tmp);
	return (result);
}

static char		*ft_lftoa_hexfp(int exp_b2, t_u64 mantissa) //, char style)
{
	char	*result;
	char	*tmp;

	tmp = ft_itoa(exp_b2);
	if (tmp[0] != '-' && ft_strlen(tmp) < 2)
		ft_strprepend("+", &tmp); //"+0", &tmp);
	else if (tmp[0] != '-')
		ft_strprepend("+", &tmp);
	ft_strpad_left_inplace(&tmp, 'p', 1);
//printf("\t\ttmp exp_b2   : %s\n", tmp);
	result = tmp;
	tmp = ft_uitoa_base(mantissa, HXLOW);	
ft_printf("\t\ttmp mantissa : %s; len = %d\n", tmp, ft_strlen(tmp));
	ft_strpad_left_inplace(&tmp, '0', 14 - ft_strlen(tmp));
	ft_strctrim_right_inplace(&tmp, '0');
	if (ft_strequ(tmp, "") || ft_strequ(tmp, "-"))
		tmp[(tmp[0] == '-')] = '0';
	ft_strinsert(&tmp, ".", (tmp[0] == '-') + 1);
	if (tmp[ft_strlen(tmp) - 1] == '.')
		ft_strappend(&tmp, "0");
	ft_strprepend(tmp, &result);
	ft_strinsert(&result, "0x", result[0] == '-');
	free(tmp);
ft_printf("\t\tresult : %s\n", result);
	return (result);
}

static char	*ft_lftoa_fp(char **bin_strs) //, int exp_b2)
{
	char	*result;
	char	*tmp;
	t_u32	frac_digits;
	t_vlq	vlq;
	t_vlq	pow10;

//ft_printf("lftoa_fp\n");
	vlq = ft_atovlq(bin_strs[0], BINAR);
//tmp = ft_vlq_abstractval_as_hex(vlq);
//ft_printf("\t{yellow}atovlq\n\t\tbin_strs[0] = %s;\n\t vlq = %s{eoc}\n", bin_strs[0], tmp);
//free(tmp);
	tmp = ft_vlqtoa_base(vlq, DECIM);
//ft_printf("\tvlqtoa_base\n\t\ttmp = %s\n", tmp);
	result = ft_strpad_right(tmp, '.', 1);
//ft_printf("\tstrpad_right\n");
	ft_strdel(&tmp);
	ft_vlqdel(&vlq);
	if (ft_strequ(bin_strs[1], "0"))
	{
		ft_strappend(&result, "0");
//ft_printf("\tIF ft_strappend\n");
		return (result);
	}
	vlq = ft_atovlq(bin_strs[1], BINAR);
//tmp = ft_vlqhex(vlq);
//ft_printf("\tatovlq 2\n\t\tbin_strs[1] = %s; vlq = %s\n", bin_strs[1], tmp);
//free(tmp);
	frac_digits = ft_strlen(bin_strs[1]);
//ft_printf("\t\texp_b2 = %d; frac_digits = %d\n", exp_b2, frac_digits);
	pow10 = ft_vlq_getpow10(frac_digits);
//tmp = ft_vlq_abstractval_as_hex(pow10);
//ft_printf("\tvlq_getpow10\n\t\tfrac_digits = %d\n\t\tpow10 = %s\n", frac_digits, tmp);
//ft_strdel(&tmp);
	ft_vlq_mul_acc(&vlq, pow10);
//tmp = ft_vlq_abstractval_as_hex(vlq);
//ft_printf("\tvlq_mul_acc\n\t\tvlq = %s\n", tmp);
//ft_strdel(&tmp);
	ft_vlq_bsr_acc(&vlq, frac_digits);
//tmp = ft_vlq_abstractval_as_hex(vlq);
//ft_printf("\tvlq_bsr_acc\n\t\tvlq = %s\n", tmp);
//ft_strdel(&tmp);
	tmp = ft_vlqtoa_base(vlq, DECIM);
//ft_printf("\tvlqtoa_base\n");
	ft_strpad_left_inplace(&tmp, '0', frac_digits - ft_strlen(tmp));
	ft_strmerge(&result, &tmp);
//ft_printf("\tstrmerge\n");
	ft_vlqdel(&pow10);
	ft_vlqdel(&vlq);
	return (result);
}
/*
** a*2^b = c*10^d with 1 <= a < 2 and 1 <= c < 10
** => d = floor(log10(a*2^b)) = floor(log10(a) + b * log10(2)); 
*/
/*
	exp_b10 = LN2_DIV_LN10 * ABS(exp_b2) + ft_logn(ABS(scimant_b2), 10);
	exp_b10 -= exp_b10 == 1.0 * ft_floor(exp_b10) ? 1 : 0;
	exp_b10 = (exp_b10 + (exp_b2 < 0)) * (-1 + 2 * (exp_b2 >= 0));
ft_printf("{cyan}exp_b2 = %d; exp_b10 = %d; scimant_b2 = %lf, ft_logn(scimant_b2, 10) = %.20lf, pure exp_b10 = %.20lf{eoc}\n", exp_b2, exp_b10, scimant_b2, ft_logn(scimant_b2, 10), LN2_DIV_LN10 * exp_b2 + ft_logn(scimant_b2, 10));
*/
static char	*ft_lftoa_exp(char **bin_strs) //, int exp_b2, double scimant_b2)
{
	char	*result;
	char	*tmp;
	int		neg;
	int		exp_b10;
	int		i;
#if 0
	while (0. < scimant_b2 && scimant_b2 < 1.)
	{
		scimant_b2 *= 2.;
		++exp_b2;
	}
	d = LN2_DIV_LN10 * ABS(exp_b2) + ft_logn(ABS(scimant_b2), 10);
	exp_b10 = d == ft_floor(d) ? d - 1 : d;
	exp_b10 = (ft_floor(exp_b10) + (exp_b2 < 0)) * (-1 + 2 * (exp_b2 >= 0));
//ft_printf("{cyan}exp_b2 = %d; exp_b10 = %d; scimant_b2 = %lf, ft_logn(scimant_b2, 10) = %.20lf, pure exp_b10 = %.20lf{eoc}\n", exp_b2, exp_b10, scimant_b2, ft_logn(scimant_b2, 10), LN2_DIV_LN10 * exp_b2 + ft_logn(scimant_b2, 10));

#endif

	tmp = ft_lftoa_fp(bin_strs); //, exp_b2); //change with comment when functional
	if ((neg = (tmp[0] == '-')))
		ft_strctrim_left_inplace(&result, '-');
	if (ft_strequ(tmp, "0.0"))
	{
		ft_strappend(&tmp, "e+00");
		return (tmp);
	}
	i = 0;
	if ((exp_b10 = ft_strfind(tmp, '.')) == 1)
		while (tmp[2 + neg + i] == '0')
			++i;
ft_printf("{cyan}exp_b10 = %d{eoc}\n", exp_b10);
	exp_b10 = exp_b10 == 1 && tmp[2 + neg + i] ? -i - (tmp[0] == '0') : exp_b10 - 1;
	result = ft_itoa(exp_b10);
	if (ft_strlen(result) < 3 && result[0] == '-')
		ft_strinsert(&result, "0", 1);
	else if (result[0] != '-')
		ft_strprepend(ft_strlen(result) == 1 ? "+0" : "+", &result);
	ft_strpad_left_inplace(&result, 'e', 1);
	ft_strmerge(&tmp, &result);
	ft_strreplace_inplace(&result, ".", "");
	ft_strctrim_left_inplace(&result, '0');
//	if (result[0] == 'e')
//		ft_strprepend("00", &result);
	ft_strinsert(&result, ".", 1);
	if (neg)
		ft_strprepend("-", &result); 
	return (result);
}

char	*ft_lftoa(double lf, char style)
{
	char	*result;
	t_u64	extract;
	int		exp_b2;
	t_u64	mantissa;
	char	**bin_strs;

ft_printf("lftoa\n");
	extract = *(t_u64*)(&lf);
	if (lf != lf)
		return (ft_strdup(MSB(extract) ? "-nan" : "nan"));
	exp_b2 = ((extract << 1) >> 53) - 1023;
	mantissa = ((extract << 12) >> 12);
	if (exp_b2 == 1024)
		return (ft_strdup(MSB(extract) ? "-inf" : "inf"));
	if (exp_b2 != -1023)
		mantissa |= 0x10000000000000;
	else
		exp_b2 = lf == 0. ? 0 : exp_b2 + 1;
	bin_strs = float_info_to_float_binstrs(exp_b2, mantissa);
	extract = (extract & (_MSB_ | 0xFFFFFFFFFFFFF)) | 0x3FF0000000000000;
	if (style == 'p')
		result = ft_lftoa_hexfp(exp_b2, mantissa); //, style);
	else if (style == 'e')
		result = ft_lftoa_exp(bin_strs); //, exp_b2, *(double*)(&extract));
	else
		result = ft_lftoa_fp(bin_strs); //, exp_b2);
	if (extract >> 63)
		ft_strprepend("-", &result);
	ft_strlsdel(&bin_strs);
ft_printf("lftoa result: %s\n", result);
	return (result);
}
