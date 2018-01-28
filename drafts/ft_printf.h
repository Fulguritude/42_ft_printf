/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 15:52:29 by tduquesn          #+#    #+#             */
/*   Updated: 2018/01/05 15:53:00 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_PRINTF
# define __FT_PRINTF

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <locale.h>
# include "libft/libft.h"

# define FLAGS "#0- +hljz" //*, $, L, '
# define CONVS "pdDioOuUxXcCsS%" //eE, fF, gG, aA, n, bB
# define PRECS ".0123456789"
# define HXMIN "0123456789abcdef"
# define HXCAP "0123456789ABCDEF"


typedef struct	s_str
{
	char	*data;
	int		len;
}				t_str;

int		ft_printf(const char *format, ...);
int		ft_printf_fd(int fd, const char *format, ...);
int		ft_vprintf_fd(int fd, const char *format, va_list args);
int		ft_asprintf(char **res, const char *format, ...);
int		ft_vasprintf(char **res, const char *format, va_list args);

#endif
