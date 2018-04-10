/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignb_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 23:03:34 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/14 19:34:55 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bignb					ft_bignb_add(t_bignb const a, t_bignb const b)
{
	t_bignb		bn;
	char		max;
	int			signs;

	if (!(a.vlq) || !(b.vlq))
		return (ft_bignbnew(1, a.base));
	if ((signs = a.neg != b.neg))
		bn.vlq = ft_vlq_sub(a.vlq, b.vlq);
	else
		bn.vlq = ft_vlq_add(a.vlq, b.vlq);
	max = ft_vlqcmp(a.vlq, b.vlq) < 0 ? 'b' : 'a';
	if ((a.neg && b.neg) ||
		(signs && ((max == 'a' && a.neg) || (max == 'b' && b.neg))))
		bn.neg = 1;
	else
		bn.neg = 0;
	bn.base = a.base;
	bn.radix = a.radix;
	bn.rev_ns = NULL;
	ft_bignb_vlq_updates_revns(&bn);
	return (bn);
}
