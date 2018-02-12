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

char	**format_to_strls(char const *format)
{
	int		i;
	int		j;
	int		k;
	char	**result;

	if (!(result = ft_ptrarrnew(2 + 2 * ft_str_countchar(format, '%'))))
		return (NULL);
	k = -1;
	i = 0;
	while (format[i])
	{
//ft_putstr("Curr str : ");
//ft_putendl(format + i);
		j = 1;
		if (format[i] == '%')
			while (format[i + j] && ft_in_base(format[i + j], ALL_SYMBOLS) != -1)
			{
				++j;
				if (ft_in_base(format[i + j], TYPES) != -1)
				{
					++j;
					break ;
				}
			}
		else
			while (format[i + j] != '%' && format[i + j])
				++j;
		result[++k] = ft_strsub(format, i, j);
		i += j;
	}
	result[++k] = NULL;
	return (result);
}

//
//
#include <stdio.h>

void	convert_str(char *fmt_part, t_list **a_lststr, va_list args)
{
	char		type;
	t_format	format_info;
	t_str		result;

	if (fmt_part[0] != '%')
		result = str_to_t_str(fmt_part);
	else
	{
		type = fmt_part[ft_strlen(fmt_part) - 1];
		if (ft_in_base(type, TYPES) == -1)
			result = str_to_t_str(fmt_part);
		else
		{
			format_info = read_format(fmt_part);
printf("Format_info : %d flags, %d width, %d prec, %d len_flag, %d type\n", format_info.flags, format_info.width, format_info.prec, format_info.len_flag, format_info.type);
			result = handle_format(format_info, fmt_part, args);
			//if (result.len == -1)
				//TODO ? make various -n error codes using the length of the t_str ?
		}
	}
	ft_lstappend(a_lststr, ft_lstnew(&result, sizeof(t_str)));
}
