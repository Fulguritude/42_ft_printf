/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 21:32:01 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/28 11:44:43 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_memalloc wipes memory with ft_bzero.
*/
char	*ft_strcnew(size_t size, char const c)
{
	char	*str;

	if (!(str = (char*)malloc(size + 1)))
		return (NULL);
	str[size] = '\0';
	ft_memset(str, c, size);
	return (str);
}
