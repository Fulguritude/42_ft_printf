/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 15:57:02 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/13 16:20:27 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//TODO remove for moulinette

long		ft_floor(double lf)
{
	long	result;
	int		exp;

	exp = (((t_u64)lf << 1) >> 52) - 1023;
	if (exp > 308)
		ft_putendl_fd("Double out of acceptable range in ft_floor.", 2);
	result = (long)lf;
	if (ABS(result) > 9007199254740992)
		ft_putendl_fd("Untrustworthy result in ft_floor.", 2);
	return (result);
}
