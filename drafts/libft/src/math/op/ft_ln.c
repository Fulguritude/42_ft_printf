/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ln.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 06:05:08 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/11 07:02:32 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


#include <stdio.h>


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
//printf("i = %.0lf;\n powx = %.20lf;\n ln(1 + %.20le) = %.25lf\n", i, powx, x, result);
		powx *= x;
		result += (((((int)i % 2)) * 2.) - 1.) * (powx / i);
		//diff = result - prev_res;
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
double		ft_ln(double lf)
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
	if (lf < 1. || 2. <= lf)
	{
		extract = *(t_u64*)(&lf);
//printf("extract %#lx\n", extract);
		norm = (extract & (_MSB_ | 0xFFFFFFFFFFFFF)) | 0x3FF0000000000000;
//printf("norm %#lx\n", norm);
//printf("norm %lf\n", *(double*)(&norm));
		return (LN2 * (((extract << 1) >> 53) - 1023) + ft_ln(*(double*)(&norm)));
	}
	if (1.9 <= lf && lf < 2)
		return (ft_ln(lf * DIV2_BY3) + LN_3DIV2);
	result = ln_taylor_series(lf - 1.);
	return (result);
}

#if 0
static double	ln_taylor_series(double x, double prec_test, double diff)
{
	double	result;
	double	prev_res;
	double	powx;
	double	i;

	i = 2.;
	powx = x;
	result = x;
	while (ABS(diff) > prec_test && i < 20.)
	{
//printf("i = %.0lf;\n powx = %lf;\n ln(1 + %10le) = %.25lf\n", i, powx, x, result);
		powx *= x;
		result += (((((int)i % 2)) * 2.) - 1.) * (powx / i);
		diff = result - prev_res;
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
double		ft_ln(double lf)
{
	double	result;
	double	prec_test;
	double	diff;
	t_u64	extract;
	t_u64	decim_prec;
 
	if (lf <= 0.)
		return (0.0f / 0.0f);
	if (lf < 1. || 2. <= lf)
	{
		extract = *(t_u64*)(&lf);
//printf("extract %#lx\n", extract);
		decim_prec = (extract & (_MSB_ | 0xFFFFFFFFFFFFF)) | 0x3FF0000000000000;
//printf("decim_prec %#lx\n", decim_prec);
//printf("decim_prec %lf\n", *(double*)(&decim_prec));
		return (LN2 * (((extract << 1) >> 53) - 1023) + ft_ln(*(double*)(&decim_prec)));
	}
	decim_prec = 18;
	prec_test = 1. / ft_lfpowi(10., decim_prec + 1);
	diff = 2.;
	result = ln_taylor_series(lf - 1., prec_test, diff);
	return (result);
}
#endif
