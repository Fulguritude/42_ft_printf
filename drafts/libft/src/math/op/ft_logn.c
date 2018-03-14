/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 06:05:08 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/11 06:55:47 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns the power to which n should be raised to obtain lf.
*/
double		ft_logn(double lf, double n, t_u8 decim_prec)
{
	return (ft_ln(lf, decim_prec + 1) / ft_ln(n, decim_prec + 1));
}
