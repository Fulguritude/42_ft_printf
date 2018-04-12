#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#include "../ft_printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#ifndef __ANSI_COLOR_CODES__
# define __ANSI_COLOR_CODES__
# define C_RED     "\x1b[31m"
# define C_GREEN   "\x1b[32m"
# define C_YELLOW  "\x1b[33m"
# define C_BLUE    "\x1b[34m"
# define C_MAGENTA "\x1b[35m"
# define C_CYAN    "\x1b[36m"
# define C_RESET   "\x1b[0m"
#endif


# define VERBOSE							1
#  define SHOW_CORRECT_RESULT_COMPARISON 	1

# define INTTYPE_SHORTHANDS_DEFINED			1 
# define STRREPLACE_DEFINED					1
/*
** To compile, these should be 0 unless you've added these shorthands to libft
** yourself, see below with ctrl+f.
** I've left the basic libft required functions out of this file. If you have
** no libft to call (why are you here if that's the case?), code a small
** function using strstr to find every "ft_" and replace it with "   " in every
** string that's returned. Since the length doesn't change, this is easy.
*/

# define _MAIN_TESTS_						1
#  define INT_HANDLER						1
#  define STR_HANDLER						1
#   define UNSET_LOCALE						0
#  define OTHER_HANDLER						1
# define MAIN_TESTS							_MAIN_TESTS_ && (INT_HANDLER || STR_HANDLER || OTHER_HANDLER)

# define _FLOAT_BONUSES_					1
#  define PERCENT_aA						1 //medium, easier than it looks
#  define PERCENT_eE						1 //very hard, or slow if you go through %f first like me
#  define PERCENT_fF						1 //hard
#  define PERCENT_gG						1 //mostly dependent on e and f, but this one is harder than it seems
#  define SPECIAL_CASES						1 && (PERCENT_aA || PERCENT_eE || PERCENT_fF || PERCENT_gG)
#  define NORMAL_CASES						1 && (PERCENT_aA || PERCENT_eE || PERCENT_fF || PERCENT_gG)
# define FLOAT_BONUSES						_FLOAT_BONUSES_ && (NORMAL_CASES || SPECIAL_CASES)

# define _SMALL_BONUSES_					0
#  define PERCENT_b							1 //easy if you've done int handling well
#  define PERCENT_B							1 //easy if you've done int handling well
#  define PERCENT_r							1 //easy with something like strreplace
#  define COLOR_BONUS						1 //easy with something like strreplace
# define SMALL_BONUSES 						_SMALL_BONUSES_ && (PERCENT_b || PERCENT_B || PERCENT_r)

//TODO: recode test_int as a varint to allow checks on improperly cast input
//TODO: add a flag with %s that frees the string used, in order to make function calls that return a string within ft_printf
//TODO: add a strls type, say %y for example, with the same flag
//TODO: add a vlq type, say %v for example, with abstractval or memory
//TODO: Make macro block for undefined tests

//TODO: make undefined type specifiers more 42 compliant

/*
** ---------------------------------------------------------------------------
**
**		This is a main used as a homemade printf tester for 42. Unlike most
**	printf testers, this one is self-contained and uses only C to function.
**		The only special requirement is that you have your printf output depend
**  on the asprintf bonus. But in any case you should have it be that way
**  anyways if you're not doing the buffering.
**		Edit the 1's in the previous section accordingly to select which tests
**  to run. 0's at the top of a block turn off all dependent subtests.
**
**
**		FT_PRINTF MAIN UNIT TESTER
**
**   IMPORTANT NOTES :
**
**   -	"#if 0" and "#endif" pragmas are used only to comment out text below for
**		readability in the stdout of the unit tests. Don't use multiline
**		comments to 'hide' code as these tend to mess things up (in general, not
**		just here).
**
**	 -	// commented lines correspond to printf values that cause warnings.
**		They are to be kept for future users to know which combinations are
**		undefined before adding unnecessary functionalities; as well as seeing
**		how various	printf implementations handle basic undefined outputs
**		(remove CFLAGS in Makefile beforehand).
**
**
**	 -  To debug your own printf efficiently, I suggest you start the printf
**		calls inside your ft_printf subcalls by an appropriate number of tabs,
**		so that each subcall looks more and more "internal" and errors can be
**		found quickly. End all printf calls with \n to force flush the printf
**		buffer to stdout and have stdout be coherent with current function call.
**
**	 -	Tests on zero are independent; do however change test_int by negatives,
**		large numbers, small numbers... As this is how the test suite was built
**		out to work. Some errors may arise for field length of number. Use
**		t_varint union provided. Also note you can give a decimal argument for
**		an int or a float to the program; otherwise, a default value is used.
**		Some good default values are provided below.
**
**	 -	Calling a va_arg() on a non-existing argument always causes a segfault.
**		One can handle this with #warning pragmas, but this use of macros is
**		forbidden within 42's 'norme'.
**
**	 -  Useful links:
**		http://kirste.userpage.fu-berlin.de/chemnet/use/info/libc/libc_19.html
**		https://en.wikipedia.org/wiki/C_localization_functions
**
**
**
**		FT_PRINTF BONUS FUNCTIONS TESTER	
**
**   IMPORTANT NOTES :
**
**	 -	Consider special case of float mentioned in: 
**		https://ryanstutorials.net/binary-tutorial/binary-floating-point.php
**
**	 -  To debug your own printf efficiently, I suggest you start the printf
**		calls inside your ft_printf subcalls by an appropriate number of tabs,
**		so that each subcall looks more and more "internal" and errors can be
**		found quickly. End all printf calls with \n to force flush the printf
**		buffer to stdout and have stdout be coherent with current function call.
**
**	 -	Some tests are given for special values and these tests are independent.
**
**	 -	Normalized floats refer to floats expressed as sign-exp-mantissa.
**		Denormalized floats are reserved, special values (NaN, +Inf, -Inf, etc).
**		Subnormal floats are floats with an exponent field of 0 which behave 
**			strangely. One of the default values is a subnormal.
**		https://randomascii.wordpress.com/2012/03/08/float-precisionfrom-zero-to-100-digits-2/
**
**	 -	Setlocale affects which separator is used for floats: ',' or '.'. To
**		avoid this behavior, our test calls setlocale(LC_ALL, "C") after checks
**		on strings. It also affects atof etc, so be careful
**
**	 -	Useful links:
**			- http://www.ryanjuckett.com/programming/printing-floating-point-numbers/
**			- https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html
**			- Steele, White, 1990 (Dragon4) ; Doitsch, 2004 (Grisu)
**			- https://github.com/libtom/libtommath
**			- D. Knuth AoCP, vol 2, chap 4, sec 4.2 & 4.3.
**
**
**
**			*** Check debug versions of the code at ***
**
**		 -->https://github.com/Fulguritude/42_ft_printf<--
**
**			 *** for more ideas or commented code. ***
**
**
** ---------------------------------------------------------------------------
*/



#if !INTTYPE_SHORTHANDS_DEFINED

typedef char			t_s8;
typedef short			t_s16;
typedef int				t_s32;
typedef	long			t_s64;

typedef	unsigned char	t_u8;
typedef	unsigned short	t_u16;
typedef	unsigned int	t_u32;
typedef	unsigned long	t_u64;

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
#endif





#if !STRREPLACE_DEFINED

void	*ft_ptrarrnew(t_u32 len)
{
	void	*result;

	if (!(result = ft_memalloc(sizeof(void*) * (len + 1))))
		return (NULL);
	return (result);
}

