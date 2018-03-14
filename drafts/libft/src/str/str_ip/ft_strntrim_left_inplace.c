/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strntrim_left_inplace.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:00:47 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/06 17:15:12 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strntrim_left_inplace(char **a_str, size_t n)
{
	char	*tmp;

	tmp = ft_strdup(*a_str + n);
	ft_strdel(a_str);
	*a_str = tmp;
}
