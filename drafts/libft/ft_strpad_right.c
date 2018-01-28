/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpad_right.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 04:24:22 by tduquesn          #+#    #+#             */
/*   Updated: 2018/01/28 01:31:52 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpad_right(const char *s, const char c, t_u32 n)
{
	t_u32	i;
	t_u32	len;
	t_u32	totlen;
	char	*result;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	totlen = n + len;
	if (!(result = ft_strnew(totlen)))
		return (NULL);
	ft_strlcpy(result, s, len + 1);
	i = len;
	while (i < totlen)
		result[i++] = c;
	return (result);
}
