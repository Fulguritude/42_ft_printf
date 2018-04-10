/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atobignb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 15:48:07 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/14 19:34:55 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bignb		ft_atobignb(char const *a, char const *base)
{
	t_bignb		result;
	char		*tmp;
	int			i;

	if (!ft_is_valid_base(base))
		return (ft_bignbnew(0, "Invalid base given to atobignb."));
	i = (a[0] == '+' || a[0] == '-') - 1;
	while (a[++i])
		if (ft_in_base(a[i], base) == -1)
			return (ft_bignbnew(0, "Digit and base mismatch in atobignb."));
	result = ft_bignbnew(0, base);
	result.vlq = ft_atovlq(a, base);
	result.neg = (a[0] == '-');
	tmp = ft_strdup((a[0] == '+' || a[0] == '-') ? a + 1 : a); 
	ft_strrev_inplace(&tmp);
//ft_printf("atobn tmp %s and %p\n", tmp, tmp);
	result.rev_ns = tmp;
	result.digits = ft_strlen(tmp);
	return (result);
}
