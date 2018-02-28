/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 02:55:30 by fulguritu         #+#    #+#             */
/*   Updated: 2018/02/28 03:06:36 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


#include <stdio.h>


char	*ft_strreplace(char const *str, char const *sub, char const *rep)
{
	char	**strls;
	char	*result;

	strls = ft_strsplitstr(str, sub);
	result = ft_strlsjoin((const char **)strls, rep);
	ft_strlsdel(&strls);
	return (result);
}
