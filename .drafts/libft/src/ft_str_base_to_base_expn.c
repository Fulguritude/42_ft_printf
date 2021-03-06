/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_base_to_base_expn.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 17:58:03 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/25 17:58:06 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*convert_base_to_basen(char const *str, char const *base_f,
									char const *base_t, t_u32 expn)
{
	char	*result;
	char	*tmp;
	t_u32	size;
	t_u32	i;
	t_u32	j;

	if ((i = ft_strlen(str) % expn) == 0)
		tmp = ft_strdup(str + (str[0] == '+' || str[0] == '-'));
	else
		tmp = ft_strpad_left(str + (str[0] == '+' || str[0] == '-'),
								base_f[0], expn - i);
	size = ft_strlen(tmp) / expn;
	result = ft_strnew(size);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < expn)
		{
			result[i] += ft_in_base(tmp[i * expn + j], base_f) * 
							ft_ipowi(ft_strlen(base_f), expn - 1 - j);
			++j;
		}
		result[i] = base_t[(t_u8)(result[i])];
		++i;
	}
	ft_strdel(&tmp);
	return (result);
}

char		*ft_str_base_to_base_expn(char const *str, char const *base_f,
									char const *base_t, t_u32 expn)
{
	if (!str || !base_f || !base_t || !ft_is_valid_nbstr_in_base(str, base_f) ||
		!ft_is_valid_base(base_t) || expn == 0)
	{
		ft_putendl_fd("Invalid operand given to str_base_to_base_expn.", 2);
		return (NULL);
	}
	if (ft_ipowi(ft_strlen(base_f), expn) != ft_strlen(base_t))
	{
		ft_putendl_fd("Invalid exponent in str_base_to_base_expn.", 2);
		return (NULL);
	}
	if (expn == 1)
		return (ft_strdup(str));
	return (convert_base_to_basen(str, base_f, base_t, expn));
}


