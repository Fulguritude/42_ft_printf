/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignb_to_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 02:56:36 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/14 19:34:57 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Remove safety check ?
*/
char	*ft_bignb_to_str(t_bignb const bn)
{
	char	*result;
	t_vlq	check;

	result = ft_strrev(bn.rev_ns);
	check = ft_atovlq(result, bn.base);
	if (ft_vlqcmp(check, bn.vlq) != 0)
		ft_putendl_fd("Incoherent argument given to bignb_to_str.", 2);	
	ft_vlqdel(&check);
	if (bn.neg == 2)
		ft_putendl_fd("Improper nbstr error in bignb_to_str.", 2);
	if (bn.neg)
		ft_strprepend("-", &result);
	return (result);
}
