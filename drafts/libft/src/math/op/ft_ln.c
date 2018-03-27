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

/*
** TODO Verify that end condition works on large numbers
*/
static double	ln_taylor_series(double lf, double prec_test, double diff)
{
	double	result;
	double	prev_res;
	double	powlf;
	double	i;

	i = 2.;
	powlf = lf;
	result = lf;
	while (ABS(diff) > prec_test)
	{
		powlf *= lf;
		result += (((((int)i % 2)) * 2) - 1) * (powlf / i);
		diff = result - prev_res;
		prev_res = result;
		++i;
	}
	return (result);
}

/*
** Returns the natural logarithm of lf.
*/
double		ft_ln(double lf, t_u8 decim_prec)
{
	double	result;
	double	prec_test;
	double	diff;

	if (lf <= 0.)
		return (0.0f / 0.0f);
	if (lf >= 2.)
		return (-ft_ln(1. / lf, decim_prec));
	if (decim_prec > 15)
		decim_prec = 15;
	prec_test = 1. / ft_lfpowi(10., decim_prec + 1);
	diff = 2.;
	result = ln_taylor_series(lf - 1, prec_test, diff);
	return (result);
}
