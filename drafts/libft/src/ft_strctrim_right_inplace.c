/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strctrim_right_inplace.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 17:16:15 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/06 17:25:49 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strctrim_right_inplace(char **a_str, char const c)
{
	int 	i;

	i = ft_strlen(*a_str) - 1;
	while (*a_str[i] == c)
		--i;
	*a_str[i + 1] = '\0';
}
