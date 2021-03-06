/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:32:02 by tduquesn          #+#    #+#             */
/*   Updated: 2017/12/01 19:22:21 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p;
	size_t	i;

	if (c == '\0')
		return ((char*)s + ft_strlen(s));
	p = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			p = (char*)s + i;
		i++;
	}
	return (p);
}
