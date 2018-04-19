/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace_inplace.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 03:17:43 by fulguritu         #+#    #+#             */
/*   Updated: 2018/02/28 03:21:22 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strreplace_inplace(char **a_str, char const *sub, char const *rep)
{
	char	*tmp;

	if (a_str)
		if (*a_str && sub && rep)
		{
			if (ft_stristr(*a_str, sub) == -1)
				return ;
			tmp = ft_strreplace(*a_str, sub, rep);
			ft_strdel(a_str);
			*a_str = tmp;
		}
}
