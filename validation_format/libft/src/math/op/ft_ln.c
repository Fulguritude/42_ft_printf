/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ln.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 06:05:08 by fulguritu         #+#    #+#             */
/*   Updated: 2018/05/12 17:14:33 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

static double	ln_taylor_series(double x)
{
	double	result;
	double	prev_res;
	double	powx;
	double	i;

	i = 2.;
	powx = x;
	result = x;
	while (powx != 0.)
	{
		powx *= x;
		result += (((((int)i % 2)) * 2.) - 1.) * (powx / i);
		if (result == prev_res)
			break ;
		prev_res = result;
		++i;
	}
	return (result);
}

/*
** Returns the natural logarithm of lf.
** ln(y) = ln(x*2^n) = n*ln(2) + ln(x) with 1 <= x < 2 and n = exp_b2
*/

double			ft_ln(double lf)
{
	double	result;
	t_u64	ex;
	t_u64	norm;

	if (lf < 0.)
		return (0. / 0.);
	if (lf == 0.)
		return (-1. / 0.);
	if (lf == 1.)
		return (0.);
	if (lf == 1. / 0.)
		return (lf);
	if (lf < 1. || 2. <= lf)
	{
		ex = *(t_u64 *)(&lf);
		norm = (ex & (_MSB_ | 0xFFFFFFFFFFFFF)) | 0x3FF0000000000000;
		result = ft_ln(*(double *)(&norm));
		return (0x1.62E42FEFA39EFp-1 * (((ex << 1) >> 53) - 1023) + result);
	}
	if (1.9 <= lf && lf < 2.)
		return (ft_ln(lf * 0x1.5555555555556p-1) + 0x1.9F323ECBF984Cp-2);
	result = ln_taylor_series(lf - 1.);
	return (result);
}
