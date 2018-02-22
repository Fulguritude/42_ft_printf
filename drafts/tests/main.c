#include "../ft_printf.h"
#include <stdio.h>


#define C_RED     "\x1b[31m"
#define C_GREEN   "\x1b[32m"
#define C_YELLOW  "\x1b[33m"
#define C_BLUE    "\x1b[34m"
#define C_MAGENTA "\x1b[35m"
#define C_CYAN    "\x1b[36m"
#define RESET     "\x1b[0m"

int main()
{
	int i = -1;
	int j = 0;
	int return_values[400];

	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf\n");
	return_values[j++] =    printf("   printf\n");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf %%\n");
	return_values[j++] =    printf("   printf %%\n");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf %d\n", 10);
	return_values[j++] =    printf("   printf %d\n", 10);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("   %sf\n", "print");
	return_values[j++] =    printf("ft_%sf\n", "print");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf %#x\n", 123);
	return_values[j++] =    printf("   printf %#x\n", 123);

	//printf("ft_printf %#-+05.5d and %#-+06.5d\n", 123456, 123);
	//   printf("   printf %#-+05.5d and %#-+06.5d\n", 123456, 123);

	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf %-+8.5d and %-+8.5d\n", 123456, 123);
	return_values[j++] =    printf("   printf %-+8.5d and %-+8.5d\n", 123456, 123);
//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf %0+8.5d and %0+8.5d\n", 123456, 123);
//	return_values[j++] =    printf("   printf %0+8.5d and %0+8.5d\n", 123456, 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf %-+5.5d and %-+5.5d\n", 123456, 123);
	return_values[j++] =    printf("   printf %-+5.5d and %-+5.5d\n", 123456, 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf %-+4.5d and %-+4.5d\n", 123456, 123);
	return_values[j++] =    printf("   printf %-+4.5d and %-+4.5d\n", 123456, 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf %-+3.5d and %-+3.5d\n", 123456, 123);
	return_values[j++] =    printf("   printf %-+3.5d and %-+3.5d\n", 123456, 123);

	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf %-+5.5d and %-+3.6d\n", 123456, 123);
	return_values[j++] =    printf("   printf %-+5.5d and %-+3.6d\n", 123456, 123);

	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %d in octal : %o\n", 123, 123);
	return_values[j++] =    printf("   printf: %d in octal : %o\n", 123, 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %d in octal : %#o\n", 123, 123);
	return_values[j++] =    printf("   printf: %d in octal : %#o\n", 123, 123);

	printf("\n\n\n");

	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %c\n", L'é');
	return_values[j++] =    printf("   printf: %c\n", L'é');
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %lc\n", L'é');
	return_values[j++] =    printf("   printf: %lc\n", L'é');
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %C\n", L'é');
	return_values[j++] =    printf("   printf: %C\n", L'é');
	//return_values[j++] = ft_printf("ft_printf: %lC\n", L'é');
	//return_values[j++] =    printf("   printf: %lC\n", L'é');
	//return_values[j++] = ft_printf("ft_printf: %s\n", L"résumé s");
	//return_values[j++] =    printf("   printf: %s\n", L"résumé s");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %ls\n", L"résumé ls");
	return_values[j++] =    printf("   printf: %ls\n", L"résumé ls");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %S\n", L"résumé S");
	return_values[j++] =    printf("   printf: %S\n", L"résumé S");
/*	return_values[j++] = ft_printf("ft_printf: %lS\n", L"résumé lS");
	return_values[j++] =    printf("   printf: %lS\n", L"résumé lS");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %jS\n", L"résumé jS");
	return_values[j++] =    printf("   printf: %jS\n", L"résumé jS");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %hhS\n", L"résumé hhS");
	return_values[j++] =    printf("   printf: %hhS\n", L"résumé hhS");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %hhs\n", L"résumé hhs");
	return_values[j++] =    printf("   printf: %hhs\n", L"résumé hhs");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %hhs\n", "rasuma hhs");
	return_values[j++] =    printf("   printf: %hhs\n", "rasuma hhs");
*/



	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %.5s\n", "%.5s", "printf");
	return_values[j++] =    printf("   printf: %s gives %.5s\n", "%.5s", "   printf");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %12s\n", "%12s", "printf");
	return_values[j++] =    printf("   printf: %s gives %12s\n", "%12s", "   printf");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %12.5s\n", "%12.5s", "printf");
	return_values[j++] =    printf("   printf: %s gives %12.5s\n", "%12.5s", "   printf");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %-12.5s\n", "%-12.5s", "printf");
	return_values[j++] =    printf("   printf: %s gives %-12.5s\n", "%-12.5s", "   printf");
//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives %#12.5s\n", "%#12.5s", "printf");
//	return_values[j++] =    printf("   printf: %s gives %#12.5s\n", "%#12.5s", "   printf");
//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives %012.5s\n", "%012.5s", "printf");
//	return_values[j++] =    printf("   printf: %s gives %012.5s\n", "%012.5s", "   printf");
//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives % 12.5s\n", "% 12.5s", "printf");
//	return_values[j++] =    printf("   printf: %s gives % 12.5s\n", "% 12.5s", "   printf");


printf("\n\n");
printf("\n\n");

//les é comptent pour pile 2 bytes. Remarquez que le .5 ne fait afficher que 2 é sur 3 par la suite
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %.5ls\n", "%.5ls", L"éprintf");
	return_values[j++] =    printf("   printf: %s gives %.5ls\n", "%.5ls", L"é   printf");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %12ls\n", "%12ls", L"éprintf");
	return_values[j++] =    printf("   printf: %s gives %12ls\n", "%12ls", L"é   printf");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %12.5ls\n", "%12.5ls", L"éprintf");
	return_values[j++] =    printf("   printf: %s gives %12.5ls\n", "%12.5ls", L"é   printf");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %-12.5ls\n", "%-12.5ls", L"éprintf");
	return_values[j++] =    printf("   printf: %s gives %-12.5ls\n", "%-12.5ls", L"é   printf");
//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives %#12.5ls\n", "%#12.5ls", L"éprintf");
//	return_values[j++] =    printf("   printf: %s gives %#12.5ls\n", "%#12.5ls", L"é   printf");
//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives %+12.5ls\n", "%+12.5ls", L"éprintf");
//	return_values[j++] =    printf("   printf: %s gives %+12.5ls\n", "%+12.5ls", L"é   printf");
//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives %012.5ls\n", "%012.5ls", L"éprintf");
//	return_values[j++] =    printf("   printf: %s gives %012.5ls\n", "%012.5ls", L"é   printf");


printf("\n\n");
printf("\n\n");


	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %.5ls\n", "%.5ls", L"éééprintf");
	return_values[j++] =    printf("   printf: %s gives %.5ls\n", "%.5ls", L"ééé   printf");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %12ls\n", "%12ls", L"éééprintf");
	return_values[j++] =    printf("   printf: %s gives %12ls\n", "%12ls", L"ééé   printf");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %12.5ls\n", "%12.5ls", L"éééprintf");
	return_values[j++] =    printf("   printf: %s gives %12.5ls\n", "%12.5ls", L"ééé   printf");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %-12.5ls\n", "%-12.5ls", L"éééprintf");
	return_values[j++] =    printf("   printf: %s gives %-12.5ls\n", "%-12.5ls", L"ééé   printf");
/*	return_values[j++] = ft_printf("ft_printf: %s gives %#12.5ls\n", "%#12.5ls", L"éééprintf");
	return_values[j++] =    printf("   printf: %s gives %#12.5ls\n", "%#12.5ls", L"ééé   printf");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %0-12.5ls\n", "%0-12.5ls", L"éééprintf");
	return_values[j++] =    printf("   printf: %s gives %0-12.5ls\n", "%0-12.5ls", L"ééé   printf");
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %012.5ls\n", "%012.5ls", L"éééprintf");
	return_values[j++] =    printf("   printf: %s gives %012.5ls\n", "%012.5ls", L"ééé   printf");
*/

printf("\n\n");
printf("\n\n");

	unsigned int		part_ad = (unsigned int)(long unsigned int)&i;
	long unsigned int	whole_ad = (long unsigned int)&i;

	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %p\n", "%p", &i);
	return_values[j++] =    printf("   printf: %s gives %p\n", "%p", &i);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %13p\n", "%13p", &i);
	return_values[j++] =    printf("   printf: %s gives %13p\n", "%13p", &i);
//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives %013p\n", "%013p", &i);
//	return_values[j++] =    printf("   printf: %s gives %013p\n", "%013p", &i);
//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives %13.5p\n", "%13.5p", &i);
//	return_values[j++] =    printf("   printf: %s gives %13.5p\n", "%13.5p", &i);


	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %x\n", "%x", part_ad);
	return_values[j++] =    printf("   printf: %s gives %x\n", "%x", part_ad);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %X\n", "%X", part_ad);
	return_values[j++] =    printf("   printf: %s gives %X\n", "%X", part_ad);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %lx\n", "%lx", whole_ad);
	return_values[j++] =    printf("   printf: %s gives %lx\n", "%lx", whole_ad);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %lX\n", "%lX", whole_ad);
	return_values[j++] =    printf("   printf: %s gives %lX\n", "%lX", whole_ad);


	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#x\n", "%#x", part_ad);
	return_values[j++] =    printf("   printf: %s gives %#x\n", "%#x", part_ad);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#X\n", "%#X", part_ad);
	return_values[j++] =    printf("   printf: %s gives %#X\n", "%#X", part_ad);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#lx\n", "%#lx", whole_ad);
	return_values[j++] =    printf("   printf: %s gives %#lx\n", "%#lx", whole_ad);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#lX\n", "%#lX", whole_ad);
	return_values[j++] =    printf("   printf: %s gives %#lX\n", "%#lX", whole_ad);


printf("\n\n");
printf("\n\n");


//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives %0.2d\n", "%0.2d", 123);
//	return_values[j++] =    printf("   printf: %s gives %0.2d\n", "%0.2d", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %2d\n", "%2d", 123456789);
	return_values[j++] =    printf("   printf: %s gives %2d\n", "%2d", 123456789);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %.3d\n", "%.3d", 123456789);
	return_values[j++] =    printf("   printf: %s gives %.3d\n", "%.3d", 123456789);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %2.3d\n", "%2.3d", 123456789);
	return_values[j++] =    printf("   printf: %s gives %2.3d\n", "%2.3d", 123456789);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %4.3d\n", "%4.3d", 123456789);
	return_values[j++] =    printf("   printf: %s gives %4.3d\n", "%4.3d", 123456789);


	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %5d\n", "%5d", 123);
	return_values[j++] =    printf("   printf: %s gives %5d\n", "%5d", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %.2d\n", "%.2d", 123);
	return_values[j++] =    printf("   printf: %s gives %.2d\n", "%.2d", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %5.2d\n", "%5.2d", 123);
	return_values[j++] =    printf("   printf: %s gives %5.2d\n", "%5.2d", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %.5d\n", "%.5d", 123);
	return_values[j++] =    printf("   printf: %s gives %.5d\n", "%.5d", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %2.5d\n", "%2.5d", 123);
	return_values[j++] =    printf("   printf: %s gives %2.5d\n", "%2.5d", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %4.5d\n", "%4.5d", 123);
	return_values[j++] =    printf("   printf: %s gives %4.5d\n", "%4.5d", 123);

	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %06d\n", "%06d", 123);
	return_values[j++] =    printf("   printf: %s gives %06d\n", "%06d", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %-6d\n", "%-6d", 123);
	return_values[j++] =    printf("   printf: %s gives %-6d\n", "%-6d", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %+6d\n", "%+6d", 123);
	return_values[j++] =    printf("   printf: %s gives %+6d\n", "%+6d", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %+-6d\n", "%+-6d", 123);
	return_values[j++] =    printf("   printf: %s gives %+-6d\n", "%+-6d", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %0+6d\n", "%0+6d", 123);
	return_values[j++] =    printf("   printf: %s gives %0+6d\n", "%0+6d", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %0+d\n", "%0+d", 123);
	return_values[j++] =    printf("   printf: %s gives %0+d\n", "%0+d", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %+d\n", "%+d", 123);
	return_values[j++] =    printf("   printf: %s gives %+d\n", "%+d", 123);

	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %-.2d\n", "%-.2d", 123);
	return_values[j++] =    printf("   printf: %s gives %-.2d\n", "%-.2d", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %+.2d\n", "%+.2d", 123);
	return_values[j++] =    printf("   printf: %s gives %+.2d\n", "%+.2d", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %+-.2d\n", "%+-.2d", 123);
	return_values[j++] =    printf("   printf: %s gives %+-.2d\n", "%+-.2d", 123);


printf("\n\n");
printf("\n\n");


//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives %+o\n", "%+o", 123);
//	return_values[j++] =    printf("   printf: %s gives %+o\n", "%+o", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %5o\n", "%5o", 123);
	return_values[j++] =    printf("   printf: %s gives %5o\n", "%5o", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %.5o\n", "%.5o", 123);
	return_values[j++] =    printf("   printf: %s gives %.5o\n", "%.5o", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %.2o\n", "%.2o", 123);
	return_values[j++] =    printf("   printf: %s gives %.2o\n", "%.2o", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#.2o\n", "%#.2o", 123);
	return_values[j++] =    printf("   printf: %s gives %#.2o\n", "%#.2o", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %2.5o\n", "%2.5o", 123);
	return_values[j++] =    printf("   printf: %s gives %2.5o\n", "%2.5o", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %4.5o\n", "%4.5o", 123);
	return_values[j++] =    printf("   printf: %s gives %4.5o\n", "%4.5o", 123);


	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#4.5o\n", "%#4.5o", 123);
	return_values[j++] =    printf("   printf: %s gives %#4.5o\n", "%#4.5o", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#5o\n", "%#5o", 123);
	return_values[j++] =    printf("   printf: %s gives %#5o\n", "%#5o", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#06o\n", "%#06o", 123);
	return_values[j++] =    printf("   printf: %s gives %#06o\n", "%#06o", 123);


	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#o\n", "%#o", 123);
	return_values[j++] =    printf("   printf: %s gives %#o\n", "%#o", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#6o\n", "%#6o", 123);
	return_values[j++] =    printf("   printf: %s gives %#6o\n", "%#6o", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#-6o\n", "%#-6o", 123);
	return_values[j++] =    printf("   printf: %s gives %#-6o\n", "%#-6o", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#06o\n", "%#06o", 123);
	return_values[j++] =    printf("   printf: %s gives %#06o\n", "%#06o", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#0o\n", "%#.2o", 123);
	return_values[j++] =    printf("   printf: %s gives %#0o\n", "%#.2o", 123);


printf("\n\n");
printf("\n\n");


//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives %+x\n", "%+x", 123);
//	return_values[j++] =    printf("   printf: %s gives %+x\n", "%+x", 123);
//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives %#0-x\n", "%#0-x", 123);
//	return_values[j++] =    printf("   printf: %s gives %#0-x\n", "%#0-x", 123);
//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives %#0-6x\n", "%#0-6x", 123);
//	return_values[j++] =    printf("   printf: %s gives %#0-6x\n", "%#0-6x", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %5x\n", "%5x", 123);
	return_values[j++] =    printf("   printf: %s gives %5x\n", "%5x", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %.5x\n", "%.5x", 123);
	return_values[j++] =    printf("   printf: %s gives %.5x\n", "%.5x", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %.2x\n", "%.2x", 123);
	return_values[j++] =    printf("   printf: %s gives %.2x\n", "%.2x", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#.2x\n", "%#.2x", 123);
	return_values[j++] =    printf("   printf: %s gives %#.2x\n", "%#.2x", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %2.5x\n", "%2.5x", 123);
	return_values[j++] =    printf("   printf: %s gives %2.5x\n", "%2.5x", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %4.5x\n", "%4.5x", 123);
	return_values[j++] =    printf("   printf: %s gives %4.5x\n", "%4.5x", 123);


	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#4.5x\n", "%#4.5x", 123);
	return_values[j++] =    printf("   printf: %s gives %#4.5x\n", "%#4.5x", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#5x\n", "%#5x", 123);
	return_values[j++] =    printf("   printf: %s gives %#5x\n", "%#5x", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#06x\n", "%#06x", 123);
	return_values[j++] =    printf("   printf: %s gives %#06x\n", "%#06x", 123);


	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#6x\n", "%#6x", 123);
	return_values[j++] =    printf("   printf: %s gives %#6x\n", "%#6x", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#0x\n", "%#0x", 123);
	return_values[j++] =    printf("   printf: %s gives %#0x\n", "%#0x", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#x\n", "%#x", 123);
	return_values[j++] =    printf("   printf: %s gives %#x\n", "%#x", 123);


printf("\n\n");
printf("\n\n");


//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives %+X\n", "%+X", 123);
//	return_values[j++] =    printf("   printf: %s gives %+X\n", "%+X", 123);
//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives %#0-X\n", "%#0-X", 123);
//	return_values[j++] =    printf("   printf: %s gives %#0-X\n", "%#0-X", 123);
//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives %#-06X\n", "%#-06X", 123);
//	return_values[j++] =    printf("   printf: %s gives %#-06X\n", "%#-06X", 123);
//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives %#0-6X\n", "%#0-6X", 123);
//	return_values[j++] =    printf("   printf: %s gives %#0-6X\n", "%#0-6X", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %5X\n", "%5X", 123);
	return_values[j++] =    printf("   printf: %s gives %5X\n", "%5X", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %.5X\n", "%.5X", 123);
	return_values[j++] =    printf("   printf: %s gives %.5X\n", "%.5X", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %.2X\n", "%.2X", 123);
	return_values[j++] =    printf("   printf: %s gives %.2X\n", "%.2X", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#.2X\n", "%#.2X", 123);
	return_values[j++] =    printf("   printf: %s gives %#.2X\n", "%#.2X", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %2.5X\n", "%2.5X", 123);
	return_values[j++] =    printf("   printf: %s gives %2.5X\n", "%2.5X", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %4.5X\n", "%4.5X", 123);
	return_values[j++] =    printf("   printf: %s gives %4.5X\n", "%4.5X", 123);


	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#4.5X\n", "%#4.5X", 123);
	return_values[j++] =    printf("   printf: %s gives %#4.5X\n", "%#4.5X", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#5X\n", "%#5X", 123);
	return_values[j++] =    printf("   printf: %s gives %#5X\n", "%#5X", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#06X\n", "%#06X", 123);
	return_values[j++] =    printf("   printf: %s gives %#06X\n", "%#06X", 123);



	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#6X\n", "%#6X", 123);
	return_values[j++] =    printf("   printf: %s gives %#6X\n", "%#6X", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#0X\n", "%#0X", 123);
	return_values[j++] =    printf("   printf: %s gives %#0X\n", "%#0X", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %#X\n", "%#X", 123);
	return_values[j++] =    printf("   printf: %s gives %#X\n", "%#X", 123);


printf("\n\n");
printf("\n\n");


//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives %#u\n", "%#u", 123);
//	return_values[j++] =    printf("   printf: %s gives %#u\n", "%#u", 123);
//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives %+u\n", "%+u", 123);
//	return_values[j++] =    printf("   printf: %s gives %+u\n", "%+u", 123);
//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] = ft_printf("ft_printf: %s gives %0-u\n", "%0-u", 123);
//	return_values[j++] =    printf("   printf: %s gives %0-u\n", "%0-u", 123);
//	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
//	return_values[j++] =    printf("   printf: %s gives %0.2u\n", "%0.2u", 123);
//	return_values[j++] = ft_printf("ft_printf: %s gives %0.2u\n", "%0.2u", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %5u\n", "%5u", 123);
	return_values[j++] =    printf("   printf: %s gives %5u\n", "%5u", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %.5u\n", "%.5u", 123);
	return_values[j++] =    printf("   printf: %s gives %.5u\n", "%.5u", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %.2u\n", "%.2u", 123);
	return_values[j++] =    printf("   printf: %s gives %.2u\n", "%.2u", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %-.2u\n", "%-.2u", 123);
	return_values[j++] =    printf("   printf: %s gives %-.2u\n", "%-.2u", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %2.5u\n", "%2.5u", 123);
	return_values[j++] =    printf("   printf: %s gives %2.5u\n", "%2.5u", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %4.5u\n", "%4.5u", 123);
	return_values[j++] =    printf("   printf: %s gives %4.5u\n", "%4.5u", 123);


	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %4.5u\n", "%4.5u", 123);
	return_values[j++] =    printf("   printf: %s gives %4.5u\n", "%4.5u", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %5u\n", "%5u", 123);
	return_values[j++] =    printf("   printf: %s gives %5u\n", "%5u", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %6u\n", "%6u", 123);
	return_values[j++] =    printf("   printf: %s gives %6u\n", "%6u", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %0u\n", "%0u", 123);
	return_values[j++] =    printf("   printf: %s gives %0u\n", "%0u", 123);
	printf(C_GREEN"\n\nTest %d:\n"RESET, ++i); printf("\n");
	return_values[j++] = ft_printf("ft_printf: %s gives %06u\n", "%06u", 123);
	return_values[j++] =    printf("   printf: %s gives %06u\n", "%06u", 123);


	i = 0;
	while (i < j)
	{
		if (return_values[i] == return_values[i + 1])
			printf(C_GREEN"Test %3d: printf %d ;    printf %d\n"RESET, i / 2, return_values[i], return_values[i + 1]);
		else
			printf(C_RED"Test %3d: printf %d ;    printf %d\n"RESET, i / 2, return_values[i], return_values[i + 1]);
		i += 2;
	}

	return (0);
}
