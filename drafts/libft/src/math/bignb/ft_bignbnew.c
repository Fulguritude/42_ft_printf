/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignbnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 02:46:09 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/14 19:34:57 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bignb				ft_bignbnew(t_u32 size, char const *base)
{
	t_bignb		result;

	result.digits = size;
	result.vlq = size > 0 ? ft_vlqnew(1) : NULL;
	result.rev_ns = size > 0 ? ft_strcnew(size, base[0]) : NULL;
	result.base = base;
	result.radix = ft_strlen(base);
	result.neg = 2;
	return (result);
}
