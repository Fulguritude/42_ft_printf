/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 12:45:43 by tduquesn          #+#    #+#             */
/*   Updated: 2018/02/20 21:38:31 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** TODO
** Fix strpad,
** strlspad,
** boolean functions,
** str_replace
** lstinsert
** lstnew without copy DONE
** lstpop with pointers ? and rename lstpopi ?
** add ft_puthex_llstelem to libft, maybe rename putlst_hex
** vim -c  sed \ti++; to \t++i;
** rename all llst to lst
** Fix libft main.
** make a t_uple type with pragmas to dynamically define type.
*/

#ifndef LIBFT_H
# define LIBFT_H

# define OK 0
# define ERROR 1

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef	unsigned char	t_u8;
typedef	unsigned short	t_u16;
typedef	unsigned int	t_u32;
typedef	unsigned long	t_u64;

typedef char			t_s8;
typedef short			t_s16;
typedef int				t_s32;
typedef	long			t_s64;

typedef struct			s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}						t_list;

/*
** ============ Memory Functions ===========
*/

/*
** Allocates 'size' bytes in memory, returning the pointer at which said bytes
** were allocated, or NULL if the memory could not be allocated.
*/

void					*ft_memalloc(size_t size);

/*
** Frees the allocated memory at '**ptr', and sets '*ptr' as NULL.
*/

void					ft_memdel(void **ptr);

/*
** Swaps the two numbers pointed to by 'ptr1' and 'ptr2' (they must both be
** of the same 'size').
*/

int						ft_swap(void *a, void *b, size_t sizeof_ab);

/*
** Fills 'n' bytes of memory with 0s, starting at 'ptr'.
*/

void					ft_bzero(void *ptr, size_t n);

/*
** Fills 'n' bytes of memory with 'byte' (taking only the first 8 bits of this
** int arg), starting at 'ptr'.
*/

void					*ft_memset(void *ptr, int byte, size_t n);

/*
** Copies 'n' bytes of memory from 'src' to 'dest'.
*/

void					*ft_memcpy(void *dest, void const *src, size_t n);

/*
** Copies at most 'n' bytes of memory from 'src' to 'dest', stopping at the
** first encounter of a byte equal to 'c'.
*/

void					*ft_memccpy(void *dest, void const *src, int c,
									size_t n);

/*
** Reads 'n' bytes of memory from 'src' then writes those bytes to 'dest'
** - useful if 'src' and 'dest' overlap.
*/

void					*ft_memmove(void *dest, void const *src, size_t n);

/*
** Finds and returns the first occurrence of a byte equal to 'byte',
** starting at 'ptr' and searching 'n' bytes.
*/

void					*ft_memchr(void const *ptr, int byte, size_t n);

/*
** Compares 'n' bytes at 'ptr1' and 'ptr2', returning (byte1 - byte2)
** at the first difference encountered.
*/

int						ft_memcmp(void const *ptr1, void const *ptr2, size_t n);

/*
** Returns a newly allocated memory area which copy of the given memory area
** 'ptr' (or NULL if the required memory could not be allocated or if ptr is
** empty).
*/

void					*ft_memdup(void const *ptr, size_t n);

/*
** Returns a string in hexadecimal describing what is contained in memory
** pointed to by s. If n is larger than allocated area, behavior is undefined.
*/

char					*ft_memhex(void const *ptr, size_t n);

/*
** If p, clears memory over mem_size bytes then frees p and NULLs it.
*/

void					ft_delete(void *p, size_t mem_size);

/*
** ========== Str-Int Conversion Functions ==========
*/

/*
** Returns the number of digits in n knowing that n is written in base 10.
*/

int						ft_digits(int n);

/*
** Returns the number of digits in n knowing that n is written in base "base".
*/

int						ft_digits_base(int n, int base);

/*
** Returns an int parsed from the given string number 'str' (returns 0 if
** 'str' is invalid).
*/

int						ft_atoi(char const *str);

/*
** Returns a long parsed from the given string number 'str', according to the
** given 'base' (returns 0 if 'str' is invalid). DOES NOT CHECK FOR LONG
** OVERFLOW.
*/

long					ft_atoi_base(char const *str, char const *base);

/*
** Returns a new string which is the representation of the given number 'n'.
*/

char					*ft_itoa(int n);

/*
** Returns a new string which is the representation of the given number 'n',
** according to the given 'base'.
*/

char					*ft_itoa_base(long nb, char const *base);

/*
** Returns a new string which is nb written in "base" where nb is unsigned.
*/

char					*ft_uitoa_base(unsigned long nb, char const *base);