int			ft_stristr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return (0);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (needle[j] == haystack[i + j])
		{
			if (needle[j + 1] == '\0')
				return (i);
			if (haystack[i + j + 1] == '\0')
				return (-1);
			j++;
		}
		i++;
	}
	return (-1);
}

static void	ft_strnb_charnb_in_strls(const char **strls, int *w_nb, int *c_nb)
{
	int str_at;

	str_at = 0;
	while (strls[str_at])
	{
		*(c_nb) += ft_strlen(strls[str_at]);
		str_at++;
	}
	*w_nb = str_at;
}

static void	ft_build_str(char *dest, char const **strls, char const *sep)
{
	int i;
	int words;
	int chars;
	int sep_i;

	i = 0;
	sep_i = 0;
	words = -1;
	while (strls[++words])
	{
		chars = 0;
		while (strls[words][chars])
			dest[i++] = strls[words][chars++];
		sep_i = 0;
		while (sep[sep_i] && strls[words + 1])
			dest[i++] = sep[sep_i++];
	}
	dest[i] = '\0';
}

char		*ft_strlsjoin(char const **strls, char const *sep)
{
	char	*str;
	int		strls_str_nb;
	int		strls_char_nb;
	int		total_sep_char_nb;
	int		total_char_nb;

	if (!strls || !sep)
		return (NULL);
	strls_str_nb = 0;
	strls_char_nb = 0;
	ft_strnb_charnb_in_strls(strls, &strls_str_nb, &strls_char_nb);
	total_sep_char_nb = (strls_str_nb - 1) * ft_strlen(sep);
	total_char_nb = total_sep_char_nb + strls_char_nb;
	if (!(str = ft_strnew(total_char_nb + 1)))
		return (NULL);
	ft_build_str(str, strls, sep);
	return (str);
}

char		**ft_strdivide(const char *str, size_t n)
{
	char	**strls;
	int		lines;
	size_t	len;
	size_t	i;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	lines = len % n == 0 ? len / n : len / n + 1;
	if (lines == 0 || !(strls = (char**)ft_ptrarrnew(lines)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (i + n < len)
			strls[i / n] = ft_strsub(str, i, n);
		else
			strls[i / n] = ft_strdup(str + i);
		i += n;
	}
	strls[lines] = NULL;
	return (strls);
}

void		ft_strlsdel(char ***a_strls)
{
	int		i;

	if (a_strls && *a_strls)
	{
		i = 0;
		while ((*a_strls)[i])
		{
			ft_strdel((*a_strls) + i);
			++i;
		}
		free(*a_strls);
		*a_strls = NULL;
	}
}

static t_u32	count_distinct_sub_in_str(char const *str, char const *sub)
{
	t_u32	occ;
	t_u32	i;
	t_u32	j;

	occ = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && sub[j] && str[i + j] == sub[j])
		{
			if (sub[j + 1] == '\0')
			{
				++occ;
				i += j;
				break ;
			}
			++j;
		}
		++i;
	}
	return (occ);
}

static char		*get_next_chunk(char const *str, char const *sub, t_u32 *i)
{
	char	*result;
	t_u32	sub_len;
	t_u32	str_len;
	int		new_len;

	sub_len = ft_strlen(sub);
	str_len = ft_strlen(str);
	new_len = ft_stristr(str + *i, sub);
	if (new_len > -1)
	{
		result = ft_strsub(str, *i, (t_u32)new_len);
		*i += new_len + sub_len * (new_len != -1);
	}
	else
	{
		result = ft_strdup(str + *i);
		*i = str_len;
	}
	return (result);
}

char			**ft_strsplitstr(char const *str, char const *sub)
{
	char	**result;
	t_u32	reslen;
	t_u32	i;
	t_u32	j;

	if (!str || !sub)
		return (NULL);
	if (sub[0] == '\0')
		return (ft_strdivide(str, 1));
	reslen = count_distinct_sub_in_str(str, sub) + 1;
	if (!(result = (char**)ft_ptrarrnew(reslen)))
		return (NULL);
	i = 0;
	j = 0;
	if (reslen == 1)
		result[0] = ft_strdup(str);
	else
		while (j < reslen)
		{
			result[j] = get_next_chunk(str, sub, &i);
			++j;			
		}
	return (result);
}

char	*ft_strreplace(char const *str, char const *sub, char const *rep)
{
	char	**strls;
	char	*result;

	strls = ft_strsplitstr(str, sub);
	result = ft_strlsjoin((char const **)strls, rep);
	ft_strlsdel(&strls);
	return (result);
}

void	ft_strreplace_inplace(char **a_str, char const *sub, char const *rep)
{
	char	*tmp;

	if (ft_stristr(*a_str, sub) == -1)
		return ;
	tmp = ft_strreplace(*a_str, sub, rep);
	ft_strdel(a_str);
	*a_str = tmp;
}
#endif







/*
** This function uses asprintf and compares both return value and string
** returned via pointer.
*/
static int	check_retvals(int j, int *return_values, char **a_str1, char *str2)
{
	static int		str_failures = 0;

	printf("\n");		

	#if VERBOSE
	if (return_values[j - 2] == return_values[j - 1])
	{
		printf(C_GREEN"\nReturn values EQUAL"C_RESET);
		#if SHOW_CORRECT_RESULT_COMPARISON
		printf("\nYOURS   :|%4d|\nEXPECTED:|%4d|\n", return_values[j - 2], return_values[j - 1]);
		#endif
	}
	else
	{
		printf(C_RED"\nReturn values UNEQUAL."C_RESET);
		printf("\nYOURS   :|%4d|\nEXPECTED:|%4d|\n", return_values[j - 2], return_values[j - 1]);
	}
	printf("\n");

	ft_strreplace_inplace(a_str1, "ft_", "   ");
	if (ft_strequ(*a_str1, str2))
	{
		printf(C_GREEN"\nStrings returned EQUAL"C_RESET);
		#if SHOW_CORRECT_RESULT_COMPARISON
		printf("\nYOURS   :|%s|\nEXPECTED:|%s|\n", *a_str1, str2);
		#endif
	}		
	else
	{
		printf(C_RED"\nStrings returned UNEQUAL. With 'ft_' removed appropriately :"C_RESET);
		printf("\nYOURS   :|%s|\nEXPECTED:|%s|\n", *a_str1, str2);
		++str_failures;
	}
	printf("\n");
	return (str_failures);
	#else
	return (-1);
	#endif
}







