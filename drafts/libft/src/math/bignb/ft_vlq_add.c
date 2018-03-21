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

t_vlq		ft_vlq_add(t_vlq const a, t_vlq const b)
{
	t_vlq	result;
	int		a_len;
	int		b_len;
	t_u64	cur_part;
	t_u64	carry;

	a_len = ft_vlqlen(a);
	b_len = ft_vlqlen(b);
	result = ft_vlqnew((MAX(a_len, b_len) + 1));
	carry = 0;
	while (--a_len >= 0 || --b_len >= 0)
	{
		cur_part = carry;
		cur_part += (a_len >= 0) ? NOT_MSB(a[a_len]) : 0;
		cur_part += (b_len >= 0) ? NOT_MSB(b[b_len]) : 0;
		carry = MSB(cur_part);
		result[MAX(a_len, b_len)] |= NOT_MSB(cur_part);
	}
	ft_vlqtrim(&result);
	return (result);
}
