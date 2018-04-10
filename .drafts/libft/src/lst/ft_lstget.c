/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 16:30:26 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/28 14:18:35 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstget(t_list *lst, t_u32 n)
{
	t_u32		i;
	t_list		*result;

	if (!lst)
		return (NULL);
	result = lst;
	i = 0;
	while (i < n)
	{
		result = result->next;
		if (!result)
			return (NULL);
		i++;
	}
	return (result);
}
