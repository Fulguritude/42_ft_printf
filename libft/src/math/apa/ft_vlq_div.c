/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_div.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 16:37:08 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/15 16:37:12 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vlq		ft_vlq_div(t_vlq const num, t_vlq const den)
{
	t_vlq	result;

	result = num;
	ft_vlq_divmod(num, den, &result, NULL);
	return (result);
}
