/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignb_mul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 07:56:16 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/20 08:00:13 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bignb					ft_bignb_mul(t_bignb const a, t_bignb const b)
{
	t_bignb		result;

	result = a;
	result.vlq = ft_vlq_mul(a.vlq, a.vlq);
	result.neg = (a.neg != b.neg);
	ft_bignb_vlq_updates_revns(&result);
	return (result);
}