int		main(int argc, char **argv)
{
	char		*str1 = NULL;
	char		*str2 = NULL;
	char		*input = NULL;

/*
** A single argument can be given, this argument will be sent to both an atoi
** and an atod protocol. This is just to test values fast with test.out
** Extra values are ignored; you can look for some default values in the rest
** of the file.
*/
	if (argc > 1)
		input = argv[1];

#if MAIN_TESTS || FLOAT_BONUSES
	int			str_fails = -1;
	int 		i = -1;
	int 		j = 0;
	int 		return_values[1000];
	t_varint	vint;

// Make sure to have your uatoi handle unsigned long, or just use strtoul
	t_u32		test_int	= input ? strtoul(input, NULL, 10) : 1010101010;
//-123; //123 is ..0007B in memory; -123 is ..FFF85 in memory
//	long		test_int2	= input ? strtol(input, NULL, 10) : -0x123456789ABCDEF0;
//-123456; //123456 is ..0001E240 in memory; -123456 is ..
	vint.sl					= input ? strtoul(input, NULL, 10) : 1234567890123;

/*
** Before setlocale
** Note that the first test is %c with zero: this is important for check_retvals
*/

# if MAIN_TESTS
#  if STR_HANDLER
//	char		*null = NULL;
//	wchar_t		*wcnull = NULL;


	printf(C_YELLOW"\n/!\\ Note that our string comparison test is not reliable for %%c with argument zero."C_RESET);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%c with 0 : |%c|\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %%c with 0 : |%c|\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

#   if UNSET_LOCALE
	printf(C_YELLOW"\n/!\\ The 9 following tests are Unicode without a call to setlocale and are considered undefined."C_RESET);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%c L'é': %C\n", L'é');
	  return_values[j++] =    asprintf(&str2, "   printf %%c L'é': %C\n", L'é');
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%lc L'é': %lC\n", L'é');
	  return_values[j++] =    asprintf(&str2, "   printf %%lc L'é': %lC\n", L'é');
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%C L'é': %C\n", L'é');
	  return_values[j++] =    asprintf(&str2, "   printf %%C L'é': %C\n", L'é');
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%ls: %S\n", L"résumé S");
	  return_values[j++] =    asprintf(&str2, "   printf %%ls: %S\n", L"résumé S");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%S: %S\n", L"résumé S");
	  return_values[j++] =    asprintf(&str2, "   printf %%S: %S\n", L"résumé S");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%6ls: %6S\n", L"résumé S");
	  return_values[j++] =    asprintf(&str2, "   printf %%6ls: %6S\n", L"résumé S");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%6S: %6S\n", L"résumé S");
	  return_values[j++] =    asprintf(&str2, "   printf %%6S: %6S\n", L"résumé S");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%.6ls: %.6S\n", L"résumé S");
	  return_values[j++] =    asprintf(&str2, "   printf %%.6ls: %.6S\n", L"résumé S");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%.6S: %.6S\n", L"résumé S");
	  return_values[j++] =    asprintf(&str2, "   printf %%.6S: %.6S\n", L"résumé S");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#   endif

/*
** After setlocale
*/
	setlocale(LC_ALL, "");

/*	printf(C_BLUE"\n\nTest %d (NULL CHECK):"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%s: %S\n", null);
	  return_values[j++] =    asprintf(&str2, "   printf %%s: %S\n", null);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d (NULL CHECK):"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%ls: %S\n", wcnull);
	  return_values[j++] =    asprintf(&str2, "   printf %%ls: %S\n", wcnull);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d (NULL CHECK):"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%S: %S\n", wcnull);
	  return_values[j++] =    asprintf(&str2, "   printf %%S: %S\n", wcnull);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
*/
/*
** %s basics
*/

	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.5S\n", "%.5S", L"ft_printF");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.5S\n", "%.5S", L"   printF");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %12S\n", "%12S", L"ft_printF");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %12S\n", "%12S", L"   printF");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %13.6S\n", "%13.6S", L"ft_printF");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %13.6S\n", "%13.6S", L"   printF");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-13.6S\n", "%-13.6S", L"ft_printF");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-13.6S\n", "%-13.6S", L"   printF");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#13.6S\n", "%#13.6S", "ft_printF");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#13.6S\n", "%#13.6S", "   printF");
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %013.6S\n", "%013.6S", "ft_printF");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %013.6S\n", "%013.6S", "   printF");
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives % 13.6S\n", "% 13.6S", "ft_printF");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives % 13.6S\n", "% 13.6S", "   printF");
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


printf("\n\n");
printf("\n\n");

	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%c L'é': %C\n", L'é');
	  return_values[j++] =    asprintf(&str2, "   printf %%c L'é': %C\n", L'é');
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %lC\n", L'é');
//	  return_values[j++] =    asprintf(&str2, "   printf: %lC\n", L'é');
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %S\n", L"résumé S");
//	  return_values[j++] =    asprintf(&str2, "   printf: %S\n", L"résumé S");
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%ls: %S\n", L"résumé S");
	  return_values[j++] =    asprintf(&str2, "   printf %%ls: %S\n", L"résumé S");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%S: %S\n", L"résumé S");
	  return_values[j++] =    asprintf(&str2, "   printf %%S: %S\n", L"résumé S");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%6ls: %6S\n", L"résumé S");
	  return_values[j++] =    asprintf(&str2, "   printf %%6ls: %6S\n", L"résumé S");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%6S: %6S\n", L"résumé S");
	  return_values[j++] =    asprintf(&str2, "   printf %%6S: %6S\n", L"résumé S");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%.6ls: %.6S\n", L"résumé S");
	  return_values[j++] =    asprintf(&str2, "   printf %%.6ls: %.6S\n", L"résumé S");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%.6S: %.6S\n", L"résumé S");
	  return_values[j++] =    asprintf(&str2, "   printf %%.6S: %.6S\n", L"résumé S");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%lls: %lS\n", L"résumé lS");
//	  return_values[j++] =    asprintf(&str2, "   printf %%lls: %lS\n", L"résumé lS");
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %S\n", L"résumé S");
//	  return_values[j++] =    asprintf(&str2, "   printf: %S\n", L"résumé S");
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %jS\n", L"résumé jS");
//	  return_values[j++] =    asprintf(&str2, "   printf: %jS\n", L"résumé jS");
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %hhS\n", L"résumé hhS");
//	  return_values[j++] =    asprintf(&str2, "   printf: %hhS\n", L"résumé hhS");
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %hhS\n", L"résumé hhS");
//	  return_values[j++] =    asprintf(&str2, "   printf: %hhS\n", L"résumé hhS");
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %hhS\n", "rasuma hhS");
//	  return_values[j++] =    asprintf(&str2, "   printf: %hhS\n", "rasuma hhS");
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.5S\n", "%.5S", L"éft_printF");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.5S\n", "%.5S", L"é   printF");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %12S\n", "%12S", L"éft_printF");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %12S\n", "%12S", L"é   printF");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %13.6S\n", "%13.6S", L"éft_printF");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %13.6S\n", "%13.6S", L"é   printF");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-13.6S\n", "%-13.6S", L"éft_printF");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-13.6S\n", "%-13.6S", L"é   printF");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#13.6S\n", "%#13.6S", L"éft_printF");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#13.6S\n", "%#13.6S", L"é   printF");
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+13.6S\n", "%+13.6S", L"éft_printF");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+13.6S\n", "%+13.6S", L"é   printF");
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %013.6S\n", "%013.6S", L"éft_printF");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %013.6S\n", "%013.6S", L"é   printF");
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

printf("\n\n");
printf("\n\n");


//les é comptent pour pile 2 bytes. Remarquez que le .5 ne fait afficher que 2 é sur 3 par la suite
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.5S\n", "%.5S", L"éééft_printF");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.5S\n", "%.5S", L"ééé   printF");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.6S\n", "%.6S", L"éééft_printF");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.6S\n", "%.6S", L"ééé   printF");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.6S\n", "%.6S", L"ééôft_printF");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.6S\n", "%.6S", L"ééô   printF");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %12S\n", "%12S", L"éééft_printF");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %12S\n", "%12S", L"ééé   printF");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %13.6S\n", "%13.6S", L"éééft_printF");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %13.6S\n", "%13.6S", L"ééé   printF");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-13.6S\n", "%-13.6S", L"éééft_printF");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-13.6S\n", "%-13.6S", L"ééé   printF");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#13.6S\n", "%#13.6S", L"éééft_printF");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#13.6S\n", "%#13.6S", L"ééé   printF");
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0-13.6S\n", "%0-13.6S", L"éééft_printF");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0-13.6S\n", "%0-13.6S", L"ééé   printF");
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %013.6S\n", "%013.6S", L"éééft_printF");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %013.6S\n", "%013.6S", L"ééé   printF");
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	setlocale(LC_ALL, "C");

