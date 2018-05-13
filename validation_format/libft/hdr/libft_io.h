/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_io.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 22:32:05 by fulguritu         #+#    #+#             */
/*   Updated: 2018/04/19 22:32:27 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_IO_H
# define LIBFT_IO_H

# include "libft.h"

# define HEXCOLS	6

# ifndef	LST_STRUCT
#  define	LST_STRUCT
typedef struct			s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}						t_list;
# endif

/*
** ============ Readers ============
*/
/*
** TODO add get_next_line
** TODO file_to_strls
*/

/*
** ============ Writers ============
*/

/*
** Writes the given char 'c' to the standard output.
*/
void					ft_putchar(char c);

/*
** Writes the given string 'str' to the standard output.
*/
void					ft_putstr(char const *str);

/*
** Writes the given string 'str' to the standard output, with a newline at the
** end.
*/
void					ft_putendl(char const *str);

/*
** Writes the string representation of the given number to the standard output.
*/
void					ft_putnbr(int number);

/*
** Writes a given nul-term list of strings to standard output.
*/
void					ft_putstrls(char const **strls);

/*
** Writes the data contained in elem to standard output as a stream of t_u8.
*/
void					ft_putlstelem(t_list *elem);

/*
** Writes the data contained in each elem of lst to standard output.
*/
void					ft_putlst(t_list *lst);

/*
** Prints memory in 'str' in 6 columns of 4 distinct bytes to stdout.
*/
void					ft_putmem(char const *str);

/*
** Writes the given char 'c' to the given file descriptor 'fd'.
*/
void					ft_putchar_fd(char c, int fd);

/*
** Writes the given string 'str' to the given file descriptor 'fd'.
*/
void					ft_putstr_fd(char const *str, int fd);

/*
** Writes the given string 'str' to the given file descriptor 'fd',
** with a newline at the end.
*/
void					ft_putendl_fd(char const *str, int fd);

/*
** Writes the string representation of the given number to the given
** file descriptor 'fd'.
*/
void					ft_putnbr_fd(int number, int fd);

/*
** Writes a given nul-term list of strings to file descriptor.
*/
void					ft_putstrls_fd(char const **strls, int fd);

/*
** Writes the data contained in elem to file descriptor as a stream of t_u8.
*/
void					ft_putlstelem_fd(t_list *elem, int fd);

/*
** Writes the data contained in each elem of lst to file descriptor as
** streams of t_u8 separated by newlines.
*/
void					ft_putlst_fd(t_list *lst, int fd);

/*
** Writes an element of a linked list containing signed numbers of any size_t
** (1, 2, 4 or 8) to file descriptor fd. If content_size is not appropriate,
** nothing is done and the function fails silently.
*/
void					ft_putnbr_lstelem_fd(t_list *elem, int fd);

/*
** Writes a linked list containing signed numbers of any size_t (1, 2, 4 or 8)
** to file descriptor fd.
*/
void					ft_putnbr_lst_fd(t_list *lst, int fd);

/*
** Prints memory in  (null-term) 'str' in HEXCOLS columns of 4 distinct bytes to
** 'fd'.
*/
void					ft_putmem_fd(char const *str, int fd);

/*
** Prints memory in  (null-term) 'str' in HEXCOLS columns of 4 distinct bytes to
** stdout.
*/
void					ft_putmem(char const *str);

/*
** ============ Printf family ===============
*/

#endif
