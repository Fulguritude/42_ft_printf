/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlqdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 03:09:57 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/17 03:12:06 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vlq		ft_vlqdup(t_vlq const vlq)
{
	return (ft_memdup(vlq, sizeof(t_u64) * ft_vlqlen(vlq)));
}