#  endif

#  if INT_HANDLER
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printF\n");
	  return_values[j++] =    asprintf(&str2, "   printF\n");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%\n");
	  return_values[j++] =    asprintf(&str2, "   printf %%\n");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %D\n", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf %D\n", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_%sF\n", "print");
	  return_values[j++] =    asprintf(&str2, "   %sF\n", "print");
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#X\n", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf %#X\n", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %D\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %D\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %U\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %U\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %O\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %O\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %X\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %X\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %X\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %X\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %3D\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %3D\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %3U\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %3U\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %3O\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %3O\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %3X\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %3X\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %3X\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %3X\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.0D\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %.0D\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.0U\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %.0U\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.0O\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %.0O\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.0X\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %.0X\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.0X\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %.0X\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.-4D\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %.-4D\n", 0);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.-4U\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %.-4U\n", 0);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.-4O\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %.-4O\n", 0);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.-4X\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %.-4X\n", 0);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.-4X\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %.-4X\n", 0);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %5.0D\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %5.0D\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %5.0U\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %5.0U\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %5.0O\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %5.0O\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %5.0X\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %5.0X\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %5.0X\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %5.0X\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

#if 0
//0 works weirdly for a long in printf it seems. Causes a "stack smashinG" error
	long long_zero = 0;

	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %lD\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %lD\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %lU\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %lU\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %lO\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %lO\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %lX\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %lX\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %lX\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %lX\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %3lD\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %3lD\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %3lU\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %3lU\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %3lO\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %3lO\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %3lX\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %3lX\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %3lX\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %3lX\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.0lD\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %.0lD\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.0lU\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %.0lU\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.0lO\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %.0lO\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.0lX\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %.0lX\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.0lX\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %.0lX\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.-4lD\n", long_zero);
//	  return_values[j++] =    asprintf(&str2, "   printf %.-4lD\n", long_zero);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.-4lU\n", long_zero);
//	  return_values[j++] =    asprintf(&str2, "   printf %.-4lU\n", long_zero);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.-4lO\n", long_zero);
//	  return_values[j++] =    asprintf(&str2, "   printf %.-4lO\n", long_zero);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.-4lX\n", long_zero);
//	  return_values[j++] =    asprintf(&str2, "   printf %.-4lX\n", long_zero);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.-4lX\n", long_zero);
//	  return_values[j++] =    asprintf(&str2, "   printf %.-4lX\n", long_zero);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %5.0lD\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %5.0lD\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %5.0lU\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %5.0lU\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %5.0lO\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %5.0lO\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %5.0lX\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %5.0lX\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %5.0lX\n", long_zero);
	  return_values[j++] =    asprintf(&str2, "   printf %5.0lX\n", long_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#endif

	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %+D\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %+D\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %+.0D\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %+.0D\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %+.0U\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %+.0U\n", 0);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %+.0O\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %+.0O\n", 0);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %+.0X\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %+.0X\n", 0);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %+.0X\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %+.0X\n", 0);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf % .0D\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf % .0D\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf % .0U\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf % .0U\n", 0);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf % .0O\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf % .0O\n", 0);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf % .0X\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf % .0X\n", 0);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf % .0X\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf % .0X\n", 0);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#.0D\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %#.0D\n", 0);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#.0U\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %#.0U\n", 0);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#.0O\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %#.0O\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#.0X\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %#.0X\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#.0X\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %#.0X\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#5.0D\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %#5.0D\n", 0);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#5.0U\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %#5.0U\n", 0);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#5.0O\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %#5.0O\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#5.0X\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %#5.0X\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#5.0X\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %#5.0X\n", 0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#if 0
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#-+05.5d and %#-+06.5D\n", test_int2, test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf %#-+05.5d and %#-+06.5D\n", test_int2, test_int);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %+8.5d and %+8.5D\n", test_int2, test_int);
	  return_values[j++] =    asprintf(&str2, "   printf %+8.5d and %+8.5D\n", test_int2, test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %-+8.5d and %-+8.5D\n", test_int2, test_int);
	  return_values[j++] =    asprintf(&str2, "   printf %-+8.5d and %-+8.5D\n", test_int2, test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %0+8.5d and %0+8.5D\n", test_int2, test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf %0+8.5d and %0+8.5D\n", test_int2, test_int);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %-+5.5d and %-+5.5D\n", test_int2, test_int);
	  return_values[j++] =    asprintf(&str2, "   printf %-+5.5d and %-+5.5D\n", test_int2, test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %-+4.5d and %-+4.5D\n", test_int2, test_int);
	  return_values[j++] =    asprintf(&str2, "   printf %-+4.5d and %-+4.5D\n", test_int2, test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %-+3.5d and %-+3.5D\n", test_int2, test_int);
	  return_values[j++] =    asprintf(&str2, "   printf %-+3.5d and %-+3.5D\n", test_int2, test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %-+5.5d and %-+3.6D\n", test_int2, test_int);
	  return_values[j++] =    asprintf(&str2, "   printf %-+5.5d and %-+3.6D\n", test_int2, test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %d in octal : %O\n", test_int, test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %d in octal : %O\n", test_int, test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %d in octal : %#O\n", test_int, test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %d in octal : %#O\n", test_int, test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#endif

printf("\n\n\n");

/*
** Len flags
*/
//TODO add len flag tests in main_asprintf

	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %hhD\n", "%hhD", vint.sc);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %hhD\n", "%hhD", vint.sc);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %hD\n", "%hD", vint.ss);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %hD\n", "%hD", vint.ss);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %lD\n", "%lD", vint.sl);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %lD\n", "%lD", vint.sl);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %llD\n", "%llD", (long long) vint.sl);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %llD\n", "%llD", (long long) vint.sl);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %hhU\n", "%hhU", vint.uc);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %hhU\n", "%hhU", vint.uc);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %hU\n", "%hU", vint.us);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %hU\n", "%hU", vint.us);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %lU\n", "%lU", vint.ul);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %lU\n", "%lU", vint.ul);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %llU\n", "%llU", (long long) vint.ul);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %llU\n", "%llU", (long long) vint.ul);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

