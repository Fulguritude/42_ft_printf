#include "../ft_printf.h"
#include <stdio.h>


#define C_RED     "\x1b[31m"
#define C_GREEN   "\x1b[32m"
#define C_YELLOW  "\x1b[33m"
#define C_BLUE    "\x1b[34m"
#define C_MAGENTA "\x1b[35m"
#define C_CYAN    "\x1b[36m"
#define RESET     "\x1b[0m"


/*
** ---------------------------------------------------------------------------
**
**   IMPORTANT NOTES :
**
**   -	"#if 0" and "#endif" pragmas are used only to comment out text below for
**		readability in the stdout of the unit tests. Don't use multiline
**		comments as they tend to mess things up.
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
**	 -	Calling a va_arg() on a non-existing argument always causes a segfault.
**
**		Check debug versions of the code on 
**			https://github.com/Fulguritude/42_ft_printf
**		for ideas.
**
** ---------------------------------------------------------------------------
*/


static void	check_retvals(int j, int *return_values)
{
	(return_values[j - 1] == return_values[j - 2]) ?
		printf(C_GREEN"\nReturn values EQUAL"RESET) :
		printf(C_RED"\nReturn values UNEQUAL."RESET);
	printf("\n");
}

int main()
{
	int i = -1;
	int j = 0;
	int return_values[400];

	setlocale(LC_ALL, "");

	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf\n");
	  return_values[j++] =    printf("   printf\n");
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf %%\n");
	  return_values[j++] =    printf("   printf %%\n");
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf %d\n", 10);
	  return_values[j++] =    printf("   printf %d\n", 10);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("   %sf\n", "print");
	  return_values[j++] =    printf("ft_%sf\n", "print");
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf %#x\n", 123);
	  return_values[j++] =    printf("   printf %#x\n", 123);
	check_retvals(j, return_values);

//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf %#-+05.5d and %#-+06.5d\n", 123456, 123);
//	  return_values[j++] =    printf("   printf %#-+05.5d and %#-+06.5d\n", 123456, 123);
//	check_retvals(j, return_values);

	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf %+8.5d and %+8.5d\n", 123456, 123);
	  return_values[j++] =    printf("   printf %+8.5d and %+8.5d\n", 123456, 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf %-+8.5d and %-+8.5d\n", 123456, 123);
	  return_values[j++] =    printf("   printf %-+8.5d and %-+8.5d\n", 123456, 123);
	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf %0+8.5d and %0+8.5d\n", 123456, 123);
//	  return_values[j++] =    printf("   printf %0+8.5d and %0+8.5d\n", 123456, 123);
//	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf %-+5.5d and %-+5.5d\n", 123456, 123);
	  return_values[j++] =    printf("   printf %-+5.5d and %-+5.5d\n", 123456, 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf %-+4.5d and %-+4.5d\n", 123456, 123);
	  return_values[j++] =    printf("   printf %-+4.5d and %-+4.5d\n", 123456, 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf %-+3.5d and %-+3.5d\n", 123456, 123);
	  return_values[j++] =    printf("   printf %-+3.5d and %-+3.5d\n", 123456, 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf %-+5.5d and %-+3.6d\n", 123456, 123);
	  return_values[j++] =    printf("   printf %-+5.5d and %-+3.6d\n", 123456, 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %d in octal : %o\n", 123, 123);
	  return_values[j++] =    printf("   printf: %d in octal : %o\n", 123, 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %d in octal : %#o\n", 123, 123);
	  return_values[j++] =    printf("   printf: %d in octal : %#o\n", 123, 123);
	check_retvals(j, return_values);

printf("\n\n\n");
	
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf %%c L'é': %c\n", L'é');
	  return_values[j++] =    printf("   printf %%c L'é': %c\n", L'é');
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf %%lc L'é': %lc\n", L'é');
	  return_values[j++] =    printf("   printf %%lc L'é': %lc\n", L'é');
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf %%C L'é': %C\n", L'é');
	  return_values[j++] =    printf("   printf %%C L'é': %C\n", L'é');
	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %lC\n", L'é');
//	  return_values[j++] =    printf("   printf: %lC\n", L'é');
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s\n", L"résumé s");
//	  return_values[j++] =    printf("   printf: %s\n", L"résumé s");
//	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf %%ls: %ls\n", L"résumé ls");
	  return_values[j++] =    printf("   printf %%ls: %ls\n", L"résumé ls");
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf %%S: %S\n", L"résumé S");
	  return_values[j++] =    printf("   printf %%S: %S\n", L"résumé S");
	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf %%lls: %lls\n", L"résumé lls");
//	  return_values[j++] =    printf("   printf %%lls: %lls\n", L"résumé lls");
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %lS\n", L"résumé lS");
//	  return_values[j++] =    printf("   printf: %lS\n", L"résumé lS");
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %jS\n", L"résumé jS");
//	  return_values[j++] =    printf("   printf: %jS\n", L"résumé jS");
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %hhS\n", L"résumé hhS");
//	  return_values[j++] =    printf("   printf: %hhS\n", L"résumé hhS");
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %hhs\n", L"résumé hhs");
//	  return_values[j++] =    printf("   printf: %hhs\n", L"résumé hhs");
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %hhs\n", "rasuma hhs");
//	  return_values[j++] =    printf("   printf: %hhs\n", "rasuma hhs");
//	check_retvals(j, return_values);


	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.5s\n", "%.5s", "ft_printf");
	  return_values[j++] =    printf("   printf: %s gives %.5s\n", "%.5s", "   printf");
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %12s\n", "%12s", "ft_printf");
	  return_values[j++] =    printf("   printf: %s gives %12s\n", "%12s", "   printf");
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %13.6s\n", "%13.6s", "ft_printf");
	  return_values[j++] =    printf("   printf: %s gives %13.6s\n", "%13.6s", "   printf");
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %-13.6s\n", "%-13.6s", "ft_printf");
	  return_values[j++] =    printf("   printf: %s gives %-13.6s\n", "%-13.6s", "   printf");
	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %#13.6s\n", "%#13.6s", "ft_printf");
//	  return_values[j++] =    printf("   printf: %s gives %#13.6s\n", "%#13.6s", "   printf");
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %013.6s\n", "%013.6s", "ft_printf");
//	  return_values[j++] =    printf("   printf: %s gives %013.6s\n", "%013.6s", "   printf");
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives % 13.6s\n", "% 13.6s", "ft_printf");
//	  return_values[j++] =    printf("   printf: %s gives % 13.6s\n", "% 13.6s", "   printf");
//	check_retvals(j, return_values);


printf("\n\n");
printf("\n\n");


	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.5ls\n", "%.5ls", L"éft_printf");
	  return_values[j++] =    printf("   printf: %s gives %.5ls\n", "%.5ls", L"é   printf");
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %12ls\n", "%12ls", L"éft_printf");
	  return_values[j++] =    printf("   printf: %s gives %12ls\n", "%12ls", L"é   printf");
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %13.6ls\n", "%13.6ls", L"éft_printf");
	  return_values[j++] =    printf("   printf: %s gives %13.6ls\n", "%13.6ls", L"é   printf");
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %-13.6ls\n", "%-13.6ls", L"éft_printf");
	  return_values[j++] =    printf("   printf: %s gives %-13.6ls\n", "%-13.6ls", L"é   printf");
	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %#13.6ls\n", "%#13.6ls", L"éft_printf");
//	  return_values[j++] =    printf("   printf: %s gives %#13.6ls\n", "%#13.6ls", L"é   printf");
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %+13.6ls\n", "%+13.6ls", L"éft_printf");
//	  return_values[j++] =    printf("   printf: %s gives %+13.6ls\n", "%+13.6ls", L"é   printf");
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %013.6ls\n", "%013.6ls", L"éft_printf");
//	  return_values[j++] =    printf("   printf: %s gives %013.6ls\n", "%013.6ls", L"é   printf");
//	check_retvals(j, return_values);

printf("\n\n");
printf("\n\n");


//les é comptent pour pile 2 bytes. Remarquez que le .5 ne fait afficher que 2 é sur 3 par la suite
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.5ls\n", "%.5ls", L"éééft_printf");
	  return_values[j++] =    printf("   printf: %s gives %.5ls\n", "%.5ls", L"ééé   printf");
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.6ls\n", "%.6ls", L"éééft_printf");
	  return_values[j++] =    printf("   printf: %s gives %.6ls\n", "%.6ls", L"ééé   printf");
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.6ls\n", "%.6ls", L"ééôft_printf");
	  return_values[j++] =    printf("   printf: %s gives %.6ls\n", "%.6ls", L"ééô   printf");
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %12ls\n", "%12ls", L"éééft_printf");
	  return_values[j++] =    printf("   printf: %s gives %12ls\n", "%12ls", L"ééé   printf");
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %13.6ls\n", "%13.6ls", L"éééft_printf");
	  return_values[j++] =    printf("   printf: %s gives %13.6ls\n", "%13.6ls", L"ééé   printf");
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %-13.6ls\n", "%-13.6ls", L"éééft_printf");
	  return_values[j++] =    printf("   printf: %s gives %-13.6ls\n", "%-13.6ls", L"ééé   printf");
	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %#13.6ls\n", "%#13.6ls", L"éééft_printf");
//	  return_values[j++] =    printf("   printf: %s gives %#13.6ls\n", "%#13.6ls", L"ééé   printf");
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %0-13.6ls\n", "%0-13.6ls", L"éééft_printf");
//	  return_values[j++] =    printf("   printf: %s gives %0-13.6ls\n", "%0-13.6ls", L"ééé   printf");
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %013.6ls\n", "%013.6ls", L"éééft_printf");
//	  return_values[j++] =    printf("   printf: %s gives %013.6ls\n", "%013.6ls", L"ééé   printf");
//	check_retvals(j, return_values);


printf("\n\n");
printf("\n\n");

	unsigned int		part_ad = (unsigned int)(long unsigned int)&i;
	long unsigned int	whole_ad = (long unsigned int)&i;

	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %p\n", "%p", &i);
	  return_values[j++] =    printf("   printf: %s gives %p\n", "%p", &i);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %15p\n", "%15p", &i);
	  return_values[j++] =    printf("   printf: %s gives %15p\n", "%15p", &i);
	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %013p\n", "%013p", &i);
//	  return_values[j++] =    printf("   printf: %s gives %013p\n", "%013p", &i);
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %13.5p\n", "%13.5p", &i);
//	  return_values[j++] =    printf("   printf: %s gives %13.5p\n", "%13.5p", &i);
//	check_retvals(j, return_values);


	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %x\n", "%x", part_ad);
	  return_values[j++] =    printf("   printf: %s gives %x\n", "%x", part_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %X\n", "%X", part_ad);
	  return_values[j++] =    printf("   printf: %s gives %X\n", "%X", part_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %lx\n", "%lx", whole_ad);
	  return_values[j++] =    printf("   printf: %s gives %lx\n", "%lx", whole_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %lX\n", "%lX", whole_ad);
	  return_values[j++] =    printf("   printf: %s gives %lX\n", "%lX", whole_ad);
	check_retvals(j, return_values);



	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#x\n", "%#x", part_ad);
	  return_values[j++] =    printf("   printf: %s gives %#x\n", "%#x", part_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#X\n", "%#X", part_ad);
	  return_values[j++] =    printf("   printf: %s gives %#X\n", "%#X", part_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#lx\n", "%#lx", whole_ad);
	  return_values[j++] =    printf("   printf: %s gives %#lx\n", "%#lx", whole_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#lX\n", "%#lX", whole_ad);
	  return_values[j++] =    printf("   printf: %s gives %#lX\n", "%#lX", whole_ad);
	check_retvals(j, return_values);



	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.15x\n", "%.15x", part_ad);
	  return_values[j++] =    printf("   printf: %s gives %.15x\n", "%.15x", part_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.15X\n", "%.15X", part_ad);
	  return_values[j++] =    printf("   printf: %s gives %.15X\n", "%.15X", part_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.15lx\n", "%.15lx", whole_ad);
	  return_values[j++] =    printf("   printf: %s gives %.15lx\n", "%.15lx", whole_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.15lX\n", "%.15lX", whole_ad);
	  return_values[j++] =    printf("   printf: %s gives %.15lX\n", "%.15lX", whole_ad);
	check_retvals(j, return_values);



	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#.15x\n", "%#.15x", part_ad);
	  return_values[j++] =    printf("   printf: %s gives %#.15x\n", "%#.15x", part_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#.15X\n", "%#.15X", part_ad);
	  return_values[j++] =    printf("   printf: %s gives %#.15X\n", "%#.15X", part_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#.15lx\n", "%#.15lx", whole_ad);
	  return_values[j++] =    printf("   printf: %s gives %#.15lx\n", "%#.15lx", whole_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#.15lX\n", "%#.15lX", whole_ad);
	  return_values[j++] =    printf("   printf: %s gives %#.15lX\n", "%#.15lX", whole_ad);
	check_retvals(j, return_values);



	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %20.15x\n", "%20.15x", part_ad);
	  return_values[j++] =    printf("   printf: %s gives %20.15x\n", "%20.15x", part_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %20.15X\n", "%20.15X", part_ad);
	  return_values[j++] =    printf("   printf: %s gives %20.15X\n", "%20.15X", part_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %20.15lx\n", "%20.15lx", whole_ad);
	  return_values[j++] =    printf("   printf: %s gives %20.15lx\n", "%20.15lx", whole_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %20.15lX\n", "%20.15lX", whole_ad);
	  return_values[j++] =    printf("   printf: %s gives %20.15lX\n", "%20.15lX", whole_ad);
	check_retvals(j, return_values);



	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#20.15x\n", "%#20.15x", part_ad);
	  return_values[j++] =    printf("   printf: %s gives %#20.15x\n", "%#20.15x", part_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#20.15X\n", "%#20.15X", part_ad);
	  return_values[j++] =    printf("   printf: %s gives %#20.15X\n", "%#20.15X", part_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#20.15lx\n", "%#20.15lx", whole_ad);
	  return_values[j++] =    printf("   printf: %s gives %#20.15lx\n", "%#20.15lx", whole_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#20.15lX\n", "%#20.15lX", whole_ad);
	  return_values[j++] =    printf("   printf: %s gives %#20.15lX\n", "%#20.15lX", whole_ad);
	check_retvals(j, return_values);



	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %20x\n", "%20x", part_ad);
	  return_values[j++] =    printf("   printf: %s gives %20x\n", "%20x", part_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %20X\n", "%20X", part_ad);
	  return_values[j++] =    printf("   printf: %s gives %20X\n", "%20X", part_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %20lx\n", "%20lx", whole_ad);
	  return_values[j++] =    printf("   printf: %s gives %20lx\n", "%20lx", whole_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %20lX\n", "%20lX", whole_ad);
	  return_values[j++] =    printf("   printf: %s gives %20lX\n", "%20lX", whole_ad);
	check_retvals(j, return_values);



	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#20x\n", "%#20x", part_ad);
	  return_values[j++] =    printf("   printf: %s gives %#20x\n", "%#20x", part_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#20X\n", "%#20X", part_ad);
	  return_values[j++] =    printf("   printf: %s gives %#20X\n", "%#20X", part_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#20lx\n", "%#20lx", whole_ad);
	  return_values[j++] =    printf("   printf: %s gives %#20lx\n", "%#20lx", whole_ad);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#20lX\n", "%#20lX", whole_ad);
	  return_values[j++] =    printf("   printf: %s gives %#20lX\n", "%#20lX", whole_ad);
	check_retvals(j, return_values);


printf("\n\n");
printf("\n\n");


//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %0.2d\n", "%0.2d", 123);
//	  return_values[j++] =    printf("   printf: %s gives %0.2d\n", "%0.2d", 123);
//	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %2d\n", "%2d", 123456789);
	  return_values[j++] =    printf("   printf: %s gives %2d\n", "%2d", 123456789);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.3d\n", "%.3d", 123456789);
	  return_values[j++] =    printf("   printf: %s gives %.3d\n", "%.3d", 123456789);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %2.3d\n", "%2.3d", 123456789);
	  return_values[j++] =    printf("   printf: %s gives %2.3d\n", "%2.3d", 123456789);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %4.3d\n", "%4.3d", 123456789);
	  return_values[j++] =    printf("   printf: %s gives %4.3d\n", "%4.3d", 123456789);
	check_retvals(j, return_values);


	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %5d\n", "%5d", 123);
	  return_values[j++] =    printf("   printf: %s gives %5d\n", "%5d", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.2d\n", "%.2d", 123);
	  return_values[j++] =    printf("   printf: %s gives %.2d\n", "%.2d", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %5.2d\n", "%5.2d", 123);
	  return_values[j++] =    printf("   printf: %s gives %5.2d\n", "%5.2d", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.5d\n", "%.5d", 123);
	  return_values[j++] =    printf("   printf: %s gives %.5d\n", "%.5d", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %2.5d\n", "%2.5d", 123);
	  return_values[j++] =    printf("   printf: %s gives %2.5d\n", "%2.5d", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %4.5d\n", "%4.5d", 123);
	  return_values[j++] =    printf("   printf: %s gives %4.5d\n", "%4.5d", 123);
	check_retvals(j, return_values);


	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %06d\n", "%06d", 123);
	  return_values[j++] =    printf("   printf: %s gives %06d\n", "%06d", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %-6d\n", "%-6d", 123);
	  return_values[j++] =    printf("   printf: %s gives %-6d\n", "%-6d", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %+6d\n", "%+6d", 123);
	  return_values[j++] =    printf("   printf: %s gives %+6d\n", "%+6d", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %+-6d\n", "%+-6d", 123);
	  return_values[j++] =    printf("   printf: %s gives %+-6d\n", "%+-6d", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %0+6d\n", "%0+6d", 123);
	  return_values[j++] =    printf("   printf: %s gives %0+6d\n", "%0+6d", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %0+d\n", "%0+d", 123);
	  return_values[j++] =    printf("   printf: %s gives %0+d\n", "%0+d", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %+d\n", "%+d", 123);
	  return_values[j++] =    printf("   printf: %s gives %+d\n", "%+d", 123);
	check_retvals(j, return_values);


	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %-.2d\n", "%-.2d", 123);
	  return_values[j++] =    printf("   printf: %s gives %-.2d\n", "%-.2d", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %+.2d\n", "%+.2d", 123);
	  return_values[j++] =    printf("   printf: %s gives %+.2d\n", "%+.2d", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %+-.2d\n", "%+-.2d", 123);
	  return_values[j++] =    printf("   printf: %s gives %+-.2d\n", "%+-.2d", 123);
	check_retvals(j, return_values);


printf("\n\n");
printf("\n\n");


//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %+o\n", "%+o", 123);
//	  return_values[j++] =    printf("   printf: %s gives %+o\n", "%+o", 123);
//	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %5o\n", "%5o", 123);
	  return_values[j++] =    printf("   printf: %s gives %5o\n", "%5o", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.5o\n", "%.5o", 123);
	  return_values[j++] =    printf("   printf: %s gives %.5o\n", "%.5o", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.2o\n", "%.2o", 123);
	  return_values[j++] =    printf("   printf: %s gives %.2o\n", "%.2o", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#.2o\n", "%#.2o", 123);
	  return_values[j++] =    printf("   printf: %s gives %#.2o\n", "%#.2o", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %2.5o\n", "%2.5o", 123);
	  return_values[j++] =    printf("   printf: %s gives %2.5o\n", "%2.5o", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %4.5o\n", "%4.5o", 123);
	  return_values[j++] =    printf("   printf: %s gives %4.5o\n", "%4.5o", 123);
	check_retvals(j, return_values);


	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#4o\n", "%#4o", 123);
	  return_values[j++] =    printf("   printf: %s gives %#4o\n", "%#4o", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#.5o\n", "%#.5o", 123);
	  return_values[j++] =    printf("   printf: %s gives %#.5o\n", "%#.5o", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#4.5o\n", "%#4.5o", 123);
	  return_values[j++] =    printf("   printf: %s gives %#4.5o\n", "%#4.5o", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#5o\n", "%#5o", 123);
	  return_values[j++] =    printf("   printf: %s gives %#5o\n", "%#5o", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#06o\n", "%#06o", 123);
	  return_values[j++] =    printf("   printf: %s gives %#06o\n", "%#06o", 123);
	check_retvals(j, return_values);


	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#o\n", "%#o", 123);
	  return_values[j++] =    printf("   printf: %s gives %#o\n", "%#o", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#6o\n", "%#6o", 123);
	  return_values[j++] =    printf("   printf: %s gives %#6o\n", "%#6o", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#-6o\n", "%#-6o", 123);
	  return_values[j++] =    printf("   printf: %s gives %#-6o\n", "%#-6o", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#06o\n", "%#06o", 123);
	  return_values[j++] =    printf("   printf: %s gives %#06o\n", "%#06o", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#0o\n", "%#.2o", 123);
	  return_values[j++] =    printf("   printf: %s gives %#0o\n", "%#.2o", 123);
	check_retvals(j, return_values);


printf("\n\n");
printf("\n\n");


//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %+x\n", "%+x", 123);
//	  return_values[j++] =    printf("   printf: %s gives %+x\n", "%+x", 123);
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %#0-x\n", "%#0-x", 123);
//	  return_values[j++] =    printf("   printf: %s gives %#0-x\n", "%#0-x", 123);
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %#0-6x\n", "%#0-6x", 123);
//	  return_values[j++] =    printf("   printf: %s gives %#0-6x\n", "%#0-6x", 123);
//	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %5x\n", "%5x", 123);
	  return_values[j++] =    printf("   printf: %s gives %5x\n", "%5x", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.5x\n", "%.5x", 123);
	  return_values[j++] =    printf("   printf: %s gives %.5x\n", "%.5x", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.2x\n", "%.2x", 123);
	  return_values[j++] =    printf("   printf: %s gives %.2x\n", "%.2x", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#.2x\n", "%#.2x", 123);
	  return_values[j++] =    printf("   printf: %s gives %#.2x\n", "%#.2x", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %2.5x\n", "%2.5x", 123);
	  return_values[j++] =    printf("   printf: %s gives %2.5x\n", "%2.5x", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %4.5x\n", "%4.5x", 123);
	  return_values[j++] =    printf("   printf: %s gives %4.5x\n", "%4.5x", 123);
	check_retvals(j, return_values);


	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#4.5x\n", "%#4.5x", 123);
	  return_values[j++] =    printf("   printf: %s gives %#4.5x\n", "%#4.5x", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#5x\n", "%#5x", 123);
	  return_values[j++] =    printf("   printf: %s gives %#5x\n", "%#5x", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#06x\n", "%#06x", 123);
	  return_values[j++] =    printf("   printf: %s gives %#06x\n", "%#06x", 123);
	check_retvals(j, return_values);


	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#6x\n", "%#6x", 123);
	  return_values[j++] =    printf("   printf: %s gives %#6x\n", "%#6x", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#0x\n", "%#0x", 123);
	  return_values[j++] =    printf("   printf: %s gives %#0x\n", "%#0x", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#x\n", "%#x", 123);
	  return_values[j++] =    printf("   printf: %s gives %#x\n", "%#x", 123);
	check_retvals(j, return_values);


printf("\n\n");
printf("\n\n");


//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %+X\n", "%+X", 123);
//	  return_values[j++] =    printf("   printf: %s gives %+X\n", "%+X", 123);
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %#0-X\n", "%#0-X", 123);
//	  return_values[j++] =    printf("   printf: %s gives %#0-X\n", "%#0-X", 123);
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %#-06X\n", "%#-06X", 123);
//	  return_values[j++] =    printf("   printf: %s gives %#-06X\n", "%#-06X", 123);
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %#0-6X\n", "%#0-6X", 123);
//	  return_values[j++] =    printf("   printf: %s gives %#0-6X\n", "%#0-6X", 123);
//	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %5X\n", "%5X", 123);
	  return_values[j++] =    printf("   printf: %s gives %5X\n", "%5X", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.5X\n", "%.5X", 123);
	  return_values[j++] =    printf("   printf: %s gives %.5X\n", "%.5X", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.2X\n", "%.2X", 123);
	  return_values[j++] =    printf("   printf: %s gives %.2X\n", "%.2X", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#.2X\n", "%#.2X", 123);
	  return_values[j++] =    printf("   printf: %s gives %#.2X\n", "%#.2X", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %2.5X\n", "%2.5X", 123);
	  return_values[j++] =    printf("   printf: %s gives %2.5X\n", "%2.5X", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %4.5X\n", "%4.5X", 123);
	  return_values[j++] =    printf("   printf: %s gives %4.5X\n", "%4.5X", 123);
	check_retvals(j, return_values);


	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#4.5X\n", "%#4.5X", 123);
	  return_values[j++] =    printf("   printf: %s gives %#4.5X\n", "%#4.5X", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#5X\n", "%#5X", 123);
	  return_values[j++] =    printf("   printf: %s gives %#5X\n", "%#5X", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#06X\n", "%#06X", 123);
	  return_values[j++] =    printf("   printf: %s gives %#06X\n", "%#06X", 123);
	check_retvals(j, return_values);



	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#6X\n", "%#6X", 123);
	  return_values[j++] =    printf("   printf: %s gives %#6X\n", "%#6X", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#0X\n", "%#0X", 123);
	  return_values[j++] =    printf("   printf: %s gives %#0X\n", "%#0X", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#X\n", "%#X", 123);
	  return_values[j++] =    printf("   printf: %s gives %#X\n", "%#X", 123);
	check_retvals(j, return_values);


printf("\n\n");
printf("\n\n");


//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %#u\n", "%#u", 123);
//	  return_values[j++] =    printf("   printf: %s gives %#u\n", "%#u", 123);
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %+u\n", "%+u", 123);
//	  return_values[j++] =    printf("   printf: %s gives %+u\n", "%+u", 123);
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] = ft_printf("ft_printf: %s gives %0-u\n", "%0-u", 123);
//	  return_values[j++] =    printf("   printf: %s gives %0-u\n", "%0-u", 123);
//	check_retvals(j, return_values);
//	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	  return_values[j++] =    printf("   printf: %s gives %0.2u\n", "%0.2u", 123);
//	  return_values[j++] = ft_printf("ft_printf: %s gives %0.2u\n", "%0.2u", 123);
//	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %5u\n", "%5u", 123);
	  return_values[j++] =    printf("   printf: %s gives %5u\n", "%5u", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.5u\n", "%.5u", 123);
	  return_values[j++] =    printf("   printf: %s gives %.5u\n", "%.5u", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.2u\n", "%.2u", 123);
	  return_values[j++] =    printf("   printf: %s gives %.2u\n", "%.2u", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %-.2u\n", "%-.2u", 123);
	  return_values[j++] =    printf("   printf: %s gives %-.2u\n", "%-.2u", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %2.5u\n", "%2.5u", 123);
	  return_values[j++] =    printf("   printf: %s gives %2.5u\n", "%2.5u", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %4.5u\n", "%4.5u", 123);
	  return_values[j++] =    printf("   printf: %s gives %4.5u\n", "%4.5u", 123);
	check_retvals(j, return_values);

	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %4.5u\n", "%4.5u", 123);
	  return_values[j++] =    printf("   printf: %s gives %4.5u\n", "%4.5u", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %5u\n", "%5u", 123);
	  return_values[j++] =    printf("   printf: %s gives %5u\n", "%5u", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %6u\n", "%6u", 123);
	  return_values[j++] =    printf("   printf: %s gives %6u\n", "%6u", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %0u\n", "%0u", 123);
	  return_values[j++] =    printf("   printf: %s gives %0u\n", "%0u", 123);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:\n"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %06u\n", "%06u", 123);
	  return_values[j++] =    printf("   printf: %s gives %06u\n", "%06u", 123);
	check_retvals(j, return_values);


	int fails = 0;

	i = 0;
	while (i < j)
	{
		if (return_values[i] == return_values[i + 1])
			printf(C_GREEN"Test %3d: ft_printf %d ;    printf %d\n"RESET, i / 2, return_values[i], return_values[i + 1]);
		else
		{
			printf(C_RED"Test %3d: ft_printf %d ;    printf %d\n"RESET, i / 2, return_values[i], return_values[i + 1]);
			++fails;
		}
		i += 2;
	}
	fails == 0 ?
		printf(C_GREEN"\nThere are 0 failed tests based on return values. Check that output values are adequate on tests where a width flag might return strings of equal lengths.\n"RESET) :	
		printf(C_RED"\nThere are %d failed tests based on return values.\n"RESET, fails);
	printf("\n");
	  return (0);
}
