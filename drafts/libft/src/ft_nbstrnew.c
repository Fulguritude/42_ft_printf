/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbstrnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 02:46:09 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/06 02:54:32 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_nbstr				ft_nbstrnew(t_u32 size, char const *base)
{
	t_nbstr		result;

	result.digits = size;
	result.rev_mant = ft_strcnew(size, base[0]);
	result.base = base;
	result.base_n = ft_strlen(base);
	result.neg = 2;
	return (result);
}
