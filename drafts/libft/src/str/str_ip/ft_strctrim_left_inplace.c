/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strctrim_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:00:47 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/06 17:15:09 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strctrim_left_inplace(char **a_str, char const c)
{
	int		i;
	char	*tmp;

	if ((*a_str)[0] != c)
		return ;
	i = 0;
	while ((*a_str)[i] == c)
		++i;
	tmp = ft_strdup((*a_str) + i);
	ft_strdel(a_str);
	*a_str = tmp;
}
