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

static char		*ft_lftoa_base_exp(char const *base, t_u8 minus,
									int exp, t_u32 mantissa)
{
	char	*result;
	char	*tmp;

	tmp = ft_uitoa_base(mantissa, base);
	result = ft_strinsert(tmp, ".", 1);
	free(tmp);
	tmp = ft_itoa_base(exp, base);
	if (tmp[0] != '-' && ft_strlen(tmp) < 2)
		ft_strpad_left_inplace(tmp, base[0], 1);
	else if (tmp[0] == '-' && ft_strlen(tmp) < 3)
	{
		tmp[0] = base[0];
		ft_strprepend("-", tmp);
	}
	ft_strappend(result, "\t");
	ft_strappend(result, tmp);
	free(tmp);
	if (minus)
		ft_strprepend(result, "-");
	return (result);
}

static char		*ft_lftoa_base_point(char const *base, t_u8 minus,
									int exp, t_u32 mantissa)
{
	char	*result;
	int		index;

	result = ft_uitoa_base(mantissa, base);
	if (exp > 0)
		ft_strpad_right_in_place(result, base[0], exp);
	else if (exp < 0 && (index = ft_strlen(result) - exp) > 0)
		ft_strinsert(result, ".", index);
	else if (exp < 0 && index <= 0)
	{
		ft_strpad_left_inplace(result, base[0], -index);
		ft_strprepend(".", result);
		ft_strpad_left_inplace(result, base[0], 1);
	}
	if (minus)
		ft_strprepend("-", result);
	return (result);
}

char			*ft_lftoa_base(double lf, char const *base, char style)
{
	char	*result;
	t_u8	minus;
	int		exp;
	t_u64	mantissa;

	minus = lf >> 63;
	exp = ((lf << 1) >> 52) - 1023;
	mantissa = (lf << 12) >> 12;
	result = ft_strnew(0);
	if (ft_isalpha(style))
	{
		result = ft_lftoa_base_exp(base, sign, exp, mantissa);
		result[ft_strchr(result, '\t')] = style;
	}
	else
		result = ft_lftoa_base_point(base, sign, exp, mantissa);
	return (result);
}
