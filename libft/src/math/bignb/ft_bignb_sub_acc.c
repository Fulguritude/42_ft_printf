/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignb_sub_acc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 00:49:09 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/14 19:34:57 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Note that this function is made for speedy use, and there should be a
** subsequent call to bignb_vlq_updates_revns before using the revns.
** Works as usual substraction should, ((-a)-(-b)) should return (b - a).
*/
void					ft_bignb_sub_acc(t_bignb *acc, t_bignb const bn)
{
	t_bignb		tmp;

	tmp = bn;
	tmp.neg = !bn.neg;
	ft_bignb_add_acc(acc, tmp);
}