/*
** Takes a string as a number written in base "base_from" (digit val == index
** of digit symbol in string) and returns a newly allocated (itoa_base) string
** in base "base_to".
*/

char					*ft_convert_base(char const *nbr, char const *base_from,
										char const *base_to);
/*
** Returns 1 if base contains only distinct symbols and contains only printable
** characters. Returns 0 otherwise, or if '+' or '-' are used as symbols in
** base.
*/

int						ft_is_valid_base(char const *base);

/*
** Returns the index of c in base, which is also its digit value. Inputting '\0'
** for c returns strlen, absence of c in base returns -1.
*/

int						ft_in_base(char c, char const *base);

/*
** =========== Character Functions ==========
*/

/*
** Returns 1 if the given char 'c' is a letter (lowercase or uppercase), and
** 0 otherwise.
*/

int						ft_isalpha(int c);

/*
** Returns 1 if the given char 'c' is a numerical digit, and 0 otherwise.
*/

int						ft_isdigit(int c);

/*
** Returns 1 if the given char 'c' is alphanumeric (number or letter), and 0
** otherwise.
*/

int						ft_isalnum(int c);

/*
** Returns 1 if the given char 'c' has a value between 0 and 127, and 0
** otherwise.
*/

int						ft_isascii(int c);

/*
** Returns 1 if the given char 'c' is a printable ASCII character, and 0
** otherwise.
*/

int						ft_isprint(int c);

/*
** Returns the uppercase equivalent of the given char 'c' (nothing is done
** if 'c' is not a letter).
*/

int						ft_toupper(int c);

/*
** Returns the lowercase equivalent of the given char 'c' (nothing is done
** if 'c' is not a letter).
*/

int						ft_tolower(int c);

/*
** Returns 1 if the given char 'c' is \t, \n, \v, \r or \f, and 0 otherwise.
*/

int						ft_isspace(int c);

/*
** ============ String Functions ===========
*/

/*
** Returns the length of the given null-terminated string 'str'.
*/

size_t					ft_strlen(char const *str);

/*
** Creates a new string of the given 'size', allocating memory, setting
** each element to '\0'.
*/

char					*ft_strnew(size_t size);

/*
** Creates a 2D rectangle of newly allocated memory.
*/

char					**ft_strlsnew(t_u32 y, size_t x, char const c);

/*
** Deletes the string pointed to by 'ptr', freeing memory.
*/

void					ft_strdel(char **ptr);

/*
** Clears the given string 's', setting each element to '\0'.
*/

void					ft_strclr(char *str);

/*
** Returns a newly allocated string which is a copy of the given string
** 'str' (or NULL if the required memory could not be allocated).
*/

char					*ft_strdup(char const *str);

/*
** Returns a newly-allocated copy of str, considering c as an additional
** terminating character for str.
*/

char					*ft_strcdup(char const *str, char const c);

/*
** Returns a newly allocated string containing the same characters as
** 'str', in reverse order.
*/

char					*ft_strrev(char const *str);

/*
** Copies the given string 'src' into 'dest' (null-terminator included),
** and returns 'dest'.
*/

char					*ft_strcpy(char *dest, char const *src);

/*
** Copies the first 'n' characters of the given string 'src' into 'dest',
** and returns 'dest'.
*/

char					*ft_strncpy(char *dest, char const *src, size_t n);

/*
** Copies the given string 'src' into 'dest', null-terminating 'dest'
** (the '\0' is placed at ('size' - 1)), and it returns the resulting
** size of 'dest'.
*/

size_t					ft_strlcpy(char *dest, char const *src, size_t size);

/*
** Concatenates the given string 'src' to the end of 'dest', and returns 'dest'.
*/

char					*ft_strcat(char *dest, char const *src);

/*
** Concatenates the first 'n' characters of the given string 'src' to the end
** of 'dest', and returns 'dest'.
*/

char					*ft_strncat(char *dest, char const *src, size_t n);

/*
** Concatenates up to ('size' - 1) characters of the given string 'src' to the
** end of 'dest', null-terminating the result, and returning the resulting size.
*/

size_t					ft_strlcat(char *dest, char const *src, size_t size);

/*
** Returns a newly allocated string, the result of the concatenation of s1
** containing the character c a total of n times, and a string s2 == s.
*/

char					*ft_strpad_left(char const *s, char const c, t_u32 n);

/*
** Returns ft_strpad_left by reference rather than new allocation.
*/

void					ft_strpad_left_inplace(char **a_str,
											char const c, t_u32 len);

/*
** Returns a newly allocated string list, where each line is the result of
** the appropriate ft_strpad_left of length n.
*/

