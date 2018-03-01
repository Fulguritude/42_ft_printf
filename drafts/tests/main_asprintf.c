#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#include "../ft_printf.h"
#include <stdio.h>
#include <stdlib.h>

#define C_RED     "\x1b[31m"
#define C_GREEN   "\x1b[32m"
#define C_YELLOW  "\x1b[33m"
#define C_BLUE    "\x1b[34m"
#define C_MAGENTA "\x1b[35m"
#define C_CYAN    "\x1b[36m"
#define RESET     "\x1b[0m"

# define VAL_1	-123 //123 is ..0007B in memory; -123 is ..FFF85 in memory
# define VAL_2	-123456 //123456 is ..0001E240 in memory; -123456 is ..
# define VAL_3	1234567890123 //1234567890123


# define VERBOSE							1
# define SHOW_CORRECT_RESULT_COMPARISON 	0

/*
** ---------------------------------------------------------------------------
**
**		FT_PRINTF MAIN UNIT TESTER
**
**   IMPORTANT NOTES :
**
**   -	"#if 0" and "#endif" pragmas are used only to comment out text below for
**		readability in the stdout of the unit tests. Don't use multiline
**		comments to 'hide' code as these tend to mess things up.
**
**	 -	// commented lines correspond to printf values that cause warnings.
**		They are to be kept for future users to know which combinations are
**		undefined before adding unnecessary functionalities; as well as seeing
**		how various	printf implementations handle basic undefined outputs
**		(remove CFLAGS in Makefile beforehand).
**
**	 -  setlocale(LC_ALL, "") is called.
**
**	 -  To debug your own printf efficiently, I suggest you start the printf
**		calls inside your ft_printf subcalls by an appropriate number of tabs,
**		so that each subcall looks more and more "internal" and errors can be
**		found quickly. End all printf calls with \n to force flush the printf
**		buffer to stdout and have stdout be coherent with current function call.
**
**	 -	Tests on zero are independent; do however change VAL_1 etc by negatives,
**		large numbers, small numbers... As this is how the test suite was built
**		out to work. Some errors may arise for field length of number. Use
**		t_varint union provided.
**
**	 -	Calling a va_arg() on a non-existing argument always causes a segfault.
**
**		Check debug versions of the code on 
**			https://github.com/Fulguritude/42_ft_printf
**		for ideas.
**
** ---------------------------------------------------------------------------
*/



static int	check_retvals(int j, int *return_values, char **a_str1, char *str2)
{
	static int		str_failures = 0;

	printf("\n");		

	#if VERBOSE
	if (return_values[j - 2] == return_values[j - 1])
	{
		printf(C_GREEN"\nReturn values EQUAL"RESET);
		#if SHOW_CORRECT_RESULT_COMPARISON
		printf("\nYOURS   :|%4d|\nEXPECTED:|%4d|\n", return_values[j - 2], return_values[j - 1]);
		#endif
	}
	else
	{
		printf(C_RED"\nReturn values UNEQUAL."RESET);
		printf("\nYOURS   :|%4d|\nEXPECTED:|%4d|\n", return_values[j - 2], return_values[j - 1]);
	}
	printf("\n");

	if (j == 2)
		printf(C_YELLOW"/!\\ Note that our string comparison test is not reliable and thus omitted for %%c with argument zero."RESET);
	else if	(j <= 12)
		printf(C_YELLOW"/!\\ Note that our string comparison test is omitted because printf may segfault with multibytes when setlocale has not been called."RESET);
	else
	{
		ft_strreplace_inplace(a_str1, "ft_", "   ");
		if (ft_strequ(*a_str1, str2))
		{
			printf(C_GREEN"\nStrings returned EQUAL"RESET);
			#if SHOW_CORRECT_RESULT_COMPARISON
			printf("\nYOURS   :|%s|\nEXPECTED:|%s|\n", *a_str1, str2);
			#endif
		}		
		else
		{
			printf(C_RED"\nStrings returned UNEQUAL. With 'ft_' removed appropriately :"RESET);
			printf("\nYOURS   :|%s|\nEXPECTED:|%s|\n", *a_str1, str2);
			++str_failures;
		}
	}
	printf("\n");
	return (str_failures);
	#else
	return (-1);
	#endif
}

