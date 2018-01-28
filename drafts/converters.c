//dans quel cas le \0 dans la chaine ? dans le fmt plaintext, ca passe ?

#include "ft_printf.h"

//change all char ** to t_list of t_str

char	**format_to_strls(char const *format, int argc)
{
	int		i;
	int		j;
	int		k;
	char	**result;

	if (!(result = ft_ptrarrnew(2 * argc)))
		return (NULL);
	k = -1;
	i = 0;
	while (format[i])
	{
		j = 0;
		if (format[i] == '%')
			while (ft_in_base(format[i + j], CONVS) == -1)
				++j;
		else
			while (format[i + j] != '%')
				++j;
		result[++k] = ft_strsub(format, i, j);
		i += j;
	}
	result[++k] = NULL;
	return (result);
}

/*
** Strings here are already checked to start with '%'
*/

int		convert_str(char **fmt_part, va_list args)
{
	char	converter;
	void	*data;
	t_str	*result;
	int		len;

//	converter = (*fmt_part
	return (len);
}
