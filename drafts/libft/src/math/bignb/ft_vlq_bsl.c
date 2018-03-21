/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_bsl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:41:55 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/20 04:22:15 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//TODO Remove diff if necessary for moulinette, or see if the if else structure can employ smart ternaries ? 
/*
** (diff = shift - vlqmsb_offset) > 0 iff there's a right shift on the first
** chunk, and at least 1 added new index. Also notice that for bsl chunks, those
** that need to be shifted left are shifted by "shift % 63" while those that
** need to be shifted right are shifted by "63 - (shift % 63)", and that this
** behavior is reversed for bsr_chunk_shift.
**
** Keep an eye on the fact that tmp is built of the union of two chnks of bits:
** one with 'shift' bits, the other with '63 - shift' bits. Either of these two
** values will be added with a 1 in order to skip the vlq format MSB in each.
** The shift on a single chunk is obviously always '63 - sigbit_in_chunk'... 
** where sigbit_in_chunk is our 'shift' or '63 - shift'
**
** shift mod 63 is sm63 or s63 because of 80 columns and moulinette.
*/
static t_vlq	bsl_chunk_shift(t_vlq const vlq, t_u32 sm63, 
								t_u8 size, t_u8 vlqmsb_offset)
{
	t_vlq	result;
	t_u64	tmp;
	t_s8	diff;
	int		i;
	
	result = ft_vlqnew(size);
	diff = sm63 - vlqmsb_offset;
	i = -1;
	while (++i < size)
	{
		tmp = 0;
		if (diff > 0)
		{
			if (0 < i)
				tmp |= ft_u64bits_itoj(vlq[i - 1], 1 + sm63, 64) << sm63;
			tmp |= ft_u64bits_itoj(vlq[i], 1, 1 + sm63) >> (63 - sm63);
		}
		else
		{
			tmp |= ft_u64bits_itoj(vlq[i], 1 + sm63, 64) << sm63;
			if (i + 1 < size)
				tmp |= ft_u64bits_itoj(vlq[i + 1], 1, 1 + sm63) >> (63 - sm63);
		}
		result[i] |= tmp;
	}
	return (result);
}

/*
** vlqmsb_offset is the number of leading zeros in vlq[0]
*/
t_vlq			ft_vlq_bsl(t_vlq const vlq, t_u32 shift)
{
	t_vlq	result;
	t_u8	vlqmsb_offset;
	t_u8	size;

	if (shift == 0)
		result = ft_vlqdup(vlq);
	else
	{
		vlqmsb_offset = 63 - ft_vlq_count_sigbit_of_part(vlq[0]);
		size = ft_vlqlen(vlq) + (shift - vlqmsb_offset) / 63;
		result = bsl_chunk_shift(vlq, shift % 63, size, vlqmsb_offset);
	}
	return (result);
}
