/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlqtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 07:05:37 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/15 07:22:27 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns the vlq without its leading parts == _MSB_ which contain no info.
** This version reallocates to avoid future problems with free on *a_vlq.
*/ 
void			ft_vlqtrim(t_vlq *a_vlq)
{
	int		i;
	long	len;
	t_vlq	tmp;

	if (a_vlq)
		if (*a_vlq)
		{
			len = ft_vlqlen(*a_vlq);
			i = -1;
			while (MSB((*a_vlq)[++i]))
				if (NOT_MSB((*a_vlq)[i]))
					break ;
			if (i > 0)
			{
				tmp = ft_vlqnew(len - i);
				while (--len >= i)
					tmp[len - i] |= NOT_MSB((*a_vlq)[len]);
				ft_vlqdel(a_vlq);
				*a_vlq = tmp;
			}
		}
}
