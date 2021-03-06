/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:51 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/30 16:23:55 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*result;
	t_list	*cur_elem;

	if (!lst || !f)
		return (NULL);
	result = NULL;
	while (lst)
	{
		cur_elem = f(lst);
		if (!cur_elem)
		{
			ft_lstdel(&result, ft_delete);
			return (NULL);
		}
		ft_lstappend(&result, cur_elem);
		lst = lst->next;
	}
	return (result);
}
