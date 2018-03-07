/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbstr_sub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 01:00:22 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/06 04:15:04 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		set_max_min(t_nbstr const a, t_nbstr const b,
							t_nbstr *max, t_nbstr *min)
{
	char	max_c;
	int		cmp;

	cmp = ft_nbstrcmp(a, b);
	max_c = cmp > 0 ? 'a' : 'b';
	*max = max_c == 'a' ? a : *max;
	*max = max_c == 'b' ? b : *max;
	*min = max_c == 'a' ? b : *min;
	*min = max_c == 'b' ? a : *min;
	return (max_c);
}

static void		do_sub(t_nbstr const max, t_nbstr const min, t_nbstr ns, char const *tmp)
{
	int			i;
	int			diff;
	t_u8		neg;

	i = max.digits;
	while (--i >= 0)
	{
		diff = ft_in_base(max.rev_mant[i], max.base) -
				ft_in_base(tmp[i], min.base) - neg;
		neg = diff < 0 ? 1 : 0;
		diff = diff < 0 ? diff + ns.base_n : diff;
		ns.rev_mant[i] = ns.base[diff];
	}
}

t_nbstr			ft_nbstr_sub(t_nbstr const a, t_nbstr const b)
{
	t_nbstr		ns;
	t_nbstr		max;
	t_nbstr		min;
	char		*tmp;
	char		max_c;

	max_c = set_max_min(a, b, &max, &min);
	ns = ft_nbstrnew(max.digits, max.base);
	tmp = ft_strpad_right(min.rev_mant, min.base[0], max.digits - min.digits);
	do_sub(max, min, ns, tmp);
	ft_strdel(&tmp);
	ns.digits = max.digits;
	while (ns.rev_mant[ns.digits - 1] == ns.base[0])
		--ns.digits;
	ns.rev_mant[ns.digits] = '\0';
	if (max_c != 'e')
		ns.neg = (max_c == 'a' && a.neg) || (max_c == 'b' && b.neg) ? 1 : 0;
	return (ns);
}
