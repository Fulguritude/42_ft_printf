/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strntrim_right_inplace.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:21:37 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/06 17:25:42 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strntrim_right_inplace(char **a_str, size_t n)
{
	*a_str[ft_strlen(*a_str) - n] = '\0';
}
