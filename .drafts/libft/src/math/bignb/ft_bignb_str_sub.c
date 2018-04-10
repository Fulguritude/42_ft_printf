/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignb_str_sub.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 01:00:22 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/14 19:34:57 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		set_max_min(t_bignb const a, t_bignb const b,
							t_bignb *max, t_bignb *min)
{
	char	max_c;
	int		cmp;

	cmp = ft_bignb_strcmp(a, b);
	max_c = cmp > 0 ? 'a' : 'b';
	*max = max_c == 'a' ? a : *max;
	*max = max_c == 'b' ? b : *max;
	*min = max_c == 'a' ? b : *min;
	*min = max_c == 'b' ? a : *min;
	return (max_c);
}

static void		do_sub(t_bignb const max, t_bignb const min,
						t_bignb bn) //, char const *tmp)
{
	t_u32		i;
	int			diff;
	t_u8		neg_carry;

	i = 0;
	neg_carry = 0;
	while (i < max.digits)
	{
		diff = ft_in_base(max.rev_ns[i], max.base);
		diff -=	i < min.digits ? ft_in_base(min.rev_ns[i], min.base) : 0;
		diff -= neg_carry;
		neg_carry = diff < 0 ? 1 : 0;
		diff = diff < 0 ? diff + bn.radix : diff;
		bn.rev_ns[i] = bn.base[diff];
		++i;
	}
}

t_bignb			ft_bignb_str_sub(t_bignb const a, t_bignb const b)
{
	t_bignb		bn;
	t_bignb		max;
	t_bignb		min;
	char		max_c;

	if (!(a.radix == b.radix) || !(a.neg != b.neg) || !a.rev_ns || !b.rev_ns)
		ft_putendl_fd("Sign, operand or radix error in bignb_str_sub.", 2);
	max_c = set_max_min(a, b, &max, &min);
	bn = ft_bignbnew(max.digits, max.base);
	do_sub(max, min, bn);
	bn.digits = max.digits;
	while (bn.rev_ns[bn.digits - 1] == bn.base[0])
		--bn.digits;
	bn.rev_ns[bn.digits] = '\0';
	if (max_c != 'e')
		bn.neg = (max_c == 'a' && a.neg) || (max_c == 'b' && b.neg) ? 1 : 0;
	ft_bignb_revns_updates_vlq(&bn);
	return (bn);
}
