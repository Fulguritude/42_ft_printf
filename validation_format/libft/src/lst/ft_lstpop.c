/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:25:10 by tduquesn          #+#    #+#             */
/*   Updated: 2017/12/12 19:37:29 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstpop(t_list **alst, t_u32 index, void (*del)(void *, size_t))
{
	t_list	*tmp_elem;
	t_list	*start;
	t_u32	i;

	if (!alst || !*alst || !del)
		return ;
	if (index == 0)
	{
		tmp_elem = (*alst)->next;
		ft_lstdelone(alst, del);
		*alst = tmp_elem;
		return ;
	}
	start = *alst;
	i = 0;
	while (++i < index)
		*alst = (*alst)->next;
	tmp_elem = (*alst)->next->next;
	ft_lstdelone(&((*alst)->next), del);
	(*alst)->next = tmp_elem;
	*alst = start;
}