int main()
{
	int 		i = -1;
	int 		j = 0;
	int 		return_values[400];
	char		*str1 = NULL;
	char		*str2 = NULL;
	t_varint	vint;

	vint.sl = VAL_3;

/*
** Before setlocale
** Note that the first test is %c with zero: this is important for check_retvals
*/
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%c with 0 : |%c|\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %%c with 0 : |%c|\n", 0);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%c L'é': %c\n", L'é');
	  return_values[j++] =    asprintf(&str2, "   printf %%c L'é': %c\n", L'é');
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%lc L'é': %lc\n", L'é');
	  return_values[j++] =    asprintf(&str2, "   printf %%lc L'é': %lc\n", L'é');
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%C L'é': %C\n", L'é');
	  return_values[j++] =    asprintf(&str2, "   printf %%C L'é': %C\n", L'é');
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%ls: %ls\n", L"résumé ls");
	  return_values[j++] =    asprintf(&str2, "   printf %%ls: %ls\n", L"résumé ls");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%S: %S\n", L"résumé S");
	  return_values[j++] =    asprintf(&str2, "   printf %%S: %S\n", L"résumé S");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

/*
** After setlocale
*/
	setlocale(LC_ALL, "");

	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf\n");
	  return_values[j++] =    asprintf(&str2, "   printf\n");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%\n");
	  return_values[j++] =    asprintf(&str2, "   printf %%\n");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %d\n", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf %d\n", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_%sf\n", "print");
	  return_values[j++] =    asprintf(&str2, "   %sf\n", "print");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#x\n", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf %#x\n", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.0d\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %.0d\n", 0);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.0u\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %.0u\n", 0);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.0o\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %.0o\n", 0);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.0x\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %.0x\n", 0);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.0X\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %.0X\n", 0);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.-4d\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %.-4d\n", 0);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.-4u\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %.-4u\n", 0);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.-4o\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %.-4o\n", 0);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.-4x\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %.-4x\n", 0);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %.-4X\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %.-4X\n", 0);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %5.0d\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %5.0d\n", 0);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %5.0u\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %5.0u\n", 0);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %5.0o\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %5.0o\n", 0);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %5.0x\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %5.0x\n", 0);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %5.0X\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %5.0X\n", 0);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %+.0d\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %+.0d\n", 0);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %+.0u\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %+.0u\n", 0);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %+.0o\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %+.0o\n", 0);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %+.0x\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %+.0x\n", 0);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %+.0X\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %+.0X\n", 0);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf % .0d\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf % .0d\n", 0);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf % .0u\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf % .0u\n", 0);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf % .0o\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf % .0o\n", 0);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf % .0x\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf % .0x\n", 0);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf % .0X\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf % .0X\n", 0);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#.0d\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %#.0d\n", 0);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#.0u\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %#.0u\n", 0);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#.0o\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %#.0o\n", 0);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#.0x\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %#.0x\n", 0);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#.0X\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %#.0X\n", 0);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#5.0d\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %#5.0d\n", 0);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#5.0u\n", 0);
//	  return_values[j++] =    asprintf(&str2, "   printf %#5.0u\n", 0);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#5.0o\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %#5.0o\n", 0);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#5.0x\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %#5.0x\n", 0);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#5.0X\n", 0);
	  return_values[j++] =    asprintf(&str2, "   printf %#5.0X\n", 0);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %#-+05.5d and %#-+06.5d\n", VAL_2, VAL_1);
//	  return_values[j++] =    asprintf(&str2, "   printf %#-+05.5d and %#-+06.5d\n", VAL_2, VAL_1);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %+8.5d and %+8.5d\n", VAL_2, VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf %+8.5d and %+8.5d\n", VAL_2, VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %-+8.5d and %-+8.5d\n", VAL_2, VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf %-+8.5d and %-+8.5d\n", VAL_2, VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %0+8.5d and %0+8.5d\n", VAL_2, VAL_1);
//	  return_values[j++] =    asprintf(&str2, "   printf %0+8.5d and %0+8.5d\n", VAL_2, VAL_1);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %-+5.5d and %-+5.5d\n", VAL_2, VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf %-+5.5d and %-+5.5d\n", VAL_2, VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %-+4.5d and %-+4.5d\n", VAL_2, VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf %-+4.5d and %-+4.5d\n", VAL_2, VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %-+3.5d and %-+3.5d\n", VAL_2, VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf %-+3.5d and %-+3.5d\n", VAL_2, VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %-+5.5d and %-+3.6d\n", VAL_2, VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf %-+5.5d and %-+3.6d\n", VAL_2, VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %d in octal : %o\n", VAL_1, VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %d in octal : %o\n", VAL_1, VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %d in octal : %#o\n", VAL_1, VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %d in octal : %#o\n", VAL_1, VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

