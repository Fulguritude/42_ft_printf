/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbstr_to_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 02:56:36 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/07 03:06:17 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_nbstr_to_str(t_nbstr const ns, char const flag)
{
	char	*result;

	result = ft_strrev(ns.rev_mant);
	if (ns.neg == 2)
		ft_putendl_fd("Improper nbstr conversion error.", 2);
	else if (ns.neg)
		ft_strprepend("-", &result);
	else if (flag == ' ' && !ns.neg)
		ft_strprepend(" ", &result);
	else if (flag == '+' && !ns.neg)
		ft_strprepend("+", &result);
	return (result);
}
