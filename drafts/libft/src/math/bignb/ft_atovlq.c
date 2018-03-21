/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atovlq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 02:11:16 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/15 03:02:34 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_vlq		bin_atovlq(char const *a)
{
	t_vlq	result;
	char	*tmp;
	t_u32	size;
	t_u32	i;
	int		j;

	tmp = ft_strdup(a);
	ft_strctrim_left_inplace(&tmp, '0');
	ft_strpad_right_inplace(&tmp, '0', 63 - (ft_strlen(tmp) % 63));
	j = ft_strlen(tmp);
	size = j / 63;
	result = ft_vlqnew(size);
	i = 0;
	while (i < size)
		while (--j >= 0)
		{
			if (tmp[j] == '1')
				result[i] |= (0x1 << (j % 63));
			if (j % 63 == 0)
				++i; 
		}
	return (result);
}

/*
** nbstr in input are in normal order, not rev.
** leading + and - are ignored; internal + and - cause error.
*/
t_vlq				ft_atovlq(char const *a, char const *base)
{
	t_vlq	result;
	int		i;
	int		len;
	t_u64	val;

	if (!ft_is_valid_base(base))
	{
		ft_putendl_fd("Invalid base given to atovlq.", 2);
		return (NULL);
	}
	i = (a[0] == '+' || a[0] == '-') - 1;
	while (a[++i])
		if (ft_in_base(a[i], base) == -1)
		{
			ft_putendl("Digit and base mismatch in atovlq.");
			return (NULL);
		}
	if (ft_strequ(base, BINAR))
		return (bin_atovlq(a));
	i = (a[0] == '+' || a[0] == '-') - 1;
	len = ft_strlen(a);
	*result = 0;
	while (i < --len)
	{
		val = ft_in_base(a[len], base);
		ft_vlq_add_acc(&result, &val);
	}
	return (result);
}
