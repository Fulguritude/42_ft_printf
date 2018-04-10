/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignb_iszero.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 03:40:40 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/14 19:34:56 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** This function accepts untrimmed rev_ns, but not untrimmed vlq.
*/
int				ft_bignb_iszero(t_bignb const bn)
{
	int		i;
	t_u8	iszero;

	if (!bn.rev_ns || !bn.vlq)
		return (0);
	iszero = 0;
	if (bn.rev_ns[0] == bn.base[0] && bn.rev_ns[1] == '\0')
		iszero = 1;
	if (iszero && !(bn.vlq[0] == 0))
	{
		ft_putendl_fd("Incoherence in input to bignb_iszero.", 2);
		return (0);
	}
	else if (iszero)
		return (1);
	i = 0;
	while (bn.rev_ns[i] == bn.base[0])
		if (bn.rev_ns[++i] != bn.base[0] && bn.rev_ns != '\0')
			return (0);
	return (2);
}
