/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ipowi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 11:27:32 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:14:33 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

t_u64	ft_ipowi(t_u32 nb, t_u8 power)
{
	int		i;
	t_u64	result;

	result = 1;
	i = 0;
	while (++i <= power)
	{
		if (ULONG_MAX / nb < result)
			return (0);
		result *= nb;
	}
	return (result);
}
