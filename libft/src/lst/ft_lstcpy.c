/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 22:03:30 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/28 11:44:33 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstelemcpy(t_list *elem)
{
	if (!elem)
		return (NULL);
	return (ft_lstnew(elem->content, elem->content_size));
}

t_list			*ft_lstcpy(t_list *lst)
{
	if (!lst)
		return (NULL);
	return (ft_lstmap(lst, &ft_lstelemcpy));
}
