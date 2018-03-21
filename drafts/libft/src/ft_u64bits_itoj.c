/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u64bits_itoj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 04:18:06 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/21 04:18:09 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns a value such that every bit b that is not at index i <= b < j is
** switched off. Returns -1 (ie, 0xFFF...FF) in case of error. 
** TODO: add to libft_mem.h and appropriate doc
** TODO: make it work with a byte_len argument 1, 2, 4 or 8, like ft_swap ?
*/
/*
** 0 is MSB, 63 is LSB ; bit at i included, bit at j excluded
** j is an index, not a number of bits after i.
*/
t_u64			ft_u64bits_itoj(t_u64 ul, t_u8 i, t_u8 j)
{
	t_u64	allbits;

	allbits = (t_u64)-1;
	if (63 < i || 64 < j || j < i)
		return (allbits);
	allbits = ((allbits << i) >> (i + j)) << j;
	return (ul & allbits);
}
