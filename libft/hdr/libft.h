/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 12:45:43 by tduquesn          #+#    #+#             */
/*   Updated: 2018/03/07 19:32:38 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** TODO
** Fix strlspad,
** add boolean functions (bool and boolarr)
** strinsert is an inplace which returns itself: make other inplace functions
** 				like this ? 
** lstinsert
** lstpop with pointers ? and rename current lstpop to lstpopi ?
** add ft_puthex_llstelem to libft, maybe rename putlst_hex
** vim -c  sed \ti++; to \t++i;
** vim -c  sed base_n to radix;
** rename all llst to lst
** Fix libft main.
** make a t_uple type with pragmas to dynamically define type.
** make an optimized Tensor/Matrix/Vector library.
*/

#ifndef __LIBFT_H
# define __LIBFT_H

# define OK 0
# define ERROR 1

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <inttypes.h>
# include <limits.h>

//# include "ft_printf.h" here, or in io, seeing that asprintf is a string function ?

# ifndef __BASES__
#  define __BASES__
#  define BINAR "01"
#  define OCTAL "01234567"
#  define DECIM "0123456789"
#  define HXLOW "0123456789abcdef"
#  define HXUPP "0123456789ABCDEF"
# endif

/*
** Shorthands for primitive types as bitsizes
*/
typedef char			t_s8;
typedef short			t_s16;
typedef int				t_s32;
typedef	long			t_s64;

typedef	unsigned char	t_u8;
typedef	unsigned short	t_u16;
typedef	unsigned int	t_u32;
typedef	unsigned long	t_u64;

typedef float			t_f32;
typedef double			t_f64;

/*
** Unions used for difficult casting conditions.
*/
typedef union			u_varint
{
	t_s8			sc;
	t_s16			ss;
	t_s32			si;
	t_s64			sl;
	t_u8			uc;
	t_u16			us;
	t_u32			ui;
	t_u64			ul;
}						t_varint;

typedef union			u_varfloat
{
	t_f32			f;
	t_f64			lf;
}						t_varfloat;

# ifndef __LIBFT_LST_H
#  include "libft_lst.h"
# endif
# ifndef __LIBFT_IO_H
#  include "libft_io.h"
# endif
# ifndef __LIBFT_MEM_H
#  include "libft_mem.h"
# endif
# ifndef __LIBFT_STR_H
#  include "libft_str.h"
# endif
# ifndef __LIBFT_MATH_H
#  include "libft_math.h"
# endif
# ifndef __LIBFT_APA_H
#  include "libft_apa.h"
# endif

/*
** NB : The functions below are kept in libft.h until they have been properly
** debugged. Their source should be kept in the top-level of ../src/
*/

/*
** =========== Str-Float Conversion Functions ==========
*/

/*
** Returns the standard, decimal representation of f as a string.
*/

char					*ft_ftoa(float f);

/*
** Returns the standard representation of f as a string in the base "base".
** Style specifies either exponential with an alphabetic char as exponent,
** or dot notation is a non-alpha character is given.
*/

char					*ft_ftoa_base(float f, char const *base, char style);

/*
** Returns the standard representation of lf as a string in the base "base".
** Style specifies either exponential with an alphabetic char as exponent,
*/

char					*ft_lftoa_base(double lf, char const *base, char style);



char		*ft_str_base_to_base_expn(char const *str, char const *base_f,
									char const *base_t, t_u32 expn);

char		*ft_str_base_expn_to_base(char const *str, char const *base_f,
									char const *base_t, t_u32 expn);

char		*ft_vlq_abstractval_as_hex(t_vlq const vlq);


t_vlq		ft_vlq_get_greatest_sub_pow10(t_vlq const vlq);


char		*ft_lftoa(double lf, char style);

#endif
