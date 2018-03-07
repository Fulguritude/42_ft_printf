/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbstr_iszero.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 03:40:40 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/06 06:40:19 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_nbstr_iszero(t_nbstr const ns)
{
	int		i;

	if (ns.rev_mant[0] == ns.base[0] && ns.rev_mant[1] == '\0')
		return (1);
	i = 0;
	while (ns.rev_mant[i] == ns.base[0])
		if (ns.rev_mant[++i] != ns.base[0] && ns.rev_mant != '\0')
			return (0);
	return (2);
}
