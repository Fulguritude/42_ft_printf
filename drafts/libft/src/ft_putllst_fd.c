/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putllst_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:55 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/28 11:44:37 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putllst_fd(t_list *lst, int fd)
{
	while (lst)
	{
		ft_putllstelem_fd(lst, fd);
		ft_putchar_fd('\n', fd);
		lst = lst->next;
	}
}
