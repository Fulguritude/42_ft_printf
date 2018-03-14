/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:32:02 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/28 13:31:37 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(const char *s)
{
	t_u32	i;
	t_u32	len;
	char	*rev;

	if (!s)
		return (NULL);
	rev = ft_strdup(s);
	len = ft_strlen(s);
	i = 0;
	while (i < len / 2)
	{
		ft_swap(&rev[i], &rev[len - 1 - i], sizeof(char));
		i++;
	}
	return (rev);
}
