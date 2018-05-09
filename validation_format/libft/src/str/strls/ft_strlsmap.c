/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlsmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 21:32:00 by tduquesn          #+#    #+#             */
/*   Updated: 2018/03/11 13:32:06 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_strlsmap(char const **strls, char *(*f)(char const *))
{
	t_u32	i;
	char	**result;

	if (!strls || !*strls || !f ||
		!(result = ft_ptrarrnew(ft_ptrarrlen(strls))))
		return (NULL);
	i = 0;
	while (strls[i])
	{
		result[i] = (*f)(strls[i]);
		++i;
	}
	return (result);
}
