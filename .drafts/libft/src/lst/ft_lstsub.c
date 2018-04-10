/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 22:15:03 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/28 11:44:35 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstsub(t_list *lst, t_u32 start, t_u32 len)
{
	t_list	*result;
	t_list	*lst_tail;

	if (!lst || start + len >= ft_lstsize(lst))
		return (NULL);
	if (!(result = ft_lstget(lst, start)))
		return (NULL);
	result = ft_lstcpy(result);
	lst_tail = ft_lstget(result, len);
	ft_lstdel(&lst_tail, &ft_delete);
	ft_lstget(result, len - 1)->next = NULL;
	return (result);
}
