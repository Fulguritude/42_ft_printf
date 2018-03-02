/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lftoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:48:07 by fulguritu         #+#    #+#             */
/*   Updated: 2018/02/26 16:40:14 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


//TODO REMOVE
#include <stdio.h>


static char		*ft_lftoa_base_exp(char const *base, t_u8 minus,
									int exp_b2, t_u64 mantissa)
{
	char	*result;
	char	*tmp;

	tmp = ft_uitoa_base(mantissa, base);
printf("\t\ttmp mantissa : %s\n", tmp);
	result = ft_strinsert(&tmp, ".", 1);
printf("\t\tresult mantissa : %s\n", tmp);
//	free(tmp);
	tmp = ft_itoa_base(exp_b2, base);
printf("\t\ttmp exp_b2   : %s\n", tmp);
	if (tmp[0] != '-' && ft_strlen(tmp) < 2)
		ft_strprepend("+0", &tmp);
	else if (tmp[0] != '-')
		ft_strprepend("+", &tmp);		
	else if (tmp[0] == '-' && ft_strlen(tmp) < 3)
	{
		tmp[0] = base[0];
		ft_strprepend("-", &tmp);
	}
printf("\t\ttmp exp_b2 2 : %s\n", tmp);
	ft_strappend(&result, "\t");
printf("\t\tresult : %s\n", result);
	ft_strappend(&result, tmp);
printf("\t\tresult : %s\n", result);
	free(tmp);
	if (minus)
		ft_strprepend("-", &result);
printf("\t\tresult : %s\n", result);
	return (result);
}

static char		*ft_lftoa_base_hexfp(char style, t_u8 minus,
									int exp_b2, t_u64 mantissa)
{
//TODO
printf("TODO : %c, %hhd, %d, %lx\n", style, minus, exp_b2, mantissa);
	return (NULL);
}

static char		*ft_lftoa_base_point(char const *base, t_u8 minus,
									int exp_b2, t_u64 mantissa)
{
	char	*result;
	int		index;
	int		exp_b10;

	exp_b10 = exp_b2 * 30103 / 100000; //0.30103 ~= ln(2)/ln(10)
	result = ft_uimaxtoa_base(mantissa, base);
printf("\t\tresult mantissa : %s\n", result);
	if (exp_b10 > 0)
		ft_strpad_right_inplace(&result, base[0], exp_b10);
	else if (exp_b10 < 0 && (index = ft_strlen(result) - exp_b10) > 0)
		ft_strinsert(&result, ".", index);
	else if (exp_b10 < 0 && index <= 0)
	{
		ft_strpad_left_inplace(&result, base[0], -index);
		ft_strprepend(".", &result);
		ft_strpad_left_inplace(&result, base[0], 1);
	}
printf("\t\tresult after pads : %s\n", result);
	if (minus)
		ft_strprepend("-", &result);
	return (result);
}

char			*ft_lftoa_base(double lf, char const *base, char style)
{
	char	*result;
	t_u64	extract;
	t_u8	minus;
	int		exp_b2;
	t_u64	mantissa;

	extract = 0;
	ft_memcpy(&extract, &lf, 8);
	minus = extract >> 63;
	exp_b2 = ((extract << 1) >> 53) - 1023;
	mantissa = (((extract << 12) >> 12) | 0x10000000000000);
printf("\t\tmantissa : %lx\n", mantissa);
printf("\t\tmantissa : %ld\n", (long)mantissa);
	result = NULL;
	if (style == 'a' || style == 'A')
		result = ft_lftoa_base_hexfp(style, minus, exp_b2, mantissa);
	else if (ft_isalpha(style))
	{
		result = ft_lftoa_base_exp(base, minus, exp_b2, mantissa);
		result[ft_strfind(result, '\t')] = style;
	}
	else
		result = ft_lftoa_base_point(base, minus, exp_b2, mantissa);
	return (result);
}
