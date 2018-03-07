/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbstr_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 23:03:34 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/06 00:59:18 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_nbstr					ft_nbstr_add(t_nbstr const a, t_nbstr const b)
{
	t_nbstr		ns;
	int			char_sum;
	t_u8		holdover;
	t_u32		i;

	if (a.neg != b.neg)
		return (ft_nbstr_sub(a, b));
	ns.rev_mant = ft_strnew((MAX(a.digits, b.digits)) + 1);
	i = 0;
	holdover = 0;
	while (i < a.digits || i < b.digits || holdover)
	{
		char_sum = holdover;
		if (i < a.digits)
			char_sum += ft_in_base(a.rev_mant[i], a.base);
		if (i < b.digits)
			char_sum += ft_in_base(b.rev_mant[i], b.base);
		holdover = char_sum >= a.base_n ? 1 : 0;
		char_sum %= a.base_n;
		ns.rev_mant[i++] = a.base[char_sum];
	}
	ns.base = a.base;
	ns.base_n = a.base_n;
	ns.digits = ft_strlen(ns.rev_mant);
	return (ns);
}
