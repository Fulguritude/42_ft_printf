#include "ft_printf.h"

/*
** The call to ft_ptrarrnew might allocate more memory than necessary, but in
** the absence of a way to find the length of the va_list, this is an adequate
** solution. Extra space will be allocated in the following circumstances:
** presence of a %%, any succession of %x%y without a 'plain/literal' substring
** between the two %x substrings, the format being a single "%y" without any
** plain string next to it, etc. What we give is a linear upper bound, at most
** 2n+1 where n is the optimal number of strings allocated one could obtain by
** analysing the format string before allocating memory.
** Accounting for the null-term => 2n+1+1
*/
/*
** Maybe just read the string linearly ? With multiple whiles
*/

char	**format_to_strls(char const *fmt)
{
	int		i;
	int		j;
	int		k;
	char	**result;

	if (!(result = ft_ptrarrnew(2 + 2 * ft_str_countchar(fmt, '%'))))
		return (NULL); //remove if moulinette ? or add ++j to if in first while below ? 
	k = -1;
	i = 0;
	while (fmt[i])
	{
		j = 1;
		if (fmt[i] == '%')
			while (fmt[i + j] && ft_in_base(fmt[i + j], ALL_SYMBOLS) != -1)
			{
				++j;
				if (ft_in_base(fmt[i + j - 1], TYPES) != -1)
					break ;
			}
		else
			while (fmt[i + j] && fmt[i + j] != '%')
				++j;
		result[++k] = ft_strsub(fmt, i, j);
		i += j;
	}
//	result[++k] = NULL;
	return (result);
}

t_format		read_format(char const *fmt_part)
{
	int			i;
	t_format	result;
//ft_putstr("\tRead format ...");
	i = 1;
	result.flags = read_format_flags(fmt_part, &i);
	result.width = read_format_width(fmt_part, &i);
	result.prec = read_format_prec(fmt_part, &i);
	result.len_flag = read_format_len_flag(fmt_part, &i);
	result.type = read_format_type(fmt_part, &result, i);
//ft_putendl("... format read\n");
	if (result.type == float_pt && result.prec == -1 &&
		result.type_char != 'a' && result.type_char != 'A')
		result.prec = 6;
	return (result);
}

//
// TODO remove
#include <stdio.h>

void	convert_str(char const *fmt_part, t_list **a_lststr, va_list args)
{
	char		type;
	t_format	format_info;
	t_str		*result;

	if (fmt_part[0] != '%')
		result = str_to_t_str(fmt_part);
	else
	{
		type = fmt_part[ft_strlen(fmt_part) - 1];
		if (ft_in_base(type, TYPES) == -1)
			result = str_to_t_str(fmt_part);
		else
		{
//printf("\t\t--Format_info :\n\t\t\t");
			format_info = read_format(fmt_part);
//printf("%d flags, %d width, %d prec, %d len_flag, %d type\n\t\t++Format_info end.\n", format_info.flags, format_info.width, format_info.prec, format_info.len_flag, format_info.type);
//printf("\t\t--Handled result :\n\t\t\t");
			result = handle_format(format_info, fmt_part, args);
//printf("data: %s, len: %lu\n\t\t++Handled result end.\n", result->data, result->len);
		}
	}
//printf("\tFinal result :\n\t\tdata: %s;\n\t\tlen: %lu\n", result->data, result->len);
	ft_lstappend(a_lststr, ft_lstnew_no_copy(result, sizeof(t_str)));
}
