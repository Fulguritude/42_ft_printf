/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:32:01 by tduquesn          #+#    #+#             */
/*   Updated: 2017/12/01 19:23:55 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	min;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	min = s1_len < s2_len ? s1_len : s2_len;
	min = n < min + 1 ? n : min + 1;
	return (ft_memcmp(s1, s2, min));
}