printf("\n\n\n");
	
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%c L'é': %c\n", L'é');
	  return_values[j++] =    asprintf(&str2, "   printf %%c L'é': %c\n", L'é');
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%lc L'é': %lc\n", L'é');
	  return_values[j++] =    asprintf(&str2, "   printf %%lc L'é': %lc\n", L'é');
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%C L'é': %C\n", L'é');
	  return_values[j++] =    asprintf(&str2, "   printf %%C L'é': %C\n", L'é');
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %lC\n", L'é');
//	  return_values[j++] =    asprintf(&str2, "   printf: %lC\n", L'é');
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s\n", L"résumé s");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s\n", L"résumé s");
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%ls: %ls\n", L"résumé ls");
	  return_values[j++] =    asprintf(&str2, "   printf %%ls: %ls\n", L"résumé ls");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%S: %S\n", L"résumé S");
	  return_values[j++] =    asprintf(&str2, "   printf %%S: %S\n", L"résumé S");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf %%lls: %lls\n", L"résumé lls");
//	  return_values[j++] =    asprintf(&str2, "   printf %%lls: %lls\n", L"résumé lls");
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %lS\n", L"résumé lS");
//	  return_values[j++] =    asprintf(&str2, "   printf: %lS\n", L"résumé lS");
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %jS\n", L"résumé jS");
//	  return_values[j++] =    asprintf(&str2, "   printf: %jS\n", L"résumé jS");
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %hhS\n", L"résumé hhS");
//	  return_values[j++] =    asprintf(&str2, "   printf: %hhS\n", L"résumé hhS");
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %hhs\n", L"résumé hhs");
//	  return_values[j++] =    asprintf(&str2, "   printf: %hhs\n", L"résumé hhs");
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %hhs\n", "rasuma hhs");
//	  return_values[j++] =    asprintf(&str2, "   printf: %hhs\n", "rasuma hhs");
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

/*
** Len flags
*/

	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %hhd\n", "%hhd", vint.sc);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %hhd\n", "%hhd", vint.sc);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %hd\n", "%hd", vint.ss);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %hd\n", "%hd", vint.ss);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %ld\n", "%ld", vint.sl);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %ld\n", "%ld", vint.sl);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %lld\n", "%lld", (long long) vint.sl);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %lld\n", "%lld", (long long) vint.sl);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %hhu\n", "%hhu", vint.uc);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %hhu\n", "%hhu", vint.uc);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %hu\n", "%hu", vint.us);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %hu\n", "%hu", vint.us);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %lu\n", "%lu", vint.ul);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %lu\n", "%lu", vint.ul);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %llu\n", "%llu", (long long) vint.ul);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %llu\n", "%llu", (long long) vint.ul);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


/*
** %s basics
*/

	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.5s\n", "%.5s", "ft_printf");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.5s\n", "%.5s", "   printf");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %12s\n", "%12s", "ft_printf");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %12s\n", "%12s", "   printf");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %13.6s\n", "%13.6s", "ft_printf");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %13.6s\n", "%13.6s", "   printf");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-13.6s\n", "%-13.6s", "ft_printf");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-13.6s\n", "%-13.6s", "   printf");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#13.6s\n", "%#13.6s", "ft_printf");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#13.6s\n", "%#13.6s", "   printf");
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %013.6s\n", "%013.6s", "ft_printf");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %013.6s\n", "%013.6s", "   printf");
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives % 13.6s\n", "% 13.6s", "ft_printf");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives % 13.6s\n", "% 13.6s", "   printf");
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


printf("\n\n");
printf("\n\n");


	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.5ls\n", "%.5ls", L"éft_printf");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.5ls\n", "%.5ls", L"é   printf");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %12ls\n", "%12ls", L"éft_printf");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %12ls\n", "%12ls", L"é   printf");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %13.6ls\n", "%13.6ls", L"éft_printf");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %13.6ls\n", "%13.6ls", L"é   printf");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-13.6ls\n", "%-13.6ls", L"éft_printf");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-13.6ls\n", "%-13.6ls", L"é   printf");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#13.6ls\n", "%#13.6ls", L"éft_printf");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#13.6ls\n", "%#13.6ls", L"é   printf");
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+13.6ls\n", "%+13.6ls", L"éft_printf");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+13.6ls\n", "%+13.6ls", L"é   printf");
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %013.6ls\n", "%013.6ls", L"éft_printf");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %013.6ls\n", "%013.6ls", L"é   printf");
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

