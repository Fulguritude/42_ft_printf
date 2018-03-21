/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignb_str_mul.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 03:40:40 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/14 19:34:57 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		set_max_min(t_bignb const a, t_bignb const b,
							t_bignb *max, t_bignb *min)
{
	char	max_c;
	int		cmp;

	cmp = ft_bignb_strcmp(a, b);
	max_c = cmp > 0 ? 'a' : 'b';
	*max = max_c == 'a' ? a : *max;
	*max = max_c == 'b' ? b : *max;
	*min = max_c == 'a' ? b : *min;
	*min = max_c == 'b' ? a : *min;
}

static void		do_digit_mul(t_bignb *a_p, t_bignb max, char const c)
{
	t_bignb	tmp_ns;
	t_bignb	tmp_ns2;
	int		val_ib;
	int		i;

	val_ib = ft_in_base(c, a_p->base);
	i = 0;
	tmp_ns = *a_p;
	tmp_ns.rev_ns = ft_strdup(max.rev_ns);
	while (i < val_ib)
	{
		tmp_ns2 = ft_bignb_add(tmp_ns, *a_p); //TODO recode more optimally
		ft_strdel(&(a_p->rev_ns));
		a_p->rev_ns = tmp_ns2.rev_ns;
		++i;
	}
	ft_strdel(&(tmp_ns.rev_ns));
}

static void		do_mul(t_bignb const max, t_bignb const min, t_bignb *a_p)
{
	t_bignb	tmp_ns;
	t_bignb	tmp_ns2;
	char	c;
	int		i;

	i = 0;
	tmp_ns = max;
	while ((c = min.rev_ns[i]))
	{
		tmp_ns.rev_ns = ft_strcnew(1, c);
		do_digit_mul(&tmp_ns, max, c);
		ft_strpad_left_inplace(&(tmp_ns.rev_ns), max.base[0], i);
		tmp_ns2 = ft_bignb_add(*a_p, tmp_ns);
		ft_strdel(&(a_p->rev_ns));
		ft_strdel(&(tmp_ns.rev_ns));
		a_p->rev_ns = tmp_ns2.rev_ns;
		++i;
	}
}

t_bignb			ft_bignb_str_mul(t_bignb const a, t_bignb const b)
{
	t_bignb		p;
	t_bignb		max;
	t_bignb		min;

	p = ft_bignbnew(1, a.base);
	if (a.radix != b.radix)
		return (p);
	if (ft_bignb_iszero(a) || ft_bignb_iszero(b))
	{
		p.neg = 0;
		return (p);
	}
	set_max_min(a, b, &max, &min);
	do_mul(max, min, &p);
	p.digits = ft_strlen(p.rev_ns);
	p.neg = a.neg != b.neg && !ft_bignb_iszero(p);
	ft_bignb_revns_updates_vlq(&p);
	return (p);
}
