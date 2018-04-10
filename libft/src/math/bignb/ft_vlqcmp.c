/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlqcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 06:18:38 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/15 06:26:13 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_vlqcmp(t_vlq const a, t_vlq const b)
{
	long	diff;
	t_u32	a_len;
	t_u32	i;

	if ((!NOT_MSB(a[0]) && MSB(a[0])) || (!NOT_MSB(b[0]) && MSB(b[0])))
	{
		ft_putendl_fd("Improper vlq in vlqcmp.", 2);
		return (0);
	}
	a_len = ft_vlqlen(a);
	diff = a_len - ft_vlqlen(b);
	if (diff == 0)
	{
		i = 0;
		while (i < a_len && a[i] == b[i])
			++i;
		return (i == a_len ? 0 : NOT_MSB(a[i]) - NOT_MSB(b[i]));
	}
	else
		return (diff);
}
