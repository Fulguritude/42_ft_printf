/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 06:07:41 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/15 07:26:00 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Maybe improve size management to avoid call to vlqtrim : there is a carry iff
** the union of the two operands has a series of leading 1s, and at its inter-
** section has at least 1 bit in common with that series.
** Use inspiration from here for bwa and bwo
*/
t_vlq		ft_vlq_add(t_vlq const a, t_vlq const b)
{
	t_vlq	result;
	int		a_len;
	int		b_len;
	t_u64	cur_part;
	t_u64	carry;

	a_len = ft_vlqlen(a) - 1;
	b_len = ft_vlqlen(b) - 1;
	result = ft_vlqnew((MAX(a_len, b_len) + 2));
	carry = 0;
	while (a_len >= 0 || b_len >= 0)
	{
//ft_printf("alen %d : blen %d\n", a_len, b_len);
		cur_part = carry;
//ft_printf("1 - res = %#lx, a = %#lx\n", cur_part, a[a_len]);
		cur_part += (a_len >= 0) ? NOT_MSB(a[a_len]) : 0;
//ft_printf("2 - res = %#lx, b = %#lx\n", cur_part, b[b_len]);
		cur_part += (b_len >= 0) ? NOT_MSB(b[b_len]) : 0;
//ft_printf("3 - res = %#lx\n", cur_part);
		carry = MSB(cur_part);
//ft_printf("4 - carry = %d\n", carry);
		result[MAX(a_len, b_len) + 1] |= NOT_MSB(cur_part);
		--a_len;
		--b_len;
	}
//ft_putendl(ft_vlqhex(result));
	ft_vlqtrim(&result);
//ft_putendl(ft_vlqhex(result));
	return (result);
}
