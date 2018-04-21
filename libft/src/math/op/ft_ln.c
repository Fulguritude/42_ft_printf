/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ln.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 06:05:08 by fulguritu         #+#    #+#             */
/*   Updated: 2018/04/21 15:20:18 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	t_u64	extract;
	t_u64	norm;

	if (lf < 0.)
		return (0.0f / 0.0f);
	if (lf == 0.)
		return (-1. / 0.);
	if (lf == 1.)
		return (0.);
	if (lf == 1. / 0.)
		return (lf);
	if (lf < 1. || 2. <= lf)
	{
		extract = *(t_u64*)(&lf);
		norm = (extract & (_MSB_ | 0xFFFFFFFFFFFFF)) | 0x3FF0000000000000;
		return (LN2 * (((extract << 1) >> 53) - 1023)
					+ ft_ln(*(double*)(&norm)));
	}
	if (1.9 <= lf && lf < 2)
		return (ft_ln(lf * DIV2_BY3) + LN_3DIV2);
	result = ln_taylor_series(lf - 1.);
	return (result);
}
