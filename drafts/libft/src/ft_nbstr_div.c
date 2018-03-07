/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbstr_div.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 03:40:40 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/06 06:40:19 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		setters_nbstr_div(t_nbstr *v_nbstr, char mode)
{
	int			val_c;
	char const	*base;

	base = v_nbstr->base;
	if (mode == '0')
		v_nbstr->rev_mant[0] = base[0];
	else if (mode == '+' || mode == '-')
	{
		val_c = ft_in_base(v_nbstr->rev_mant[0], base);
		if (!(val_c != -1 && val_c < v_nbstr->base_n - 1))			
			setters_nbstr_div(v_nbstr, 'e');
		v_nbstr->rev_mant[0] = mode == '+' ? base[val_c + 1] : base[val_c - 1];
	}
	else if (mode == 'd')
		ft_strntrim_left_inplace(&(v_nbstr->rev_mant), 1);
	else
		ft_putendl_fd("Unexpected error in nbstr_div:iterate_nbstr_digit", 2);
}

static void		do_div(t_nbstr r, t_nbstr d, t_nbstr *a_q)
{
	t_nbstr		new_q_val;
	t_nbstr		tmp_ns;
	t_nbstr		cur_q_x_d;

	ft_strpad_left_inplace(&(d.rev_mant), a_q->base[0], r.digits - d.digits -
			(ft_nbstrcmp(r, d) < 0)); //replace by "ctrim 'base0'" below ?
	new_q_val = ft_nbstrnew(1, a_q->base);
	cur_q_x_d = ft_nbstrnew(1, a_q->base);
	while (ft_strlen(d.rev_mant) >= d.digits || ft_nbstrcmp(r,d) > 0)
	{
		setters_nbstr_div(&new_q_val, '0');
		while (ft_in_base(new_q_val.rev_mant[0], a_q->base) < a_q->base_n)
		{
			setters_nbstr_div(&new_q_val, '+');
			tmp_ns = ft_nbstr_mul(d, new_q_val);
			if (ft_nbstrcmp(tmp_ns, r) > 0)
			{
				ft_strdel(&(tmp_ns.rev_mant));
				setters_nbstr_div(&new_q_val, '-');
				ft_strprepend(new_q_val.rev_mant, &(a_q->rev_mant));
				tmp_ns = ft_nbstr_sub(r, cur_q_x_d);
				ft_strdel(&(r.rev_mant));
				r = tmp_ns;
				ft_strdel(&(cur_q_x_d.rev_mant));
				break ;
			}
			ft_strdel(&(cur_q_x_d.rev_mant));
			cur_q_x_d = tmp_ns;
		}
		setters_nbstr_div(&d, 'd');
	}
	ft_strdel(&(new_q_val.rev_mant));
}

t_nbstr			ft_nbstr_div(t_nbstr const r, t_nbstr const d)
{
	t_nbstr		q;
	t_nbstr		tmp_r;
	t_nbstr		tmp_d;

	tmp_r = r;
	tmp_d = d;
	tmp_r.rev_mant = ft_strdup(r.rev_mant);
	tmp_d.rev_mant = ft_strdup(d.rev_mant);
	q = ft_nbstrnew(r.digits, r.base);
	if (r.base_n != q.base_n || ft_nbstr_iszero(d))
		return (q);
	if (ft_nbstrcmp(r,d) < 0 || ft_nbstr_iszero(r))
		q.rev_mant[0] = q.base[0];
	else
		do_div(tmp_r, tmp_d, &q);
	ft_strdel(&(tmp_r.rev_mant));
	ft_strdel(&(tmp_d.rev_mant));
	q.digits = ft_strlen(q.rev_mant);
	q.neg = r.neg != d.neg;
	return (q);
}
