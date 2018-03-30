/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignbdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 16:11:39 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/28 16:18:15 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bignb		ft_bignbdup(t_bignb const bn)
{
	t_bignb		result;

	result = bn;
	result.vlq = bn.vlq ? ft_vlqdup(bn.vlq) : NULL;
	result.rev_ns = bn.rev_ns ? ft_strdup(bn.rev_ns) : NULL;
	return (result);
}