printf("\n\n");
printf("\n\n");

	unsigned int		part_ad = (unsigned int)(long unsigned int)&i;
	long unsigned int	whole_ad = (long unsigned int)&i;

	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %p\n", "%p", &i);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %p\n", "%p", &i);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %15p\n", "%15p", &i);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %15p\n", "%15p", &i);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %013p\n", "%013p", &i);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %013p\n", "%013p", &i);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %13.5p\n", "%13.5p", &i);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %13.5p\n", "%13.5p", &i);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %X\n", "%X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %X\n", "%X", part_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %X\n", "%X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %X\n", "%X", part_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %lX\n", "%lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %lX\n", "%lX", whole_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %lX\n", "%lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %lX\n", "%lX", whole_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);



	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#X\n", "%#X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#X\n", "%#X", part_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#X\n", "%#X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#X\n", "%#X", part_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#lX\n", "%#lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#lX\n", "%#lX", whole_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#lX\n", "%#lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#lX\n", "%#lX", whole_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);



	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15X\n", "%.15X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15X\n", "%.15X", part_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15X\n", "%.15X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15X\n", "%.15X", part_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15lX\n", "%.15lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15lX\n", "%.15lX", whole_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15lX\n", "%.15lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15lX\n", "%.15lX", whole_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);



	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.15X\n", "%#.15X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.15X\n", "%#.15X", part_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.15X\n", "%#.15X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.15X\n", "%#.15X", part_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.15lX\n", "%#.15lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.15lX\n", "%#.15lX", whole_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.15lX\n", "%#.15lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.15lX\n", "%#.15lX", whole_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);



	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15X\n", "%20.15X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15X\n", "%20.15X", part_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15X\n", "%20.15X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15X\n", "%20.15X", part_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15lX\n", "%20.15lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15lX\n", "%20.15lX", whole_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15lX\n", "%20.15lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15lX\n", "%20.15lX", whole_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);



	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#20.15X\n", "%#20.15X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#20.15X\n", "%#20.15X", part_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#20.15X\n", "%#20.15X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#20.15X\n", "%#20.15X", part_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#20.15lX\n", "%#20.15lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#20.15lX\n", "%#20.15lX", whole_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#20.15lX\n", "%#20.15lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#20.15lX\n", "%#20.15lX", whole_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);



	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20X\n", "%20X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20X\n", "%20X", part_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20X\n", "%20X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20X\n", "%20X", part_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20lX\n", "%20lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20lX\n", "%20lX", whole_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20lX\n", "%20lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20lX\n", "%20lX", whole_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);



	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#20X\n", "%#20X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#20X\n", "%#20X", part_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#20X\n", "%#20X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#20X\n", "%#20X", part_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#20lX\n", "%#20lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#20lX\n", "%#20lX", whole_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#20lX\n", "%#20lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#20lX\n", "%#20lX", whole_ad);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


printf("\n\n");
printf("\n\n");


//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0.2D\n", "%0.2D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0.2D\n", "%0.2D", test_int);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %2D\n", "%2D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %2D\n", "%2D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.3D\n", "%.3D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.3D\n", "%.3D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %2.3D\n", "%2.3D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %2.3D\n", "%2.3D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %4.3D\n", "%4.3D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %4.3D\n", "%4.3D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %5D\n", "%5D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %5D\n", "%5D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.2D\n", "%.2D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.2D\n", "%.2D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %5.2D\n", "%5.2D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %5.2D\n", "%5.2D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.5D\n", "%.5D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.5D\n", "%.5D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %2.5D\n", "%2.5D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %2.5D\n", "%2.5D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %4.5D\n", "%4.5D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %4.5D\n", "%4.5D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %06D\n", "%06D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %06D\n", "%06D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-6D\n", "%-6D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-6D\n", "%-6D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+6D\n", "%+6D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+6D\n", "%+6D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+-6D\n", "%+-6D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+-6D\n", "%+-6D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0+6D\n", "%0+6D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0+6D\n", "%0+6D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0+D\n", "%0+D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0+D\n", "%0+D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+D\n", "%+D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+D\n", "%+D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.2D\n", "%-.2D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.2D\n", "%-.2D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+.2D\n", "%+.2D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+.2D\n", "%+.2D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+-.2D\n", "%+-.2D", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+-.2D\n", "%+-.2D", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


printf("\n\n");
printf("\n\n");


//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+O\n", "%+O", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+O\n", "%+O", test_int);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %5O\n", "%5O", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %5O\n", "%5O", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.5O\n", "%.5O", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.5O\n", "%.5O", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.2O\n", "%.2O", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.2O\n", "%.2O", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.2O\n", "%#.2O", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.2O\n", "%#.2O", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %2.5O\n", "%2.5O", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %2.5O\n", "%2.5O", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %4.5O\n", "%4.5O", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %4.5O\n", "%4.5O", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#4O\n", "%#4O", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#4O\n", "%#4O", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.5O\n", "%#.5O", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.5O\n", "%#.5O", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#4.5O\n", "%#4.5O", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#4.5O\n", "%#4.5O", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#5O\n", "%#5O", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#5O\n", "%#5O", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#06O\n", "%#06O", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#06O\n", "%#06O", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#O\n", "%#O", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#O\n", "%#O", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#6O\n", "%#6O", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#6O\n", "%#6O", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#-6O\n", "%#-6O", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#-6O\n", "%#-6O", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#06O\n", "%#06O", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#06O\n", "%#06O", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#0O\n", "%#0O", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#0O\n", "%#0O", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.0O\n", "%#.0O", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.0O\n", "%#.0O", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);



printf("\n\n");
printf("\n\n");


//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+X\n", "%+X", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+X\n", "%+X", test_int);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#0-X\n", "%#0-X", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#0-X\n", "%#0-X", test_int);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#0-6X\n", "%#0-6X", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#0-6X\n", "%#0-6X", test_int);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %5X\n", "%5X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %5X\n", "%5X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.5X\n", "%.5X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.5X\n", "%.5X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.2X\n", "%.2X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.2X\n", "%.2X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.2X\n", "%#.2X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.2X\n", "%#.2X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %2.5X\n", "%2.5X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %2.5X\n", "%2.5X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %4.5X\n", "%4.5X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %4.5X\n", "%4.5X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#4.5X\n", "%#4.5X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#4.5X\n", "%#4.5X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#5X\n", "%#5X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#5X\n", "%#5X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#06X\n", "%#06X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#06X\n", "%#06X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#6X\n", "%#6X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#6X\n", "%#6X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#0X\n", "%#0X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#0X\n", "%#0X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#X\n", "%#X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#X\n", "%#X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


printf("\n\n");
printf("\n\n");


//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+X\n", "%+X", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+X\n", "%+X", test_int);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#0-X\n", "%#0-X", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#0-X\n", "%#0-X", test_int);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#-06X\n", "%#-06X", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#-06X\n", "%#-06X", test_int);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#0-6X\n", "%#0-6X", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#0-6X\n", "%#0-6X", test_int);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %5X\n", "%5X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %5X\n", "%5X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.5X\n", "%.5X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.5X\n", "%.5X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.2X\n", "%.2X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.2X\n", "%.2X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.2X\n", "%#.2X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.2X\n", "%#.2X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %2.5X\n", "%2.5X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %2.5X\n", "%2.5X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %4.5X\n", "%4.5X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %4.5X\n", "%4.5X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#4.5X\n", "%#4.5X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#4.5X\n", "%#4.5X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#5X\n", "%#5X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#5X\n", "%#5X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#06X\n", "%#06X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#06X\n", "%#06X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);



	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#6X\n", "%#6X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#6X\n", "%#6X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#0X\n", "%#0X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#0X\n", "%#0X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#X\n", "%#X", test_int);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#X\n", "%#X", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


printf("\n\n");
printf("\n\n");


