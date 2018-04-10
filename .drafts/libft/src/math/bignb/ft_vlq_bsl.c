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
** Keep an eye on the fact that tmp is built of the union of two chunks of bits:
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
	t_u32	len;
	t_u32	i;
	
	len = ft_vlqlen(vlq);
	result = ft_vlqnew(size);
	diff = sm63 - vlqmsb_offset;
	i = 0;
	while (i < size)
	{
		tmp = 0;
		if (diff > 0)
		{
			if (0 < i && i - 1 < len)
{
				tmp |= ft_u64bits_itoj(vlq[i - 1], 1 + sm63, 64) << sm63;
//ft_printf("\t\t\t%2d - diff = %d > 0 READ 1; tmp = %20lx; sm63 == %d; voff == %d; vlq[i - 1] == %#lx\n", i, diff, tmp, sm63, vlqmsb_offset, vlq[i - 1]);
}			if (i < len)
{
				tmp |= ft_u64bits_itoj(vlq[i], 1, 1 + sm63) >> (63 - sm63);
//ft_printf("\t\t\t%2d - diff = %d > 0 READ 2; tmp = %20lx; sm63 == %d; voff == %d; vlq[i    ] == %#lx\n", i, diff, tmp, sm63, vlqmsb_offset, vlq[i]);
}
		}
		else
		{
			if (i < len)
{
				tmp |= ft_u64bits_itoj(vlq[i], 1 + sm63, 64) << sm63;
//ft_printf("\t\t\t%2d - diff = %d <= 0 READ 1; tmp = %20lx; sm63 == %d; voff == %d; vlq[i    ] == %#lx\n", i, diff, tmp, sm63, vlqmsb_offset, vlq[i]);
}
			if (i + 1 < len)
{
				tmp |= ft_u64bits_itoj(vlq[i + 1], 1, 1 + sm63) >> (63 - sm63);
//ft_printf("\t\t\t%2d - diff = %d <= 0 READ 2; tmp = %20lx; sm63 == %d; voff == %d; vlq[i + 1] == %#lx\n", i, diff, tmp, sm63, vlqmsb_offset, vlq[i + 1]);
}
		}
		if ((i <= len && diff > 0) || (i < len && diff <= 0)) //TODO THIS CONDITION IN BSL
			result[i] |= tmp;
		++i;
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
		size = ft_vlqlen(vlq) + (62 + shift - vlqmsb_offset) / 63;
		result = bsl_chunk_shift(vlq, shift % 63, size, vlqmsb_offset);
	}
	return (result);
}

/*
** 	max = 0x0de0b6b3a7640000
			0 000 1101 1110 0000
**	tmp = 0xef05b59d3b200000, 0x0000000000000000 (shift = 3)
			1 110 1111 0000
=> bitshift left 1 de trop et overwrite du bit souhaité qand shift = vlqmsb_os
**
**
	max = 0x6bc75e2d63100000
			0 110 1011 1100
	tmp = 0x8000000000000006, 0x5e3af16b18800000 (shift = 3)
					... 0110    0 101 1110 0011
*/
