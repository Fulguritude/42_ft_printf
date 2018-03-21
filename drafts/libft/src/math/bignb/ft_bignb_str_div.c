/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bignb_str_div.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 03:40:40 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/14 19:34:56 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		setters_nbstr_div(t_bignb *v_nbstr, char mode)
{
	int			val_c;
	char const	*base;

	base = v_nbstr->base;
	if (mode == '0')
		v_nbstr->rev_ns[0] = base[0];
	else if (mode == '+' || mode == '-')
	{
		val_c = ft_in_base(v_nbstr->rev_ns[0], base);
		if (!(val_c != -1 && val_c < v_nbstr->radix - 1))			
			setters_nbstr_div(v_nbstr, 'e');
		v_nbstr->rev_ns[0] = mode == '+' ? base[val_c + 1] : base[val_c - 1];
	}
	else if (mode == 'd')
		ft_strntrim_left_inplace(&(v_nbstr->rev_ns), 1);
	else
		ft_putendl_fd("Unexpected error in nbstr_div:iterate_nbstr_digit", 2);
}

static void		do_div(t_bignb r, t_bignb d, t_bignb *a_q)
{
	t_bignb		new_q_val;
	t_bignb		tmp_ns;
	t_bignb		cur_q_x_d;

	ft_strpad_left_inplace(&(d.rev_ns), a_q->base[0], r.digits - d.digits -
			(ft_bignb_strcmp(r, d) < 0)); //replace by "ctrim 'base0'" below ?
	new_q_val = ft_bignbnew(1, a_q->base);
	cur_q_x_d = ft_bignbnew(1, a_q->base);
	while (ft_strlen(d.rev_ns) >= d.digits || ft_bignb_strcmp(r,d) > 0)
	{
		setters_nbstr_div(&new_q_val, '0');
		while (ft_in_base(new_q_val.rev_ns[0], a_q->base) < a_q->radix)
		{
			setters_nbstr_div(&new_q_val, '+');
			tmp_ns = ft_bignb_mul(d, new_q_val);
			if (ft_bignb_strcmp(tmp_ns, r) > 0)
			{
				ft_strdel(&(tmp_ns.rev_ns));
				setters_nbstr_div(&new_q_val, '-');
				ft_strprepend(new_q_val.rev_ns, &(a_q->rev_ns));
				tmp_ns = ft_bignb_sub(r, cur_q_x_d);
				ft_strdel(&(r.rev_ns));
				r = tmp_ns;
				ft_strdel(&(cur_q_x_d.rev_ns));
				break ;
			}
			ft_strdel(&(cur_q_x_d.rev_ns));
			cur_q_x_d = tmp_ns;
		}
		setters_nbstr_div(&d, 'd');
	}
	ft_strdel(&(new_q_val.rev_ns));
}

t_bignb			ft_bignb_str_div(t_bignb const r, t_bignb const d)
{
	t_bignb		q;
	t_bignb		tmp_r;
	t_bignb		tmp_d;

	tmp_r = r;
	tmp_d = d;
	tmp_r.rev_ns = ft_strdup(r.rev_ns);
	tmp_d.rev_ns = ft_strdup(d.rev_ns);
	q = ft_bignbnew(r.digits, r.base);
	if (r.radix != q.radix || ft_bignb_iszero(d))
		return (q);
	if (ft_bignb_strcmp(r,d) < 0 || ft_bignb_iszero(r))
		q.rev_ns[0] = q.base[0];
	else
		do_div(tmp_r, tmp_d, &q);
	ft_strdel(&(tmp_r.rev_ns));
	ft_strdel(&(tmp_d.rev_ns));
	q.digits = ft_strlen(q.rev_ns);
	q.neg = r.neg != d.neg;
	q.vlq = ft_atovlq(q.rev_ns, q.base);
	return (q);
}
