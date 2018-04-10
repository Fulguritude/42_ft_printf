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
#if 0
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
#endif

/*
** Note that bitshift right on a negative long is implementation defined (can
** fill memory with zeros or ones, so we made a version of carry here that works
** with both).
*/
static t_vlq	do_vlqsub(t_vlq const max, t_vlq const min) //, t_vlq *a_res)
{
	t_vlq	result;
	int		max_len;
	int		min_len;
	long	cur_part;
	t_u64	carry;

	max_len = ft_vlqlen(max) - 1;
	min_len = ft_vlqlen(min) - 1;
	result = ft_vlqnew(max_len + 1);
	carry = 0;
	while (max_len >= 0)
	{
//ft_printf("maxlen %d : minlen %d\n", max_len, min_len);
		cur_part = NOT_MSB(max[max_len]);
//ft_printf("1 - cur_part = %#lx, max[max_len] = %#lx\n", cur_part, max[max_len]);
		cur_part -= (min_len >= 0) ? NOT_MSB(min[min_len]) : 0;
//ft_printf("2 - cur_part = %#lx, min[min_len] = %#lx\n", cur_part, min[min_len]);
		cur_part -= carry ? 1 : 0;
		carry = MSB(cur_part);
//ft_printf("3 - carry = %d\n", carry);
		result[max_len] |= NOT_MSB(cur_part);
//ft_printf("4 - cur_part = %#lx\n", cur_part);
//ft_printf("5 - result[max_len] = %#lx\n", result[max_len]);
		--max_len;
		--min_len;
	}
//ft_putendl(ft_vlqhex(result));
	ft_vlqtrim(&result);
//ft_putendl(ft_vlqhex(result));
	return (result);
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
	result = do_vlqsub(max, min); // ft_vlqnew(ft_vlqlen(max));
//	ft_vlqtrim(&result);
	return (result);
}
