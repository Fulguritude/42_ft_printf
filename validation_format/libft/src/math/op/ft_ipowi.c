/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ipowi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 11:27:32 by tduquesn          #+#    #+#             */
/*   Updated: 2017/09/05 11:37:10 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
