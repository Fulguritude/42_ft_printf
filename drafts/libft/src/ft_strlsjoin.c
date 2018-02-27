/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlsjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 12:50:11 by tduquesn          #+#    #+#             */
/*   Updated: 2017/11/28 11:44:42 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strnb_charnb_in_strls(const char **str_ls, int *w_nb, int *c_nb)
{
	int str_at;

	str_at = 0;
	while (str_ls[str_at])
	{
		*(c_nb) += ft_strlen(str_ls[str_at]);
		str_at++;
	}
	*w_nb = str_at;
}

static void	ft_build_str(char *dest, const char **str_ls, const char *sep)
{
	int i;
	int words;
	int chars;
	int sep_i;

	i = 0;
	sep_i = 0;
	words = -1;
	while (str_ls[++words])
	{
		chars = 0;
		while (str_ls[words][chars])
			dest[i++] = str_ls[words][chars++];
		sep_i = 0;
		while (sep[sep_i] && str_ls[words + 1])
			dest[i++] = sep[sep_i++];
	}
	dest[i] = '\0';
}

char		*ft_strlsjoin(const char **strls, const char *sep)
{
	char	*str;
	int		strls_str_nb;
	int		strls_char_nb;
	int		total_sep_char_nb;
	int		total_char_nb;

	if (!strls || !sep)
		return (NULL);
	ft_strnb_charnb_in_strls(strls, &strls_str_nb, &strls_char_nb);
	total_sep_char_nb = (strls_str_nb - 1) * ft_strlen(sep);
	total_char_nb = total_sep_char_nb + strls_char_nb;
	if (!(str = (char*)malloc((total_char_nb + 1) * sizeof(*str))))
		return (NULL);
	ft_build_str(str, strls, sep);
	return (str);
}
