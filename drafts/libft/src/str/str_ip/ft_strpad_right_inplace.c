/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpad_right_inplace.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 19:23:07 by tduquesn          #+#    #+#             */
/*   Updated: 2018/02/20 21:38:14 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strpad_right_inplace(char **a_str, char const c, t_u32 len)
{
	char	*tmp;

	tmp = ft_strpad_right(*a_str, c, len);
	ft_strdel(a_str);
	*a_str = tmp;
}
