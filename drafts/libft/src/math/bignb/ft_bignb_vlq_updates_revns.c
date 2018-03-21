/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignb_vlq_updates_revns.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 05:45:48 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/15 05:51:01 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*vlqpart_to_tmp_binstr(t_u64 val)
{
	char	*result;
	int		j;

	result = ft_strnew(63);
	j = 0;
	while (j < 63)
	{
		result[j] = val % 2 ? '1' : '0';
		val /= 2;
		++j;
	}
	return (result);
}

/*
** Returns the representation of vlq in binary as a string, which is then
** reversed.
*/
static char			*vlq_to_bin_revns(t_vlq const vlq)
{
	char	*result;
	char	*tmp;
	int		i;

	result = ft_strnew(0);
	i = 0;
	while ((vlq[i] & _MSB_))
	{
		tmp = vlqpart_to_tmp_binstr(NOT_MSB(vlq[i]));
		ft_strmerge(&tmp, &result);
		++i;
	}
	tmp = vlqpart_to_tmp_binstr(result[i]);
	ft_strmerge(&tmp, &result);
	ft_strctrim_right_inplace(&result, '0');
	return (result);
}

/*
**
** Binary sums of 5
**
** 5			101
** 10		   1010
** 15		   1111
** 20		  10100
** 25		  11001
**
** binary powers of ten
**  		10^			|			5^		 |  2^
** 0		1       			             1
** 1		10 					           1010
** 2		100 				         1100100
** 3		1000 				       1111101000
** 4		10000 				    10011100010000
** 5		100000				  11000011010100000
** 6		1000000				11110100001001000000
** 7		10000000		 100110001001011010000000
** 8		100000000	   101111101011110000100000000
**			rdx10							rdx2
**
** jusqua puissance 18 pour les unsigned long de 63 bits, faudrait en hexa,
** voire une formule generale pour anybase.
*/

static char		*vlq_to_anybase_revns(t_vlq const vlq, char const *base)
{
	//TODO this is as naive an implementation as it gets...

	char	*result;
	t_vlq	tmp_vlq;
	t_vlq	div;
	t_vlq	mod;
	t_u64	radix;

	result = ft_strnew(0);
	tmp_vlq = vlq;
	radix = ft_strlen(base);
	while (tmp_vlq)
	{
		ft_vlq_divmod(tmp_vlq, &radix, &div, &mod);
		ft_strpad_left_inplace(&result, base[*mod], 1);
		ft_vlqdel(&tmp_vlq);
		tmp_vlq = div;
	}
	return (result);
}

static char		*vlq_to_decim_revns(t_vlq const vlq)
{
	//TODO placeholder: optimize for base_10

	return (vlq_to_anybase_revns(vlq, DECIM));
}

void		ft_bignb_vlq_updates_revns(t_bignb *bn)
{
	if (!bn->vlq)
	{
		ft_putendl_fd("Empty vlq field in bignb_vlq_updates_revns arg.", 2);
		return ;
	}
	ft_strdel(&(bn->rev_ns));
	if (ft_strequ(bn->base, BINAR))
		bn->rev_ns = vlq_to_bin_revns(bn->vlq);
	else if (ft_strequ(bn->base, DECIM))
		bn->rev_ns = vlq_to_decim_revns(bn->vlq);
	else if (bn->radix == 4 || bn->radix == 8 || bn->radix == 16 ||
		bn->radix == 32 || bn->radix == 64 || bn->radix == 128)
	{
		bn->rev_ns = vlq_to_bin_revns(bn->vlq);
		ft_bignb_str_bin2base_inplace(bn, (char const*)bn->base);
	}
	else
		bn->rev_ns = vlq_to_anybase_revns(bn->vlq, bn->base);
	bn->digits = ft_strlen(bn->rev_ns);
}