//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#U\n", "%#U", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#U\n", "%#U", test_int);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+U\n", "%+U", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+U\n", "%+U", test_int);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0-U\n", "%0-U", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0-U\n", "%0-U", test_int);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0.2U\n", "%0.2U", test_int);
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0.2U\n", "%0.2U", test_int);
//	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %5U\n", "%5U", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %5U\n", "%5U", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.5U\n", "%.5U", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.5U\n", "%.5U", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.2U\n", "%.2U", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.2U\n", "%.2U", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.2U\n", "%-.2U", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.2U\n", "%-.2U", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %2.5U\n", "%2.5U", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %2.5U\n", "%2.5U", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %4.5U\n", "%4.5U", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %4.5U\n", "%4.5U", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %4.5U\n", "%4.5U", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %4.5U\n", "%4.5U", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %5U\n", "%5U", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %5U\n", "%5U", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %6U\n", "%6U", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %6U\n", "%6U", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0U\n", "%0U", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0U\n", "%0U", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %06U\n", "%06U", test_int);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %06U\n", "%06U", test_int);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#  endif
# endif

# if FLOAT_BONUSES
#  if SPECIAL_CASES
	//these values are also worth checking with width etc
	double	plus_inf = 1./0.; //INF
	double	minus_inf = -(1./0.);
	double	plus_zero = 0x0.000000000000p+0;
	double	minus_zero = -0x0.000000000000p+0;
	double	dbl_max = DBL_MAX;
	double	dbl_min = -DBL_MAX;
	double	mach_err = DBL_EPSILON;
	double	not_a_nb = 0.0f / 0.0f; //NAN
	double	negnot_a_nb = -(0.0f / 0.0f);

#   if PERCENT_fF
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-inf) gives %lF\n", "%lF", minus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-inf) gives %lF\n", "%lF", minus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+inf) gives %lF\n", "%lF", plus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+inf) gives %lF\n", "%lF", plus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (eps) gives %lF\n", "%lF", mach_err);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (eps) gives %lF\n", "%lF", mach_err);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %lF\n", "%lF", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %lF\n", "%lF", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %lF\n", "%lF", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %lF\n", "%lF", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %+lF\n", "%+lF", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %+lF\n", "%+lF", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %+lF\n", "%+lF", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %+lF\n", "%+lF", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (NaN) gives %lF\n", "%lF", not_a_nb);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (NaN) gives %lF\n", "%lF", not_a_nb);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-NaN) gives %lF\n", "%lF", negnot_a_nb);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-NaN) gives %lF\n", "%lF", negnot_a_nb);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-DBL_MAX) gives %lF\n", "%lF", dbl_min);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-DBL_MAX) gives %lF\n", "%lF", dbl_min);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (DBL_MAX) gives %lF\n", "%lF", dbl_max);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (DBL_MAX) gives %lF\n", "%lF", dbl_max);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-inf) gives %.300lF\n", "%.300lF", minus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-inf) gives %.300lF\n", "%.300lF", minus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+inf) gives %.300lF\n", "%.300lF", plus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+inf) gives %.300lF\n", "%.300lF", plus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (eps) gives %.300lF\n", "%.300lF", mach_err);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (eps) gives %.300lF\n", "%.300lF", mach_err);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %.300lF\n", "%.300lF", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %.300lF\n", "%.300lF", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %.300lF\n", "%.300lF", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %.300lF\n", "%.300lF", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %+.300lF\n", "%+.300lF", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %+.300lF\n", "%+.300lF", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %+.300lF\n", "%+.300lF", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %+.300lF\n", "%+.300lF", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (NaN) gives %.300lF\n", "%.300lF", not_a_nb);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (NaN) gives %.300lF\n", "%.300lF", not_a_nb);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-NaN) gives %.300lF\n", "%.300lF", negnot_a_nb);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-NaN) gives %.300lF\n", "%.300lF", negnot_a_nb);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-DBL_MAX) gives %.300lF\n", "%.300lF", dbl_min);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-DBL_MAX) gives %.300lF\n", "%.300lF", dbl_min);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (DBL_MAX) gives %.300lF\n", "%.300lF", dbl_max);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (DBL_MAX) gives %.300lF\n", "%.300lF", dbl_max);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#   endif


#   if PERCENT_eE
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-inf) gives %lE\n", "%lE", minus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-inf) gives %lE\n", "%lE", minus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+inf) gives %lE\n", "%lE", plus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+inf) gives %lE\n", "%lE", plus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (eps) gives %lE\n", "%lE", mach_err);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (eps) gives %lE\n", "%lE", mach_err);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %lE\n", "%lE", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %lE\n", "%lE", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %lE\n", "%lE", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %lE\n", "%lE", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %+lE\n", "%+lE", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %+lE\n", "%+lE", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %+lE\n", "%+lE", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %+lE\n", "%+lE", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (NaN) gives %lE\n", "%lE", not_a_nb);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (NaN) gives %lE\n", "%lE", not_a_nb);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-DBL_MAX) gives %lE\n", "%lE", dbl_min);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-DBL_MAX) gives %lE\n", "%lE", dbl_min);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (DBL_MAX) gives %lE\n", "%lE", dbl_max);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (DBL_MAX) gives %lE\n", "%lE", dbl_max);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#   endif


#   if PERCENT_gG
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-inf) gives %lG\n", "%lG", minus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-inf) gives %lG\n", "%lG", minus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+inf) gives %lG\n", "%lG", plus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+inf) gives %lG\n", "%lG", plus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (eps) gives %lG\n", "%lG", mach_err);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (eps) gives %lG\n", "%lG", mach_err);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %lG\n", "%lG", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %lG\n", "%lG", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %lG\n", "%lG", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %lG\n", "%lG", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %+lG\n", "%+lG", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %+lG\n", "%+lG", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %+lG\n", "%+lG", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %+lG\n", "%+lG", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (NaN) gives %lG\n", "%lG", not_a_nb);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (NaN) gives %lG\n", "%lG", not_a_nb);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-DBL_MAX) gives %lG\n", "%lG", dbl_min);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-DBL_MAX) gives %lG\n", "%lG", dbl_min);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (DBL_MAX) gives %lG\n", "%lG", dbl_max);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (DBL_MAX) gives %lG\n", "%lG", dbl_max);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#   endif


#   if PERCENT_aA
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-inf) gives %lA\n", "%lA", minus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-inf) gives %lA\n", "%lA", minus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+inf) gives %lA\n", "%lA", plus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+inf) gives %lA\n", "%lA", plus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (eps) gives %lA\n", "%lA", mach_err);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (eps) gives %lA\n", "%lA", mach_err);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %lA\n", "%lA", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %lA\n", "%lA", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %lA\n", "%lA", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %lA\n", "%lA", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %+lA\n", "%+lA", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %+lA\n", "%+lA", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %+lA\n", "%+lA", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %+lA\n", "%+lA", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (NaN) gives %lA\n", "%lA", not_a_nb);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (NaN) gives %lA\n", "%lA", not_a_nb);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-DBL_MAX) gives %lA\n", "%lA", dbl_min);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-DBL_MAX) gives %lA\n", "%lA", dbl_min);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (DBL_MAX) gives %lA\n", "%lA", dbl_max);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (DBL_MAX) gives %lA\n", "%lA", dbl_max);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#   endif
#  endif



#  if NORMAL_CASES
	float 	f = input ? atof(input) : 99.9999;
//-0.9999; //0.55555; // 0xf.edcba012345p-64;		//other vals: 123.456789; //1e+250;//2.;
	double 	d = input ? atof(input) : -0x0.00034543210p-1023;
//1e+23;//-0x1.123456789abcdp+1010;//1e+250;//16.125; //-0x1.123456789abcdp+1010;	//other vals: 1234567.8987654321; 0.000002432543654332000; 1e+23; 1e+20; 

