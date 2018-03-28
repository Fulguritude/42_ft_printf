/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_bsr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 02:23:02 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/20 04:22:15 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//TODO fix copy of bsl
/*
** (sum = shift + vlqmsb_offset) > 63 iff there's a left shift on the first
** chunk, and at least 1 removed index.
** Note that we treat this case in the else statement here, unlike the < 0 in
** bsl. This is to maintain a sort of symmetry that puts the parsing order
** first and foremost in order to make the code more legible.
*/
static t_vlq	bsr_chunk_shift(t_vlq const vlq, t_u32 sm63, 
								t_u8 size, t_u8 vlqmsb_offset)
{
	t_vlq	result;
	t_u64	tmp;
	t_s8	sum;
	int		i;
	
	if (sm63 == 0)
		sm63 = 63;
	result = ft_vlqnew(size);
	sum = sm63 + vlqmsb_offset;
	i = -1;
	while (++i < size)
	{
		tmp = 0;
//ft_printf("{blue}Read %d, sum = %d, sm63 = %d\n{eoc}", i, sum, sm63);
		if (sum < 63)
		{
			if (0 < i)
				tmp |= ft_u64bits_itoj(vlq[i - 1], 64 - sm63, 64) << (63 - sm63);
			tmp |= ft_u64bits_itoj(vlq[i], 1, 64 - sm63) >> sm63;
		}
		else
		{
			tmp |= ft_u64bits_itoj(vlq[i], 64 - sm63, 64) << (63 - sm63);
			tmp |= ft_u64bits_itoj(vlq[i + 1], 1, 64 - sm63) >> sm63;
		}
//ft_printf("{green}Read %d, tmp = %#lx\n{eoc}", i, tmp);
		result[i] |= tmp;
	}
	return (result);
}

/*
** vlqmsb_offset is the number of leading zeros in vlq[0]
*/
t_vlq		ft_vlq_bsr(t_vlq const vlq, t_u32 shift)
{
	t_vlq	result;
	t_u32	size;
	t_u8	vlqmsb_offset;

	if (shift == 0)
		result = ft_vlqdup(vlq);
	else if (ft_vlq_count_sigbit(vlq) <= shift)
		result = ft_vlqnew(1);
	else
	{
		vlqmsb_offset = 63 - ft_vlq_count_sigbit_of_part(vlq[0]);
		size = ft_vlqlen(vlq) - ((shift + vlqmsb_offset) / 63);
//ft_printf("vlqlen %d ; shift + vlqmsb %d ; size = %d\n", ft_vlqlen(vlq), shift + vlqmsb_offset, size);
		result = bsr_chunk_shift(vlq, shift % 63, size, vlqmsb_offset);
	}
	return (result);
}
