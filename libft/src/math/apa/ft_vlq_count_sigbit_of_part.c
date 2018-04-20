/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_count_sigbit_of_part.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 02:56:05 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/20 02:56:10 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns the number of significant bits in a single index of a vlq, ignoring
** the MSB used for the vlq format (MSB is not a significant value).
*/

t_u8			ft_vlq_count_sigbit_of_part(t_u64 vlq_p)
{
	t_u64	tmp;
	t_u8	i;

	tmp = NOT_MSB(vlq_p);
	i = 0;
	while (tmp)
	{
		tmp >>= 1;
		++i;
	}
	return (i);
}
