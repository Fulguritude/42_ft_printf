/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignb_revns_updates_vlq.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 05:45:48 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/15 05:51:01 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_bignb_revns_updates_vlq(t_bignb *bn)
{
	char	*notrev;

	if (!bn->rev_ns)
	{
		ft_putendl_fd("Empty nbstr field in bignb_revns_updates_vlq arg.", 2);
		return ;
	}
	ft_vlqdel(&(bn->vlq));
	notrev = ft_strrev(bn->rev_ns);
	bn->vlq = ft_atovlq(notrev, bn->base);
	ft_strdel(&notrev);
}
