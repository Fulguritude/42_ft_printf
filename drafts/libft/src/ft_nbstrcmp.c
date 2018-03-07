/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbstrcmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 03:48:55 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/06 04:10:29 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbstrcmp(t_nbstr const ns1, t_nbstr const ns2)
{
	int		diff;
	int		i;

	if (ns1.base_n != ns2.base_n)
		ft_putendl_fd("User caused a base error in nbstrcmp", 2);
	if (ns1.digits != ns2.digits)
		return ((ns1.digits > ns2.digits) ?
			ft_in_base(ns1.rev_mant[ns1.digits - 1], ns1.base) :
			-ft_in_base(ns2.rev_mant[ns2.digits - 1], ns2.base));
	i = ns1.digits - 1;
	while (i >= 0 && (diff = ft_in_base(ns1.rev_mant[i], ns1.base) 
				- ft_in_base(ns2.rev_mant[i], ns2.base)) == 0)
		--i;
	return (diff);
}
