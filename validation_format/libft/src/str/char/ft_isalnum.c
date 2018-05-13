/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:47 by tduquesn          #+#    #+#             */
/*   Updated: 2018/05/12 17:16:09 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

inline int		ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}