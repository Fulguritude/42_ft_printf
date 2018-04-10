/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrarrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 17:19:36 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/28 11:44:36 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_u32		ft_ptrarrlen(const void *a_ptrarr)
{
	t_u32		i;

	if (!a_ptrarr)
		return (0);
	i = 0;
	while (((t_u8**)a_ptrarr)[i])
		i++;
	return (i);
}
