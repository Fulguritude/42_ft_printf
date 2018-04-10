/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignb_add_acc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 00:49:09 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/14 19:34:55 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Note that this function is made for speedy use, and there should be a
** subsequent call to bignb_vlq_updates_revns before using the rev_ns.
*/
void					ft_bignb_add_acc(t_bignb *acc, t_bignb const bn)
{
	t_vlq	tmp;
	char	max;
	int		signs;

	if (!acc || !(acc->vlq) || !bn.vlq)
	{
		ft_putendl_fd("Invalid operand to bignb_add_acc.", 2);
		return ;
	}
	if ((signs = acc->neg != bn.neg))
		tmp = ft_vlq_sub(acc->vlq, bn.vlq);
	else
		tmp = ft_vlq_add(acc->vlq, bn.vlq);
	max = ft_vlqcmp(acc->vlq, bn.vlq) < 0 ? 'b' : 'a';
	if ((acc->neg && bn.neg) ||
		(signs && ((max == 'a' && acc->neg) || (max == 'b' && bn.neg))))
		acc->neg = 1;
	else
		acc->neg = 0;
	ft_vlqdel(&(acc->vlq));
	acc->vlq = tmp;
}
