/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ipowi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 11:27:32 by tduquesn          #+#    #+#             */
/*   Updated: 2017/09/05 11:37:10 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ipowi(int nb, int power)
{
	int		i;
	int		result;

	result = 1;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	i = 0;
	while (++i <= power)
		result *= nb;
	return (result);
}