#   if PERCENT_fF
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %F\n", "%F", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %F\n", "%F", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0F\n", "%.0F", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0F\n", "%.0F", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0F\n", "%.0F", 0.0);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0F\n", "%.0F", 0.0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+F\n", "%+F", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+F\n", "%+F", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);	
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0F\n", "%0F", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0F\n", "%0F", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#F\n", "%#F", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#F\n", "%#F", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.0F\n", "%#.0F", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.0F\n", "%#.0F", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.3F\n", "%-.3F", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.3F\n", "%-.3F", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.3F\n", "%.3F", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.3F\n", "%.3F", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15F\n", "%.15F", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15F\n", "%.15F", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20F\n", "%20F", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20F\n", "%20F", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020F\n", "%020F", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020F\n", "%020F", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15F\n", "%20.15F", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15F\n", "%20.15F", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020.15F\n", "%020.15F", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020.15F\n", "%020.15F", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.15F\n", "%-20.15F", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.15F\n", "%-20.15F", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.3F\n", "%-20.3F", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.3F\n", "%-20.3F", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#   endif


#   if PERCENT_eE
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %E\n", "%E", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %E\n", "%E", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0E\n", "%.0E", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0E\n", "%.0E", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0E\n", "%.0E", 0.0);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0E\n", "%.0E", 0.0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+E\n", "%+E", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+E\n", "%+E", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);	
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0E\n", "%0E", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0E\n", "%0E", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#E\n", "%#E", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#E\n", "%#E", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.0E\n", "%#.0E", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.0E\n", "%#.0E", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.3E\n", "%-.3E", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.3E\n", "%-.3E", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.3E\n", "%.3E", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.3E\n", "%.3E", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15E\n", "%.15E", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15E\n", "%.15E", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20E\n", "%20E", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20E\n", "%20E", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020E\n", "%020E", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020E\n", "%020E", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15E\n", "%20.15E", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15E\n", "%20.15E", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020.15E\n", "%020.15E", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020.15E\n", "%020.15E", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.15E\n", "%-20.15E", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.15E\n", "%-20.15E", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.3E\n", "%-20.3E", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.3E\n", "%-20.3E", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#   endif


#   if PERCENT_aA
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %A\n", "%A", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %A\n", "%A", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0A\n", "%.0A", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0A\n", "%.0A", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0A\n", "%.0A", 0.0);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0A\n", "%.0A", 0.0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+A\n", "%+A", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+A\n", "%+A", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);	
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0A\n", "%0A", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0A\n", "%0A", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#A\n", "%#A", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#A\n", "%#A", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.0A\n", "%#.0A", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.0A\n", "%#.0A", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.3A\n", "%-.3A", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.3A\n", "%-.3A", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.3A\n", "%.3A", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.3A\n", "%.3A", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15A\n", "%.15A", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15A\n", "%.15A", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20A\n", "%20A", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20A\n", "%20A", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020A\n", "%020A", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020A\n", "%020A", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15A\n", "%20.15A", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15A\n", "%20.15A", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020.15A\n", "%020.15A", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020.15A\n", "%020.15A", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.15A\n", "%-20.15A", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.15A\n", "%-20.15A", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.3A\n", "%-20.3A", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.3A\n", "%-20.3A", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#   endif


#   if PERCENT_gG
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %G\n", "%G", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %G\n", "%G", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0G\n", "%.0G", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0G\n", "%.0G", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0G\n", "%.0G", 0.0);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0G\n", "%.0G", 0.0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+G\n", "%+G", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+G\n", "%+G", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);	
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0G\n", "%0G", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0G\n", "%0G", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#G\n", "%#G", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#G\n", "%#G", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.0G\n", "%#.0G", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.0G\n", "%#.0G", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.3G\n", "%-.3G", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.3G\n", "%-.3G", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.3G\n", "%.3G", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.3G\n", "%.3G", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15G\n", "%.15G", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15G\n", "%.15G", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20G\n", "%20G", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20G\n", "%20G", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020G\n", "%020G", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020G\n", "%020G", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15G\n", "%20.15G", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15G\n", "%20.15G", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020.15G\n", "%020.15G", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020.15G\n", "%020.15G", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.15G\n", "%-20.15G", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.15G\n", "%-20.15G", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.3G\n", "%-20.3G", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.3G\n", "%-20.3G", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#   endif

/*
** fl_l
*/

#   if PERCENT_fF
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %lF\n", "%lF", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %lF\n", "%lF", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0lF\n", "%.0lF", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0lF\n", "%.0lF", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0lF\n", "%.0lF", 0.0);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0lF\n", "%.0lF", 0.0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+lF\n", "%+lF", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+lF\n", "%+lF", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);	
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0lF\n", "%0lF", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0lF\n", "%0lF", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#lF\n", "%#lF", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#lF\n", "%#lF", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.0lF\n", "%#.0lF", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.0lF\n", "%#.0lF", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.3lF\n", "%-.3lF", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.3lF\n", "%-.3lF", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.3lF\n", "%.3lF", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.3lF\n", "%.3lF", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15lF\n", "%.15lF", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15lF\n", "%.15lF", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20lF\n", "%20lF", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20lF\n", "%20lF", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020lF\n", "%020lF", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020lF\n", "%020lF", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15lF\n", "%20.15lF", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15lF\n", "%20.15lF", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020.15lF\n", "%020.15lF", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020.15lF\n", "%020.15lF", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.15lF\n", "%-20.15lF", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.15lF\n", "%-20.15lF", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.3lF\n", "%-20.3lF", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.3lF\n", "%-20.3lF", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.360lF\n", "%.360lF", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.360lF\n", "%.360lF", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#   endif


#   if PERCENT_eE
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %lE\n", "%lE", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %lE\n", "%lE", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0lE\n", "%.0lE", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0lE\n", "%.0lE", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0lE\n", "%.0lE", 0.0);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0lE\n", "%.0lE", 0.0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+lE\n", "%+lE", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+lE\n", "%+lE", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);	
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0lE\n", "%0lE", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0lE\n", "%0lE", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#lE\n", "%#lE", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#lE\n", "%#lE", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.0lE\n", "%#.0lE", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.0lE\n", "%#.0lE", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.3lE\n", "%-.3lE", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.3lE\n", "%-.3lE", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.3lE\n", "%.3lE", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.3lE\n", "%.3lE", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15lE\n", "%.15lE", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15lE\n", "%.15lE", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20lE\n", "%20lE", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20lE\n", "%20lE", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020lE\n", "%020lE", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020lE\n", "%020lE", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15lE\n", "%20.15lE", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15lE\n", "%20.15lE", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020.15lE\n", "%020.15lE", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020.15lE\n", "%020.15lE", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.15lE\n", "%-20.15lE", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.15lE\n", "%-20.15lE", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.3lE\n", "%-20.3lE", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.3lE\n", "%-20.3lE", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#   endif


