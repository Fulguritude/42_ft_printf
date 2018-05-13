/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfpowi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 11:27:32 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:14:33 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

double		ft_lfpowi(double lf, int power)
{
	int			i;
	double		result;

	result = 1.;
	i = 0;
	if (power == 0)
		return (result);
	else if (power > 0)
		while (++i <= power)
			result *= lf;
	else
	{
		power = -power;
		while (++i <= power)
			result /= lf;
	}
	return (result);
}
