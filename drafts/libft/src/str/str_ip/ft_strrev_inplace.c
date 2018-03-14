/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev_inplace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 05:57:36 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/06 06:00:12 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_strrev_inplace(char **a_str)
{
	char	*tmp;

	tmp = ft_strrev(*a_str);
	ft_strdel(a_str);
	*a_str = tmp;
}
