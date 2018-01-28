/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putllstelem_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:55 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/28 11:44:37 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putllstelem_fd(t_list *elem, int fd)
{
	if (elem && elem->content)
		write(fd, elem->content, elem->content_size);
}
