/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:36:34 by tduquesn          #+#    #+#             */
/*   Updated: 2017/12/12 19:47:38 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strappend(char **dest, char const *src)
{
	char	*tmp;

	tmp = ft_strjoin(*dest, src);
	ft_strdel(dest);
	*dest = tmp;
	return (*dest);
}
