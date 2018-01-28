/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdivide.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 01:50:05 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/28 11:44:40 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strdivide(const char *str, size_t n)
{
	char	**strls;
	int		lines;
	size_t	len;
	size_t	i;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	lines = len % n == 0 ? len / n : len / n + 1;
	if (lines == 0 || !(strls = (char**)malloc(sizeof(char*) * (lines + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (i + n < len)
			strls[i / n] = ft_strsub(str, i, n);
		else
			strls[i / n] = strdup(str + i);
		i += n;
	}
	strls[lines] = NULL;
	return (strls);
}
