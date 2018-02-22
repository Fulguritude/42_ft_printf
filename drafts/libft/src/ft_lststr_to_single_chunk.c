/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lststr_to_single_chunk.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 02:33:57 by fulguritu         #+#    #+#             */
/*   Updated: 2018/01/28 18:32:40 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static void	ft_lstmemfold(t_list *lst, size_t *size_acc)
{
	if (!size_acc)
		return ;
	while (lst)
	{
		*size_acc += lst->content_size;
		lst = lst->next;
	}
}

static void	ft_pcat(char **a, char **b)
{
	
}*/

t_list		*ft_lststr_to_single_chunk(t_list *lst)
{
	char	*res_str;
	size_t	tot_size;

	if (!lst || !(res_str = ft_strnew(0)))
		return (NULL);
	tot_size = 0;
	ft_lstmemfold(lst, &tot_size);
	ft_lstfold(lst, &res_str, ft_pcat);
	return (ft_lstnew_no_copy(res_str, tot_size));
}
