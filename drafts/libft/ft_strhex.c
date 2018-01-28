/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strhex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 00:44:37 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/28 11:44:40 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strhex(const char *str)
{
	size_t	i;
	size_t	j;
	char	*new_str;
	char	*hex_base;

	if (!str)
		return (NULL);
	hex_base = "0123456789ABCDEF";
	if (!(new_str = malloc(ft_strlen(str) * 2 + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		new_str[j++] = hex_base[(t_u8)str[i] / 16];
		new_str[j++] = hex_base[(t_u8)str[i] % 16];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
