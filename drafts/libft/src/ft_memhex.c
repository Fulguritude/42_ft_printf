/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memhex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 01:25:31 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/28 11:44:36 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memhex(const void *s, size_t n)
{
	size_t	i;
	size_t	j;
	char	*new_str;
	char	*hex_base;

	if (!s)
		return (NULL);
	hex_base = "0123456789ABCDEF";
	if (!(new_str = malloc(n * 2 + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (i < n)
	{
		new_str[j++] = hex_base[((t_u8*)s)[i] / 16];
		new_str[j++] = hex_base[((t_u8*)s)[i] % 16];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
