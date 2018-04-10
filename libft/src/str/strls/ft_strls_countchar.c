/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strls_countchar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 01:54:20 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/30 18:56:41 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_u32		ft_strls_countchar(const char **strls, const char c)
{
	t_u32		i;
	t_u32		count;

	if (!strls)
		return (0);
	count = 0;
	i = 0;
	while (strls[i])
	{
		count += ft_str_countchar(strls[i], c);
		i++;
	}
	return (count);
}