char					**ft_strlspad_left(char const **strls,
											char const c, t_u32 n);

/*
** Returns a newly allocated string, the result of the concatenation of a string
** s1 == s and s2 containing the character c a total of n times.
*/

char					*ft_strpad_right(const char *s, const char c, t_u32 n);

/*
** Returns ft_strpad_right by reference rather than new allocation.
*/

void					ft_strpad_right_inplace(char **a_str,
											char const c, t_u32 len);

/*
** Returns a pointer to the first occurence of a char 'c' in the given string
** 'str' (or NULL if nothing matched).
*/

char					*ft_strchr(char const *str, int c);

/*
** Returns a pointer to the last occurence of a char 'c' in the given string
** 'str' (or NULL if nothing matched).
*/

char					*ft_strrchr(char const *str, int c);

/*
** Returns the first occurence of the string 'sub' inside the given string
** 'str' (or NULL if nothing matched).
*/

char					*ft_strstr(char const *str, char const *sub);

/*
** Returns the first occurence of the string 'sub' inside the given string
** 'str' (or NULL if nothing matched), searching only the first 'n' bytes.
*/

char					*ft_strnstr(char const *str, char const *sub, size_t n);

/*
** Compares the two given strings, and returns the first difference of
** characters encountered: (str1[i] - str2[i]). NULL input treated like
** empty string.
*/

int						ft_strcmp(char const *s1, char const *s2);

/*
** Compares at most 'n' chars of the two given strings, and returns the
** first difference of characters encountered: (str1[i] - str2[i]).
*/

int						ft_strncmp(char const *s1, char const *s2, size_t n);

/*
** Returns 1 if the two given strings match, and 0 otherwise.
*/

int						ft_strequ(char const *s1, char const *s2);

/*
** Returns 1 if the first 'n' chars of the two given strings match, and 0
** otherwise.
*/

int						ft_strnequ(char const *s1, char const *s2, size_t n);

/*
** Iterates upon the given string 'str', applying the function 'f' to each
** of its elements.
*/

void					ft_striter(char *str, void (*f)(char *));

/*
** Iterates upon the given string 'str', applying the function 'f' to each
** of its elements (with index information).
*/

void					ft_striteri(char *str, void (*f)(unsigned int, char *));

/*
** Creates a new string by iterating upon the string 'str', applying the
** function 'f' to each of its chars.
*/

char					*ft_strmap(char const *str, char (*f)(char));

/*
** Creates a new string by iterating upon the string 'str', applying the
** function 'f' to each of its chars (with index information).
*/

char					*ft_strmapi(char const *str, char (*f)(t_u32, char));

/*
** Returns a new string which is a subsection of 'str', starting at 'start'
** and copying 'len' characters.
*/

char					*ft_strsub(char const *str, unsigned int start,
									size_t len);

/*
** Returns a newly allocated sub-stringlist from strls, similarly to ft_strsub.
*/

char					**ft_strlssub(char const **strls,
									t_u32 start, t_u32 len);

/*
** Returns the concatenation of dest and src inside the pointer of dest.
** The previous dest is freed and src is unaltered.
*/

char					*ft_strappend(char **dest, char const *src);

/*
** Returns the concatenation of src and dest inside the pointer of dest.
** The previous dest is free and src is unaltered.
*/

char					*ft_strprepend(char const *src, char **dest);

/*
** Returns a new string which is the result of the concatenation of the
** two given strings.
*/

char					*ft_strjoin(char const *str1, char const *str2);

/*
** Returns a new string from 'str' in which all leading and trailing
** whitespace characters (' ', '\n', '\t') have been removed.
*/

char					*ft_strtrim(char const *str);

/*
** Returns an array of substrings of 'str', where each element is a section
** delimited by 'c' separators, or the edges of the string.
*/

char					**ft_strsplit(char const *str, char c);

/*
** Returns an array of substrings of 'str', where any c in sep_chars is
** considered whitespace that delimits strings.
*/

char					**ft_split(char const *str, char const *sep_chars);

/*
** Returns a big-endian hexadecimal string of the elements of str considered
** as unsigned char.
*/

char					*ft_strhex(char const *str);

/*
** Returns a newly allocated string that is the sum of strings in strls, and
** the string sep has been added between each string. All arguments must be
** properly null-terminated.
*/

char					*ft_strlsjoin(char const **strls, char const *sep);

/*
** Returns a newly allocated strls from a str, which is divided into regular
** intervals of length n. str must be null-terminated.
*/

char					**ft_strdivide(char const *str, size_t n);

