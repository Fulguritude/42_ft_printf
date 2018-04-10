#ifndef __LIBFT_IO_H
# define __LIBFT_IO_H

# ifndef __LIBFT_H
#  include "libft.h"
# endif

# include <unistd.h>

//TODO fix
# ifndef __FT_PRINTF_H
#  include "../../ft_printf.h"
# endif

# define HEXCOLS	6

/*
** ============ Readers ============
*/

//TODO add get_next_line
//TODO file_to_strls

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
//ft_printf, ft_asprintf, etc

#endif
