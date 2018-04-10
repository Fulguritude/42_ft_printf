/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignb_str_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 23:03:34 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/14 19:34:55 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bignb					ft_bignb_str_add(t_bignb const a, t_bignb const b)
{
	t_bignb		bn;
	int			char_sum;
	t_u8		carry;
	t_u32		i;

	if (a.neg != b.neg)
		return (ft_bignb_str_sub(a, b));
	bn.rev_ns = ft_strnew((MAX(a.digits, b.digits)) + 1);
	i = 0;
	carry = 0;
	while (i < a.digits || i < b.digits || carry)
	{
		char_sum = carry;
		if (i < a.digits)
			char_sum += ft_in_base(a.rev_ns[i], a.base);
		if (i < b.digits)
			char_sum += ft_in_base(b.rev_ns[i], b.base);
		carry = char_sum >= a.radix ? 1 : 0;
		char_sum %= a.radix;
		bn.rev_ns[i] = a.base[char_sum];
		++i;
	}
	bn.base = a.base;
	bn.radix = a.radix;	
	bn.digits = ft_strlen(bn.rev_ns);
	bn.vlq = NULL;
	bn.neg = a.neg == 1 && b.neg == 1 ? 1 : 0;
	ft_bignb_revns_updates_vlq(&bn);
	return (bn);
}
