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
						t_bignb bn, char const *tmp)
{
	int			i;
	int			diff;
	t_u8		neg_carry;

	i = max.digits;
	while (--i >= 0)
	{
		diff = ft_in_base(max.rev_ns[i], max.base) -
				ft_in_base(tmp[i], min.base) - neg_carry;
		neg_carry = diff < 0 ? 1 : 0;
		diff = diff < 0 ? diff + bn.radix : diff;
		bn.rev_ns[i] = bn.base[diff];
	}
}

t_bignb			ft_bignb_str_sub(t_bignb const a, t_bignb const b)
{
	t_bignb		bn;
	t_bignb		max;
	t_bignb		min;
	char		*tmp;
	char		max_c;

	if (!(a.radix == b.radix) || !(a.neg != b.neg) || !a.rev_ns || !b.rev_ns)
		ft_putendl_fd("Sign, operand or radix error in bignb_str_sub.", 2);
	max_c = set_max_min(a, b, &max, &min);
	bn = ft_bignbnew(max.digits, max.base);
	tmp = ft_strpad_right(min.rev_ns, min.base[0], max.digits - min.digits);
	do_sub(max, min, bn, tmp);
	ft_strdel(&tmp);
	bn.digits = max.digits;
	while (bn.rev_ns[bn.digits - 1] == bn.base[0])
		--bn.digits;
	bn.rev_ns[bn.digits] = '\0';
	if (max_c != 'e')
		bn.neg = (max_c == 'a' && a.neg) || (max_c == 'b' && b.neg) ? 1 : 0;
	ft_bignb_revns_updates_vlq(&bn);
	return (bn);
}
