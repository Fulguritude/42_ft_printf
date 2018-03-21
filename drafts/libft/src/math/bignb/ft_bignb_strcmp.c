/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignb_strcmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 03:48:55 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/14 19:34:56 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_bignb_strcmp(t_bignb const bn1, t_bignb const bn2)
{
	int		ns_diff;
	int		i;

	if (bn1.radix != bn2.radix)
		ft_putendl_fd("User caused a base error in bignb_strcmp", 2);
	if (bn1.digits != bn2.digits)
		return ((bn1.digits > bn2.digits) ?
			ft_in_base(bn1.rev_ns[bn1.digits - 1], bn1.base) :
			-ft_in_base(bn2.rev_ns[bn2.digits - 1], bn2.base));
	i = bn1.digits - 1;
	while (i >= 0 && (ns_diff = ft_in_base(bn1.rev_ns[i], bn1.base) 
				- ft_in_base(bn2.rev_ns[i], bn2.base)) == 0)
		--i;
	return (ns_diff);
}
