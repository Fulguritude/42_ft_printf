/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 15:05:07 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/15 15:05:17 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void do_sub_parts(t_vlq const max, t_vlq const min, t_vlq *a_res, int i)
{
	int		offset;
	long	cur_part;
	long	carry;
	int		max_len;

	max_len = ft_vlqlen(max);
	cur_part = max_len - ft_vlqlen(min);
	offset = i;
	while (i < max_len)
	{
		cur_part = -(carry * (_MSB_ >> 1)); 
		cur_part += NOT_MSB(max[i]);
		cur_part -= NOT_MSB(min[i - offset]);
		carry = MSB(cur_part);
		(*a_res)[i] |= NOT_MSB(cur_part);
		++i;
	}
	cur_part -= carry * (_MSB_ >> 1); 
	cur_part += NOT_MSB(max[i]);
	cur_part -= NOT_MSB(min[i - offset]);
	if (MSB(cur_part))
		ft_putendl_fd("Last index in vlq_sub should not carry.", 2);
	(*a_res)[i] |= NOT_MSB(cur_part);
}

static void	do_vlqsub(t_vlq const max, t_vlq const min, t_vlq *a_res)
{
	t_u32	max_len;
	long	cur_part;
	int		i;

	max_len = ft_vlqlen(max);
	cur_part = max_len - ft_vlqlen(min);
	i = -1;
	while (++i < cur_part)
		(*a_res)[i] |= NOT_MSB(max[i]);
	do_sub_parts(max, min, a_res, i);
}

/*
** Subtraction operator. Always returns ABS(a-b).
*/
t_vlq		ft_vlq_sub(t_vlq const a, t_vlq const b)
{
	t_vlq	result;
	t_vlq	max;
	t_vlq	min;
	long	diff;

	diff = ft_vlqcmp(a, b);
	min = diff < 0 ? a : b;
	max = diff < 0 ? b : a;
	result = ft_vlqnew(ft_vlqlen(max));
	do_vlqsub(max, min, &result);
	ft_vlqtrim(&result);
	return (result);
}