printf("\n\n");
printf("\n\n");


//les é comptent pour pile 2 bytes. Remarquez que le .5 ne fait afficher que 2 é sur 3 par la suite
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.5ls\n", "%.5ls", L"éééft_printf");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.5ls\n", "%.5ls", L"ééé   printf");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.6ls\n", "%.6ls", L"éééft_printf");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.6ls\n", "%.6ls", L"ééé   printf");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.6ls\n", "%.6ls", L"ééôft_printf");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.6ls\n", "%.6ls", L"ééô   printf");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %12ls\n", "%12ls", L"éééft_printf");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %12ls\n", "%12ls", L"ééé   printf");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %13.6ls\n", "%13.6ls", L"éééft_printf");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %13.6ls\n", "%13.6ls", L"ééé   printf");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-13.6ls\n", "%-13.6ls", L"éééft_printf");
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-13.6ls\n", "%-13.6ls", L"ééé   printf");
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#13.6ls\n", "%#13.6ls", L"éééft_printf");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#13.6ls\n", "%#13.6ls", L"ééé   printf");
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0-13.6ls\n", "%0-13.6ls", L"éééft_printf");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0-13.6ls\n", "%0-13.6ls", L"ééé   printf");
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %013.6ls\n", "%013.6ls", L"éééft_printf");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %013.6ls\n", "%013.6ls", L"ééé   printf");
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


printf("\n\n");
printf("\n\n");

	unsigned int		part_ad = (unsigned int)(long unsigned int)&i;
	long unsigned int	whole_ad = (long unsigned int)&i;

	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %p\n", "%p", &i);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %p\n", "%p", &i);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %15p\n", "%15p", &i);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %15p\n", "%15p", &i);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %013p\n", "%013p", &i);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %013p\n", "%013p", &i);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %13.5p\n", "%13.5p", &i);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %13.5p\n", "%13.5p", &i);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %x\n", "%x", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %x\n", "%x", part_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %X\n", "%X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %X\n", "%X", part_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %lx\n", "%lx", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %lx\n", "%lx", whole_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %lX\n", "%lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %lX\n", "%lX", whole_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);



	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#x\n", "%#x", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#x\n", "%#x", part_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#X\n", "%#X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#X\n", "%#X", part_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#lx\n", "%#lx", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#lx\n", "%#lx", whole_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#lX\n", "%#lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#lX\n", "%#lX", whole_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);



	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15x\n", "%.15x", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15x\n", "%.15x", part_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15X\n", "%.15X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15X\n", "%.15X", part_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15lx\n", "%.15lx", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15lx\n", "%.15lx", whole_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15lX\n", "%.15lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15lX\n", "%.15lX", whole_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);



	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.15x\n", "%#.15x", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.15x\n", "%#.15x", part_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.15X\n", "%#.15X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.15X\n", "%#.15X", part_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.15lx\n", "%#.15lx", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.15lx\n", "%#.15lx", whole_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.15lX\n", "%#.15lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.15lX\n", "%#.15lX", whole_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);



	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15x\n", "%20.15x", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15x\n", "%20.15x", part_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15X\n", "%20.15X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15X\n", "%20.15X", part_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15lx\n", "%20.15lx", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15lx\n", "%20.15lx", whole_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15lX\n", "%20.15lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15lX\n", "%20.15lX", whole_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);



	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#20.15x\n", "%#20.15x", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#20.15x\n", "%#20.15x", part_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#20.15X\n", "%#20.15X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#20.15X\n", "%#20.15X", part_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#20.15lx\n", "%#20.15lx", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#20.15lx\n", "%#20.15lx", whole_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#20.15lX\n", "%#20.15lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#20.15lX\n", "%#20.15lX", whole_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);



	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20x\n", "%20x", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20x\n", "%20x", part_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20X\n", "%20X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20X\n", "%20X", part_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20lx\n", "%20lx", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20lx\n", "%20lx", whole_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20lX\n", "%20lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20lX\n", "%20lX", whole_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);



	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#20x\n", "%#20x", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#20x\n", "%#20x", part_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#20X\n", "%#20X", part_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#20X\n", "%#20X", part_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#20lx\n", "%#20lx", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#20lx\n", "%#20lx", whole_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#20lX\n", "%#20lX", whole_ad);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#20lX\n", "%#20lX", whole_ad);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


