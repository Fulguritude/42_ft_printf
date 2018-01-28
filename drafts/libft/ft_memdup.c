/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:53 by tduquesn          #+#    #+#             */
/*   Updated: 2017/12/01 19:35:07 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(const void *s, size_t n)
{
	void	*dup;

	if (!(dup = malloc(n)))
		return (NULL);
	dup = ft_memcpy(dup, s, n);
	return (dup);
}
