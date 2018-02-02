#include "ft_printf.c"

/*
** 0x7F = 127, 0x7FF = 2047, 0xFFFF = 65535
** Also, for 0b11000000 = 0xC0, 0b11100000 = 0xE0 and 0b11110000 = 0xF0, 
** 1 << size is 2^size, -1 makes it 00000111 with as many 1s as size, bitshift
** left (8 - size) gives the result we want.
** mod 0x40 => extract six last digits.
*/

char	*encode_unicodepoint_to_utf8(wchar_t c)
{
	size_t	size;
	char	*utf8_c;

	if (c > 0x10FFFF)
		return (NULL);
	size = 1 + (c > 0x7F) + (c > 0x7FF) + (c > 0xFFFF);
	if (!(utf8_c = ft_strnew(size)))
		return (NULL);
	utf8_c[0] = size > 1 ? ((0x1 << size) - 1) << (8 - size) : 0;
	while (--size)
	{
		utf8_c[size] = 0x80 | c % 0x40;
		c /= 0x40;
	}
	utf8_c[0] |= c;
	return (utf8_c);
}

/*
** Maybe make a single malloc of size_t (4 * len(unicode_str)) for utf8_str,
** use strcat intelligently, then another single malloc once final size_t is
** known ? strappend so often would probably be quite computation-hungry.
** See how this affects performance in the end.
*/

char	*read_utf8(wchar_t *unicode_str)
{
	char	*utf8_str;
	char	*new_char;
	int		i;

	if (!(utf8_str = ft_strnew(0)))
		return (NULL);
	i = 0;
	while (unicode_str[i])
	{
		new_char = encode_unicodepoint_to_utf8(unicode_str[i]);
		if (new_char == NULL)
		{
			free(utf8_str);
			return (NULL);
		}
		ft_strappend(utf8_str, new_char);
		free(new_char);
		++i;
	}
	return (utf8_str);	
}
