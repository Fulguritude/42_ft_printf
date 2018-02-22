/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlsdel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 00:46:24 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/28 11:44:41 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strlsdel(char ***a_strls)
{
	int		i;

	if (a_strls && *a_strls)
	{
		i = 0;
		while ((*a_strls)[i])
		{
			ft_strdel((*a_strls) + i);
		}
		ft_memdel((void**)a_strls);
	}
}
