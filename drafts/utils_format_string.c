#include "ft_printf.h"

/* t_format:
	t_u8			flags;
	int				width;
	int				prec;
	t_len_flag		len_flag;
	t_types			type;
*/

t_u8			read_format_flags(char const *fmt_part, int *i)
{
	t_u8	flags;
	char	c;

	flags = 0;
	if (ft_in_base(FLAGS, fmt_part[*i]) == -1)
		return (FL_ERROR);
	while (ft_in_base(FLAGS, fmt_part[*i]) != -1)
	{
		c = fmt_part[*i];
		if (c == '+')
			flags |= FL_PLUS;
		else if (c == '-')
			flags |= FL_MINUS;
		else if (c == '#')
			flags |= FL_HASH;
		else if (c == '0')
			flags |= FL_ZERO;
		else if (c == ' ')
			flags |= FL_SPACE;
		++(*i);
	}
	return (flags);
}

int				read_format_width(char const *fmt_part, int *i)
{
	int		width;
	t_u8	digit;

	if (ft_in_base(DECIM, fmt_part[*i]) == -1)	
		return (-1);
	width = 0;
	while (ft_in_base(DECIM, fmt_part[*i]) != -1)
	{
		digit = fmt_part[*i];
		width = width * 10 + digit - '0';
		++(*i);
	}
	return (width);
}


int				read_format_prec(char const *fmt_part, int *i)
{
	int		prec;
	t_u8	digit;

	if (fmt_part[*i] != '.')	
		return (-1);
	++(*i);
	prec = 0;
	while (ft_in_base(DECIM, fmt_part[*i]) != -1)
	{
		digit = fmt_part[*i];
		prec = prec * 10 + digit - '0';
		++(*i);
	}
	return (prec);
}


t_len_flag		read_format_len_flag(char const *fmt_part, int *i)
{
	char		len_flag_c;
	char		count;
	t_len_flag	result;

	
	if (ft_in_base(LGTHS, fmt_part[*i]) == -1)	
		return (no_len_flag);
	len_flag_c = fmt_part[*i];
	count = 1;
	++(*i);
	if (fmt_part[*i] == len_flag_c)
		(*i) += count++;
	else if (ft_in_base(LGTHS, fmt_part[*i]) != -1)
		return (incoherent_len_flag);
	if (count == 2 && ((len_flag_c != 'l' && len_flag_c != 'h') ||
						(ft_in_base(LGTHS, fmt_part[*i + 1]) != -1)))
		return (incoherent_len_flag);
	if (count == 2)
		return (len_flag_c == 'l' ? fl_ll : fl_hh);
	result = len_flag_c == 'h' ? fl_h : no_len_flag;
	result = len_flag_c == 'l' ? fl_l : result;
	result = len_flag_c == 'j' ? fl_j : result;
	result = len_flag_c == 'z' ? fl_z : result;
	return (result);
}

t_types			read_format_type(char const *fmt_part, int i)
{
	if (ft_in_base(TYPES, fmt_part[i]) == -1)
		return (no_type_error);
}

t_format		read_format(char const *fmt_part)
{
	int			i;
	t_format	result;

	i = 1;
	result.flags = read_format_flags(fmt_part, &i);
	result.width = read_format_width(fmt_part, &i);
	result.prec = read_format_prec(fmt_part, &i);
	result.len_flag = read_format_len_flag(fmt_part, &i);
	result.type = read_format_type(fmt_part, i); //maybe give "type" as an argument to gain a bit of place because read_format_type probably won't have enough lines for all possibilities
	return (result);
}

t_str			resolve_format(t_format fmt_info, va_list args)
{
	//return result.len == -1 in case of incoherent format
}
