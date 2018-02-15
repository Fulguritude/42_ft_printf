/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:32:01 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/28 11:44:43 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_memalloc wipes memory with ft_bzero.
*/
char	*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = (char*)ft_memalloc(size + 1)))
		return (NULL);
	return (str);
}
