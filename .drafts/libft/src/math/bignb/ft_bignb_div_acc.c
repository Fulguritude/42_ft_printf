/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignb_div_acc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 00:49:09 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/14 19:34:56 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					ft_bignb_div_acc(t_bignb *acc, t_bignb const bn)
{
	t_vlq	tmp;

	tmp = ft_vlq_div(acc->vlq, bn.vlq);
	ft_vlqdel(&(acc->vlq));
	acc->vlq = tmp;
	acc->neg = (acc->neg != bn.neg);
}
