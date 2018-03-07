/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbstr_mul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 03:40:40 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/06 06:40:19 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		set_max_min(t_nbstr const a, t_nbstr const b,
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
}

static void		do_digit_mul(t_nbstr *a_p, t_nbstr max, char const c)
{
	t_nbstr	tmp_ns;
	t_nbstr	tmp_ns2;
	int		val_ib;
	int		i;

	val_ib = ft_in_base(c, a_p->base);
	i = 0;
	tmp_ns = *a_p;
	tmp_ns.rev_mant = ft_strdup(max.rev_mant);
	while (i < val_ib)
	{
		tmp_ns2 = ft_nbstr_add(tmp_ns, *a_p); //TODO recode more optimally
		ft_strdel(&(a_p->rev_mant));
		a_p->rev_mant = tmp_ns2.rev_mant;
		++i;
	}
	ft_strdel(&(tmp_ns.rev_mant));
}

static void		do_mul(t_nbstr const max, t_nbstr const min, t_nbstr *a_p)
{
	t_nbstr	tmp_ns;
	t_nbstr	tmp_ns2;
	char	c;
	int		i;

	i = 0;
	tmp_ns = max;
	while ((c = min.rev_mant[i]))
	{
		tmp_ns.rev_mant = ft_strcnew(1, c);
		do_digit_mul(&tmp_ns, max, c);
		ft_strpad_left_inplace(&(tmp_ns.rev_mant), max.base[0], i);
		tmp_ns2 = ft_nbstr_add(*a_p, tmp_ns);
		ft_strdel(&(a_p->rev_mant));
		ft_strdel(&(tmp_ns.rev_mant));
		a_p->rev_mant = tmp_ns2.rev_mant;
		++i;
	}
}

t_nbstr			ft_nbstr_mul(t_nbstr const a, t_nbstr const b)
{
	t_nbstr		p;
	t_nbstr		max;
	t_nbstr		min;

	p = ft_nbstrnew(1, a.base);
	if (a.base_n != b.base_n)
		return (p);
	if (ft_nbstr_iszero(a) || ft_nbstr_iszero(b))
	{
		p.neg = 0;
		return (p);
	}
	set_max_min(a, b, &max, &min);
	do_mul(max, min, &p);
	p.digits = ft_strlen(p.rev_mant);
	p.neg = a.neg != b.neg && !ft_nbstr_iszero(p);
	return (p);
}
