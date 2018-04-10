/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignb_sub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 00:49:09 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/14 19:34:57 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Note that this function is not made for speedy use.
*/
t_bignb					ft_bignb_sub(t_bignb const a, t_bignb const b)
{
	t_bignb		tmp;
	t_bignb		result;

	tmp = b;
	tmp.neg = !b.neg;
	result = ft_bignb_add(a, tmp);
	return (result);
}
