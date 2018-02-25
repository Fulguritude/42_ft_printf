/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digits_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:46 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/28 11:44:32 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_digits_base(intmax_t n, int base)
{
	int		i;

	if (base < 1)
		return (-1);
	if (base == 1)
		return (n);
	if (n == 0)
		return (1);
	else
	{
		i = 0;
		while (n != 0)
		{
			i++;
			n /= base;
		}
	}
	return (i);
}
