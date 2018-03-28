/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_abstractval_as_hex.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 17:39:30 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/25 17:39:34 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_vlq_abstractval_as_hex(t_vlq const vlq)
{
	char		*result;
	char		*tmp;
	t_u32		i;
	t_u32		len;

	if (!vlq)
		return (ft_strdup("(null_vlq)"));
	if (vlq[0] == 0)
		return (ft_strdup("0"));
	else if (vlq[0] == _MSB_)
		return ("Invalid vlq in vlq_abstractval_as_hex");
	result = NULL;
	len = ft_vlqlen(vlq);
	i = 0;
	while (i < len)
	{
		tmp = ft_itoa_base(NOT_MSB(vlq[i]), BINAR);
		ft_strpad_left_inplace(&tmp, '0', 63 - ft_strlen(tmp));
		ft_strappend(&result, tmp);
		ft_strdel(&tmp);
		++i;
	}
	ft_strctrim_left_inplace(&result, '0');
	tmp = ft_str_base_to_base_expn(result, BINAR, HXLOW, 4);
	ft_strdel(&result);
	result = tmp;
	return (result);
}
