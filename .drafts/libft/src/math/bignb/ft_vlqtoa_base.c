/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlqtoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 20:22:00 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/28 20:22:10 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns the 63 significant bits of val as a string.
*/
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
** Returns the representation of vlq in binary as a string.
*/
static char			*vlq_to_binstr(t_vlq const vlq)
{
	char	*result;
	char	*tmp;
	t_u32	i;
	t_u32	len;

	result = ft_strnew(0);
	len = ft_vlqlen(vlq);
	i = 0;
	while (i < len)
	{
		tmp = vlqpart_to_tmp_binstr(NOT_MSB(vlq[i]));
		ft_strmerge(&tmp, &result);
		++i;
	}
	tmp = vlqpart_to_tmp_binstr(result[i]);
	ft_strmerge(&tmp, &result);
	ft_strctrim_right_inplace(&result, '0');
	ft_strrev_inplace(&result);
	return (result);
}

/*
** This is as naive an implementation as it gets, but it should suffice for most
** bases.
*/
static char		*vlq_to_anybase(t_vlq const vlq, char const *base)
{
	char	*result;
	t_vlq	tmp_vlq;
	t_vlq	div;
	t_vlq	mod;
	t_u64	radix;

	result = ft_strnew(0);
	tmp_vlq = ft_vlqdup(vlq);
	radix = ft_strlen(base);
	div = NULL;
	mod = NULL;
	while (tmp_vlq[0] || !div)
	{
		ft_vlq_divmod(tmp_vlq, &radix, &div, &mod);
		ft_strpad_left_inplace(&result, base[mod[0]], 1);

/*char *str = ft_vlq_abstractval_as_hex(tmp_vlq), *str2 = ft_vlq_abstractval_as_hex(div), *str3 = ft_vlq_abstractval_as_hex(mod);
ft_printf("{green}tmp_vlq = %s\n{eoc}radix = %#lx\n{blue}div = %s\n{magenta}mod = %s\n{yellow}result = %s{eoc}\n\n", str, radix, str2, str3, result);
ft_strdel(&str);ft_strdel(&str2);ft_strdel(&str3);
*/		ft_vlqdel(&tmp_vlq);
		ft_vlqdel(&mod);
		tmp_vlq = div;
	}
	ft_vlqdel(&tmp_vlq);
//ft_printf("final result anybase = {bold}{yellow_bg}{red}%s{eoc}\n", result);
	return (result);
}

/*
static char		*vlq_to_decim(t_vlq const vlq)
{
	//TODO placeholder: optimize for base_10 ? Or leave that to finding the topmost digits in lftoa ?

	return (vlq_to_anybase(vlq, DECIM));
}
*/

char			*ft_vlqtoa_base(t_vlq const vlq, char const *base)
{
	char	*result;
	char	*tmp;
	t_u32	radix;

	if (!vlq || !ft_is_valid_base(base) || (radix = ft_strlen(base)) < 2)
	{
		ft_putendl_fd("Invalid operand in vlqtoa_base.", 2);
		return (NULL);
	}
//	if (ft_strequ(base, DECIM))
//		return (vlq_to_decim(vlq));
	if (radix == 2 || radix == 4 || radix == 8 || radix == 16 ||
		radix == 32 || radix == 64 || radix == 128 || radix == 256)
	{
		result = vlq_to_binstr(vlq);		
		if (radix == 2 && !ft_strequ(base, BINAR))
			ft_str_csubstitute(result, "01", base);
		else if (radix != 2)
		{
			tmp = ft_str_base_to_base_expn(result, BINAR, base, ft_ilog2(radix));
			ft_strdel(&result);
			return (tmp);
		}
		return (result);
	}
	else
		return (vlq_to_anybase(vlq, base));
}
