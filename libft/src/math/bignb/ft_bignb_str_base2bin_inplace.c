/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignb_str_base2bin_inplace.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 01:03:05 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/14 19:34:55 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns the chunk conversion of a digit in base with radix 2^pow to a string
** in binary, ie ('B', HXUPP, 4) => "1011"
*/
static char		*b2_char_to_rev_binstr(char const c, char const *base, int pow)
{
	char	*result;
	char	val;
	int		i;

	val = ft_in_base(c, base);
	result = ft_strnew(pow);
	i = 0;
	while (i < pow)
	{
		result[i] = val % 2 ? '1' : '0';
		val >>= 1; 
		++i;
	}
	return (result);
}

static void		pow2base_to_binstr(t_bignb *a_bn)
{
	char	*result;
	char	*tmp;
	int		pow;
	int		i;
	
	pow = ft_ilog2(a_bn->radix);
	i = 0;
	while (a_bn->rev_ns[i])
	{
		tmp = b2_char_to_rev_binstr(a_bn->rev_ns[i], a_bn->base, pow);
		ft_strappend(&result, tmp);
		free(tmp);
		++i;
	}
	ft_strctrim_right_inplace(&result, '0');
	ft_strdel(&(a_bn->rev_ns));
	a_bn->rev_ns = result;
	a_bn->base = BINAR;
	a_bn->radix = 2;
}

/*
** Big number bit strings, like all bignb->rev_ns, are in reverse.
*/
void			ft_bignb_str_base2bin_inplace(t_bignb *a_bn)
{
	if (a_bn->radix == 2)
		return ;
	if (a_bn->radix == 4 || a_bn->radix == 8 || a_bn->radix == 16 ||
		a_bn->radix == 32 || a_bn->radix == 64 || a_bn->radix == 128)
		pow2base_to_binstr(a_bn);
	else
	{
		ft_vlqdel(&(a_bn->vlq));
		ft_strrev_inplace(&(a_bn->rev_ns));
		a_bn->vlq = ft_atovlq(a_bn->rev_ns, a_bn->base);
		a_bn->base = BINAR;
		a_bn->radix = 2;
	}
}
