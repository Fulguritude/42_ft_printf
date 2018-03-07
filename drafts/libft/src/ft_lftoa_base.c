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


/*
** Special rules if exponent is minimal (0x00), called denormalized numbers.
** The implicit leading 1 bit not added.
** https://blog.penjee.com/binary-numbers-floating-point-conversion/
*/

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
printf("TODO : %c, %hhd, %d, %lx\n", style, minus, exp_b2, mantissa);

	return (NULL);
}

static char		*ft_lftoa_base_point(char const *base, t_u8 minus,
									int exp_b2, t_u64 mantissa)
{
	char	*result;
	char	*bin_mant;
	t_u64	floor;
	char	*fractional;

	bin_mant = ft_uimaxtoa_base(mantissa, "01");
	if (exp_b2 < 0)
	{
		floor = 0;
		fractional = ft_strpad_left(bin_mant, '0', -exp_b2 - 1);
	}
	else if (0 <= exp_b2 && exp_b2 < 53)
	{
		floor = mantissa >> (52 - exp_b2);
		ft_strntrim_left_inplace(&bin_mant, exp_b2 + 1);
		fractional = bin_mant;	
	}
	else
	{
		ft_putendl_fd("LFTOA not implemented", 2);
		floor = 0;
		fractional = bin_mant;
		//ft_strpad_right_inplace(&result, '0', exp_b2 - 52); //won't work because of long overflow
		//result = ft_uconvert_base(bin_mant, BINAR, DECIM);
	}
	result = ft_itoa_base(floor, base);
	ft_strappend(&result, ".");
	ft_strappend(&result, fractional);	
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
	mantissa = ((extract << 12) >> 12);
	if (exp_b2 != -1023)
		mantissa |= 0x10000000000000;
	else
		++exp_b2;
//Mantissa should be appropriately separated with its point before each part can be converted, no ?
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