printf("\n\n");
printf("\n\n");


//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0.2d\n", "%0.2d", VAL_1);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0.2d\n", "%0.2d", VAL_1);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %2d\n", "%2d", VAL_2);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %2d\n", "%2d", VAL_2);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.3d\n", "%.3d", VAL_2);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.3d\n", "%.3d", VAL_2);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %2.3d\n", "%2.3d", VAL_2);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %2.3d\n", "%2.3d", VAL_2);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %4.3d\n", "%4.3d", VAL_2);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %4.3d\n", "%4.3d", VAL_2);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %5d\n", "%5d", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %5d\n", "%5d", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.2d\n", "%.2d", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.2d\n", "%.2d", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %5.2d\n", "%5.2d", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %5.2d\n", "%5.2d", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.5d\n", "%.5d", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.5d\n", "%.5d", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %2.5d\n", "%2.5d", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %2.5d\n", "%2.5d", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %4.5d\n", "%4.5d", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %4.5d\n", "%4.5d", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %06d\n", "%06d", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %06d\n", "%06d", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-6d\n", "%-6d", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-6d\n", "%-6d", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+6d\n", "%+6d", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+6d\n", "%+6d", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+-6d\n", "%+-6d", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+-6d\n", "%+-6d", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0+6d\n", "%0+6d", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0+6d\n", "%0+6d", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0+d\n", "%0+d", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0+d\n", "%0+d", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+d\n", "%+d", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+d\n", "%+d", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.2d\n", "%-.2d", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.2d\n", "%-.2d", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+.2d\n", "%+.2d", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+.2d\n", "%+.2d", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+-.2d\n", "%+-.2d", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+-.2d\n", "%+-.2d", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


printf("\n\n");
printf("\n\n");


//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+o\n", "%+o", VAL_1);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+o\n", "%+o", VAL_1);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %5o\n", "%5o", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %5o\n", "%5o", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.5o\n", "%.5o", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.5o\n", "%.5o", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.2o\n", "%.2o", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.2o\n", "%.2o", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.2o\n", "%#.2o", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.2o\n", "%#.2o", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %2.5o\n", "%2.5o", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %2.5o\n", "%2.5o", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %4.5o\n", "%4.5o", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %4.5o\n", "%4.5o", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#4o\n", "%#4o", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#4o\n", "%#4o", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.5o\n", "%#.5o", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.5o\n", "%#.5o", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#4.5o\n", "%#4.5o", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#4.5o\n", "%#4.5o", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#5o\n", "%#5o", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#5o\n", "%#5o", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#06o\n", "%#06o", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#06o\n", "%#06o", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#o\n", "%#o", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#o\n", "%#o", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#6o\n", "%#6o", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#6o\n", "%#6o", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#-6o\n", "%#-6o", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#-6o\n", "%#-6o", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#06o\n", "%#06o", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#06o\n", "%#06o", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#0o\n", "%#.2o", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#0o\n", "%#.2o", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


printf("\n\n");
printf("\n\n");


//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+x\n", "%+x", VAL_1);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+x\n", "%+x", VAL_1);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#0-x\n", "%#0-x", VAL_1);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#0-x\n", "%#0-x", VAL_1);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#0-6x\n", "%#0-6x", VAL_1);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#0-6x\n", "%#0-6x", VAL_1);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %5x\n", "%5x", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %5x\n", "%5x", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.5x\n", "%.5x", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.5x\n", "%.5x", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.2x\n", "%.2x", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.2x\n", "%.2x", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.2x\n", "%#.2x", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.2x\n", "%#.2x", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %2.5x\n", "%2.5x", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %2.5x\n", "%2.5x", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %4.5x\n", "%4.5x", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %4.5x\n", "%4.5x", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#4.5x\n", "%#4.5x", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#4.5x\n", "%#4.5x", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#5x\n", "%#5x", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#5x\n", "%#5x", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#06x\n", "%#06x", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#06x\n", "%#06x", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#6x\n", "%#6x", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#6x\n", "%#6x", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#0x\n", "%#0x", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#0x\n", "%#0x", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#x\n", "%#x", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#x\n", "%#x", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


printf("\n\n");
printf("\n\n");


