/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrarrnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:08:22 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/28 11:44:36 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_ptrarrnew(t_u32 len)
{
	void	*result;

	if (!(result = ft_memalloc(sizeof(void*) * (len + 1))))
		return (NULL);
	return (result);
}