#   if PERCENT_aA
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %lA\n", "%lA", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %lA\n", "%lA", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0lA\n", "%.0lA", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0lA\n", "%.0lA", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0lA\n", "%.0lA", 0.0);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0lA\n", "%.0lA", 0.0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+lA\n", "%+lA", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+lA\n", "%+lA", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);	
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0lA\n", "%0lA", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0lA\n", "%0lA", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#lA\n", "%#lA", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#lA\n", "%#lA", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.0lA\n", "%#.0lA", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.0lA\n", "%#.0lA", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.3lA\n", "%-.3lA", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.3lA\n", "%-.3lA", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.3lA\n", "%.3lA", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.3lA\n", "%.3lA", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15lA\n", "%.15lA", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15lA\n", "%.15lA", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20lA\n", "%20lA", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20lA\n", "%20lA", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020lA\n", "%020lA", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020lA\n", "%020lA", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15lA\n", "%20.15lA", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15lA\n", "%20.15lA", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020.15lA\n", "%020.15lA", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020.15lA\n", "%020.15lA", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.15lA\n", "%-20.15lA", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.15lA\n", "%-20.15lA", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.3lA\n", "%-20.3lA", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.3lA\n", "%-20.3lA", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#   endif


#   if PERCENT_gG
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %lG\n", "%lG", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %lG\n", "%lG", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0lG\n", "%.0lG", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0lG\n", "%.0lG", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0lG\n", "%.0lG", 0.0);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0lG\n", "%.0lG", 0.0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+lG\n", "%+lG", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+lG\n", "%+lG", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);	
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0lG\n", "%0lG", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0lG\n", "%0lG", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#lG\n", "%#lG", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#lG\n", "%#lG", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.0lG\n", "%#.0lG", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.0lG\n", "%#.0lG", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.3lG\n", "%-.3lG", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.3lG\n", "%-.3lG", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.3lG\n", "%.3lG", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.3lG\n", "%.3lG", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15lG\n", "%.15lG", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15lG\n", "%.15lG", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20lG\n", "%20lG", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20lG\n", "%20lG", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020lG\n", "%020lG", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020lG\n", "%020lG", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15lG\n", "%20.15lG", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15lG\n", "%20.15lG", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020.15lG\n", "%020.15lG", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020.15lG\n", "%020.15lG", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.15lG\n", "%-20.15lG", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.15lG\n", "%-20.15lG", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.3lG\n", "%-20.3lG", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.3lG\n", "%-20.3lG", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#   endif
#  endif
# endif

printf("\n\n");
printf(C_BLUE"\nTests on return values :"C_RESET);
printf("\n\n");


	int return_fails = 0;

	i = 0;
	while (i < j)
	{
		if (return_values[i] == return_values[i + 1])
			printf(C_GREEN"Test %3d: ft_printf %d ;    printf %d\n"C_RESET, i / 2, return_values[i], return_values[i + 1]);
		else
		{
			printf(C_RED"Test %3d: ft_printf %d ;    printf %d\n"C_RESET, i / 2, return_values[i], return_values[i + 1]);
			++return_fails;
		}
		i += 2;
	}
	if (str_fails == 0 && return_fails == 0)
	{
		printf(C_GREEN"\nThere are 0 failed tests based on both return values and str output values. Congratulations !"C_RESET);
		printf(C_MAGENTA"\n Have you checked for leaks yet ? ;) You do know about valgrind or the C flag -fsanitize=address and its accompanying libasan.a right ?\n"C_RESET);
	}
	else if (return_fails == 0)
	{
		printf(C_GREEN"\nThere are 0 failed tests based on return values."C_RESET);
		printf(C_YELLOW"\nTests on return values are mandatory but not sufficient."C_RESET);
		printf(C_RED"\nThere are %d failed tests based on str_output values.\n"C_RESET, str_fails);
	}
	else if (str_fails == 0)
	{
		printf(C_RED"\nThere are %d failed tests based on return values."C_RESET, return_fails);
		printf(C_GREEN"\nThere are 0 failed tests based on str output values."C_RESET);
		printf(C_YELLOW"\nTests on str output values are mandatory but not sufficient.\n"C_RESET);
	}
	else
	{
		printf(C_RED"\nThere are %d failed tests based on return values.\n"C_RESET, return_fails);
		printf(C_RED"\nThere are %d failed tests based on str_output values.\n"C_RESET, str_fails);
	}
	printf(C_YELLOW"\nNote that what precedes is untrustworthy because D, O and U specifiers are non-standard and have been commented out for the regular printf.\n"C_RESET); 
	printf("\n");
#endif


#if SMALL_BONUSES

printf("\n\n");
printf(C_BLUE"\nTests on functionalities not available in printf :"C_RESET);
printf("\n\n");

	char	*tmp;


#  if PERCENT_b
	printf(C_BLUE"Testing binary %%b: "C_RESET); printf("\n");
	ft_printf("\t%b\n", 0xAAAAAAAA);
	printf("Expected :\n\t10101010101010101010101010101010\n\n"); 

	printf(C_BLUE"Testing binary %%#b: "C_RESET); printf("\n");
	ft_printf("\t%#b\n", 0xAAAAAAAA);
	printf("Expected :\n\t0b10101010101010101010101010101010\n\n");
#  endif

#  if PERCENT_B
	printf(C_BLUE"Testing binary %%B: "C_RESET); printf("\n");
	ft_printf("\t%B\n", 0xAAAAAAAA);
	printf("Expected :\n\t10101010101010101010101010101010\n\n");
	printf(C_BLUE"Testing binary %%#B: "C_RESET); printf("\n");
	ft_printf("\t%#B\n", 0xAAAAAAAA);
	printf("Expected :\n\t0B10101010101010101010101010101010\n\n"); 
#  endif



#  if PERCENT_r
	printf(C_BLUE"Testing non-printables %%r: "C_RESET); printf("\n");
	printf(C_YELLOW"For what follows, no printable output should start with \"\\x\"."C_RESET); printf("\n");
	printf("  0 - ascii input \\x00 is unprintable. Because of how C strings work, this character is ignored.\n");
	for (i = 1; i < 256; ++i)
	{
		tmp = ft_strcnew(1, i);
		ft_printf("%3d - ascii input \\x%02x is %11s. ft_printf output is: %r\n",
			i, i, ft_isprint(i) ? "printable" : "unprintable", tmp);
		free(tmp);
	}	
#  endif



# if COLOR_BONUS
	printf(C_YELLOW"\n\nTwo examples to teach possible color usage that works by default for any C function that outputs to modern stdout. These are not tests, you should just look at the main."C_RESET); printf("\n");

	   printf(C_BLUE"\nTesting    printf BLUE."C_RESET); printf("\n");
	ft_printf(C_GREEN"Testing ft_printf GREEN."C_RESET); printf("\n");

	   printf("\n\x1b[34mTesting    printf BLUE.\x1b[0m"); printf("\n");
	ft_printf("\x1b[32mTesting ft_printf GREEN.\x1b[0m"); printf("\n");

	printf(C_YELLOW"\n\nThis function tests in-string shortcuts, each word should be its corresponding color and each semicolon should be white :"C_RESET); printf("\n");

	ft_printf("\n{red}red{eoc} ; {yellow}yellow{eoc} ; {green}green{eoc} ; {cyan}cyan{eoc} ; {blue}blue{eoc} ; {magenta}magenta{eoc}\n");
	ft_printf("\n{red}%s{eoc} ; {yellow}%s {eoc} ; {green}green, null_%c_char{eoc} ; {cyan}cyan, fake_eoc_%s_in_a_%%s{eoc} ; {blue}blue, %#+09x{eoc} ; {magenta} %s{eoc}\n", "red, {}only_a_%s_between{}", "yellow, {}trailing_space {}", 0, "{eoc}", 0x123456, "magenta, {} leading_space{}");
# endif

#endif

	return (0);
}
