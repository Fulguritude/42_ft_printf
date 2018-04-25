/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 16:12:05 by fulguritu         #+#    #+#             */
/*   Updated: 2018/04/25 22:27:56 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** http://blog.aaronballman.com/2012/06/how-variable-argument-lists-work-in-c/
*/
/*
** In the absence of a prototype the compiler performs default promotions
** of certain arguments to functions:
**
** 1.  Signed integer types smaller than int (signed char, signed short),
** are promoted to signed int.
**
** 2.  Unsigned integer types smaller than int (unsigned char, unsigned
** short) are promoted to signed int, if signed int can hold all the
** entire range of values of the smaller unsigned type, or to unsigned
** int.
**
** 3.  Plain char (defined without signed or unsigned) is promoted to
** either signed or unsigned int depending on whether plain char is
** signed or unsigned for that particular compiler, according to rule 1
** or 2.
**
** 4.  Floating point arguments of type float are promoted to type
** double.
**
** Other argument types, signed or unsigned int, long, or long long,
** floating point types double and long double, and pointer types are not
** promoted at all but are passed to the function as is.
*/

t_str				*handle_format(t_format info, char const *fmt, va_list args)
{
	t_str	*result;

	if (info.type == percent && info.flags == FL_NONE && info.width == -1 &&
		info.prec == -1 && info.len_flag == no_len_flag)
		return (str_to_t_str("%"));
	else if (info.type == percent || info.type == no_type_error ||
		info.len_flag == incoherent_len_flag)
		return (str_to_t_str(fmt));
	else if (int_dec <= info.type && info.type <= int_ubin_u)
		return (handle_int_type(info, args));
	else if (info.type == string)
		return (handle_str_type(info, args));
	else if (info.type == uchar)
		return (handle_uchar_type(info, args));
	else if (info.type == float_pt)
		return (handle_float_type(info, args));
	else
	{
		if (!(result = (t_str*)malloc(sizeof(t_str))))
			return (NULL);
		result->data = NULL;
		result->len = -1;
		return (result);
	}
}
