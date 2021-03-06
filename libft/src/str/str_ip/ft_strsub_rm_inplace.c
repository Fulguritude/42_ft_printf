/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub_rm_inplace.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 16:51:06 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/07 17:42:16 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strsub_rm_inplace(char **a_str, t_u32 start, size_t len)
{
	t_u32	size;
	t_u32	i;

	if (!*a_str)
		return ;
	size = ft_strlen(*a_str);
	if (size <= start || size < start + len)
	{
		ft_putendl_fd("Invalid index pair given to strsub_rm_inplace", 2);
		return ;
	}
	i = 0;
	while (i < size - start - len)
	{
		(*a_str)[start + i] = (*a_str)[start + len + i];
		++i;
	}
	(*a_str)[start + i] = '\0';
}