/*
** Frees a regular nul-term array of nul-term strings and NULLs appropriate
** pointers.
*/

void					ft_strlsdel(char ***a_strls);

/*
** Returns the number of occurences of c in str.
*/

t_u32					ft_str_countchar(char const *str, char const c);

/*
** Returns the number of occurences of 'c' in strls.
*/

t_u32					ft_strls_countchar(char const **strls, char const c);

/*
** Returns the number of lines in a nul-terminated strls, or just a general
** nul-terminated pointer array.
*/

t_u32					ft_ptrarrlen(void const *a_ptrarr);

/*
** Returns a point to a nul-terminated, clear, pointer array of length n.
*/

void					*ft_ptrarrnew(t_u32 n);

/*
** ============ Write Functions ============
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

void					ft_putllstelem(t_list *elem);

/*
** Writes the data contained in each elem of lst to standard output.
*/

void					ft_putllst(t_list *lst);

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

void					ft_putllstelem_fd(t_list *elem, int fd);

/*
** Writes the data contained in each elem of lst to file descriptor as
** streams of t_u8 separated by newlines.
*/

void					ft_putllst_fd(t_list *lst, int fd);

/*
** Writes an element of a linked list containing signed numbers of any size_t
** (1, 2, 4 or 8) to file descriptor fd. If content_size is not appropriate,
** nothing is done.
*/

void					ft_putnbr_llstelem_fd(t_list *elem, int fd);

/*
** Writes a linked list containing signed numbers of any size_t (1, 2, 4 or 8)
** to file descriptor fd.
*/

void					ft_putnbr_llst_fd(t_list *lst, int fd);

/*
** ============= List Functions =============
*/

/*
** Allocates and returns a new element of a list, according to the given
** arguments. Note that 'content' is duplicated.
*/

t_list					*ft_lstnew(void const *content, size_t content_size);

/*
** Same as lstnew except content is not duplicated.
*/

t_list					*ft_lstnew_no_copy(void *content, size_t content_size);

/*
** Inserts a new element of a list 'new' at the pointer '*alst', chaining it
** with the next element.
*/

void					ft_lstadd(t_list **alst, t_list *new_elem);

/*
** Appends the element 'new_elem' to the end of the list starting at '*alst'.
*/

void					ft_lstappend(t_list **alst, t_list *new_elem);

/*
** Deletes the given element pointed to by 'alst' with the given function 'del',
** then frees memory and NULLs '*alst'.
*/

void					ft_lstdelone(t_list **alst,
									void (*del)(void *, size_t));

/*
** Deletes all the elements in the list starting at '*alst', calls 'del' and
** frees memory for each, and lastly NULLs '*alst'.
*/

void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));

/*
** Returns the amount of elements in the given list 'lst'.
*/

t_u32					ft_lstsize(t_list *lst);

/*
** Removes and frees the first occurence of elem in a linked list and relinks
** the remaining strands.
*/

void					ft_lstpop(t_list **a_lst, t_u32 index,
									void (*del)(void *, size_t));

/*
** Returns a newly allocated copy of lst.
*/

t_list					*ft_lstcpy(t_list *lst);

/*
** Returns a newly allocated copy of a section of lst. Returns NULL if error.
*/

t_list					*ft_lstsub(t_list *lst, t_u32 start, t_u32 n);

/*
** Returns the pointer to the element at index n in linked list lst.
*/

t_list					*ft_lstget(t_list *lst, t_u32 n);

/*
** Iterates on the given list 'lst', applying the given function 'f' to each
** of its elements.
*/

void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));

/*
** Creates a new list which is the result of applying the given function 'f'
** to each element of 'lst'.
*/

t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

/*
** Applies operator f to the elements of lst by pairs, grinding the list into
** a single value. Here, the left operand acc is an accumulator (starting at
** the unit element for the operand type of f, like 0 for addition or "" for
** concatenation) of the results of previous iterations of f and the right
** operand is the next item in lst. The point of this function is to turn an
** associative binary operator (like +(x,y):=x + y) into an efficient n-ary
** operator (like SUM_1..n(x_i)). Note that typeof(acc), and typeof(f_arg1)
** should be the same type 'a; also, that typeof(lst->content) and
** typeof(f_arg2) should be of the same type 'b. You can make this work
** with 'a != 'b.
*/

void					ft_lstfold(t_list *lst, void *acc,
									void (*f)(void *, void *));

/*
** Useful conversion function. Must be sure to take a valid list of strings.
** Should log inoherence in size/null-term.
*/

char					**ft_lststr_to_strls(t_list	*lst);

#endif
