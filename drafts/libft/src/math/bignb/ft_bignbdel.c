/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignbdel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 04:14:20 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/15 04:14:28 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_bignbdel(t_bignb *a_bn)
{
	ft_vlqdel(&(a_bn->vlq));
	ft_strdel(&(a_bn->rev_ns));
	a_bn->neg = 3;
	a_bn->digits = -1;
	a_bn->radix = -1;
	a_bn->base = NULL;
}
