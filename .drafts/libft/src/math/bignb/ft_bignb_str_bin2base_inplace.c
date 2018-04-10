/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignb_str_bin2base_inplace.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 00:14:05 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/14 19:34:56 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*rev_binstr_chunk_to_char(char *rev)
{
	char	bit;
	char	val;
	int		i;

	bit = 0x1;
	val = 0;
	i = 0;
	while (rev[i])
	{
		if (rev[i] == '1')
			val += bit;
		bit <<= 1;
		++i;
	}
	rev[0] = val;
	rev[1] = '\0';
	return (rev);
}

static void		binstr_to_pow2base(t_bignb *a_bn)
{
	char	**bin_chunks;
	int		pow;
	int		val;
	int		i;
	char	*result;

	pow = ft_ilog2(a_bn->radix);
	result = ft_strnew((ft_strlen(a_bn->rev_ns) + pow - 1) >> pow);
	bin_chunks = ft_strdivide(a_bn->rev_ns, pow);
	ft_strlsmap_inplace(&bin_chunks, &rev_binstr_chunk_to_char);
	i = 0;
	while (bin_chunks[i])
	{
		val = bin_chunks[i][0];
		result[i] = a_bn->base[val];
		++i;
	}
	ft_strlsdel(&bin_chunks);
	ft_strdel(&(a_bn->rev_ns));
	a_bn->rev_ns = result;
}

static void		binstr_to_anybase(t_bignb *a_bn)
{
	t_bignb		result;
	t_bignb		pow2_ib;
	int			i;

	result = ft_bignbnew(1, a_bn->base);	
	result.neg = 0;
	pow2_ib = ft_bignbnew(1, a_bn->base);
	pow2_ib.neg = 0;
	pow2_ib.rev_ns[0] = a_bn->base[1];
	ft_strctrim_right_inplace(&(a_bn->rev_ns), '0');
	i = -1;
	while (a_bn->rev_ns[++i])
	{
		if (a_bn->rev_ns[i] == '1')
			ft_bignb_add_acc(&result, pow2_ib);
		ft_bignb_add_acc(&pow2_ib, pow2_ib);
	}
	ft_bignb_vlq_updates_revns(a_bn);
	result.neg = a_bn->neg;
	ft_strdel(&(a_bn->rev_ns));
	ft_strdel(&(pow2_ib.rev_ns));
	*a_bn = result;
}

/*
** TODO ft_putendl_fd("Invalid operand given to nbstr_bin2base_ip.");
**
** Since this is a function on bignb, the binstr should be in reverse.
*/
void			ft_bignb_str_bin2base_inplace(t_bignb *a_bn, char const *base)
{
	t_u32		len;

	if (ft_strequ(base, BINAR) || (!a_bn->vlq && !a_bn->rev_ns) ||
		!ft_is_valid_base(base) || !ft_strequ(a_bn->base, BINAR))
		return ;
	len = ft_strlen(base);
	if (len == 4 || len == 8 || len == 16 || len == 32 || len == 64 ||
		len == 128 || len == 256)
		binstr_to_pow2base(a_bn);
	else
		binstr_to_anybase(a_bn);
}
