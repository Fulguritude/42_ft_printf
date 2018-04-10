/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strprepend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:36:34 by tduquesn          #+#    #+#             */
/*   Updated: 2017/12/12 19:47:38 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strprepend(char const *src, char **dest)
{
	char	*tmp;

	tmp = ft_strjoin(src, *dest);
	ft_strdel(dest);
	*dest = tmp;
	return (*dest);
}