//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+X\n", "%+X", VAL_1);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+X\n", "%+X", VAL_1);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#0-X\n", "%#0-X", VAL_1);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#0-X\n", "%#0-X", VAL_1);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#-06X\n", "%#-06X", VAL_1);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#-06X\n", "%#-06X", VAL_1);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#0-6X\n", "%#0-6X", VAL_1);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#0-6X\n", "%#0-6X", VAL_1);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %5X\n", "%5X", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %5X\n", "%5X", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.5X\n", "%.5X", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.5X\n", "%.5X", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.2X\n", "%.2X", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.2X\n", "%.2X", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#.2X\n", "%#.2X", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#.2X\n", "%#.2X", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %2.5X\n", "%2.5X", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %2.5X\n", "%2.5X", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %4.5X\n", "%4.5X", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %4.5X\n", "%4.5X", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#4.5X\n", "%#4.5X", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#4.5X\n", "%#4.5X", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#5X\n", "%#5X", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#5X\n", "%#5X", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#06X\n", "%#06X", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#06X\n", "%#06X", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);



	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#6X\n", "%#6X", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#6X\n", "%#6X", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#0X\n", "%#0X", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#0X\n", "%#0X", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#X\n", "%#X", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#X\n", "%#X", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);


printf("\n\n");
printf("\n\n");


//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#u\n", "%#u", VAL_1);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#u\n", "%#u", VAL_1);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+u\n", "%+u", VAL_1);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+u\n", "%+u", VAL_1);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0-u\n", "%0-u", VAL_1);
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0-u\n", "%0-u", VAL_1);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
//	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
//	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0.2u\n", "%0.2u", VAL_1);
//	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0.2u\n", "%0.2u", VAL_1);
//	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %5u\n", "%5u", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %5u\n", "%5u", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.5u\n", "%.5u", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.5u\n", "%.5u", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.2u\n", "%.2u", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.2u\n", "%.2u", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.2u\n", "%-.2u", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.2u\n", "%-.2u", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %2.5u\n", "%2.5u", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %2.5u\n", "%2.5u", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %4.5u\n", "%4.5u", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %4.5u\n", "%4.5u", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %4.5u\n", "%4.5u", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %4.5u\n", "%4.5u", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %5u\n", "%5u", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %5u\n", "%5u", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %6u\n", "%6u", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %6u\n", "%6u", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0u\n", "%0u", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0u\n", "%0u", VAL_1);
	check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %06u\n", "%06u", VAL_1);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %06u\n", "%06u", VAL_1);
	//last test gets back the static failure number
	int str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);




printf("\n\n");
printf(C_BLUE"\nTests on return values :"RESET);
printf("\n\n");


	int return_fails = 0;

	i = 0;
	while (i < j)
	{
		if (return_values[i] == return_values[i + 1])
			printf(C_GREEN"Test %3d: ft_printf %d ;    printf %d\n"RESET, i / 2, return_values[i], return_values[i + 1]);
		else
		{
			printf(C_RED"Test %3d: ft_printf %d ;    printf %d\n"RESET, i / 2, return_values[i], return_values[i + 1]);
			++return_fails;
		}
		i += 2;
	}
	if (str_fails == 0 && return_fails == 0)
	{
		printf(C_GREEN"\nThere are 0 failed tests based on both return values and str output values. Congratulations !"RESET);
		printf(C_MAGENTA"\n Have you checked for leaks yet ? ;) You do know about valgrind or the C flag -fsanitize=address and its accompanying libasan.a right ?\n"RESET);
	}
	else if (return_fails == 0)
	{
		printf(C_GREEN"\nThere are 0 failed tests based on return values."RESET);
		printf(C_YELLOW"\nTests on return values are mandatory but not sufficient."RESET); 
		printf(C_RED"\nThere are %d failed tests based on str_output values.\n"RESET, str_fails);
	}
	else if (str_fails == 0)
	{
		printf(C_RED"\nThere are %d failed tests based on return values."RESET, return_fails);
		printf(C_GREEN"\nThere are 0 failed tests based on str output values."RESET);
		printf(C_YELLOW"\nTests on str output values are mandatory but not sufficient.\n"RESET);
	}
	else
	{
		printf(C_RED"\nThere are %d failed tests based on return values.\n"RESET, return_fails);
		printf(C_RED"\nThere are %d failed tests based on str_output values.\n"RESET, str_fails);
	}
	printf("\n");
	return (0);
}
