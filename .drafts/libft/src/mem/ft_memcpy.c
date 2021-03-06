/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:52 by tduquesn          #+#    #+#             */
/*   Updated: 2017/12/01 19:15:49 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest || !src)
	{
		ft_putendl_fd("null operand given to ft_memcpy.", 2);
		return (NULL);
	}
	i = 0;
	while (i < n)
	{
		((t_u8*)dest)[i] = ((t_u8*)src)[i];
		i++;
	}
	return (dest);
}
