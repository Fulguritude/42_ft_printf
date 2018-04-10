/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uconvert_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:31:46 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/28 11:44:31 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uconvert_base(const char *n, const char *base_f, const char *base_t)
{
	int		i;
	t_u64	nb;
	int		symbols_bf;
	int		symbols_bt;
	char	*new_n;

	if (!n || !base_f || !base_t)
		return (NULL);
	symbols_bf = ft_in_base('\0', base_f);
	symbols_bt = ft_in_base('\0', base_t);
	if (!ft_is_valid_base(base_f) || !ft_is_valid_base(base_t) ||
		!n || !n[0] || symbols_bf <= 1 || symbols_bt <= 1)
		return (NULL);
	i = -1;
	while (n[++i])
		if (ft_in_base(n[i], base_f) == -1)
			return (NULL);
	nb = (t_u64)ft_atoui_base(n, base_f);
	new_n = ft_uitoa_base(nb, base_t);
	return (new_n);
}
