/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:47 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/28 11:44:32 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_in_base(char c, const char *base)
{
	int i;
	int index;

	index = -1;
	if (!base)
		return (index);
	i = -1;
	while (base[++i])
		if (base[i] == c)
			index = i;
	if (c == '\0')
		return (i);
	else
		return (index);
}
