/*
De ce que je comprends:
Codepoint: numéro de 0 à 1114000 et quelques
[9:55 PM]
UTF-8 écriture du codepoint en taille variable
[9:56 PM]
Maintenant, comment appeler write ? Sur le codepoint ou le UTF-8 ?
[9:57 PM]
wchar_t: c'est le type du codepoint ou du UTF-8 ?
youva [10:26 PM]
Je sais même pas c'est quoi un codepoint xD
[10:27 PM]
Wchar_t c'est une valeur unicode pas encodée en utf_8
tduquesn [10:27 PM]
C'est la valeur en int clair de ton symbole, si tu veux
[10:27 PM]
donc wchar_t pour le code point du coup
youva [10:27 PM]
Ouais
tduquesn [10:28 PM]
Gracias. Et pour l'appel à write ?
youva [10:28 PM]
Bah de lutf8
[10:28 PM]
En gros quand tu write ça doit être une chaîne de chars
tduquesn [10:29 PM]
D'accord, donc write comprend l'utf-8 nativement ?
[10:29 PM]
Du coup, pourquoi wchar_t ?
youva [10:30 PM]
Parce que une chaîne unicode est pas encodée de base
tduquesn [10:31 PM]
D'accord, tu la reçois en wchar_t et tu dois la convertir en utf-8 pour que write la lise
[10:32 PM]
Okok
[10:32 PM]
Je vais me coucher (grosse grippe). Cimer frérot
*/


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
