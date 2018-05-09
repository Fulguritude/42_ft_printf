/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:49 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/28 11:44:33 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd(t_list **alst, t_list *new_elem)
{
	if (!alst || !new_elem)
		return ;
	if (!*alst)
	{
		*alst = new_elem;
		return ;
	}
	new_elem->next = *alst;
	*alst = new_elem;
}
