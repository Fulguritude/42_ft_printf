#include <stdio.h>
#include <locale.h>

int		main()
{
	int i = -1;
	int j = 0;
	int return_values[200];


	// tout backslash ne faisant pas partie d'une escape sequence est ignoré par le compilateur
/*	return_values[j++] = printf("%\n");
	return_values[j++] = printf("\%\n");
	return_values[j++] = printf("%\%\n");
	return_values[j++] = printf("\%\%\n");
	return_values[j++] = printf("%\%\%\n");
	return_values[j++] = printf("\%\%\%\n");
	return_values[j++] = printf("%\n");
	return_values[j++] = printf("%%\n");
	return_values[j++] = printf("%%%\n");
	return_values[j++] = printf("%%%%\n");
	return_values[j++] = printf("%\n");
	return_values[j++] = printf("%\\\n");
	return_values[j++] = printf("\\%\n");
	return_values[j++] = printf("\%\%\n");
	return_values[j++] = printf("\%d\n", ++i);
	return_values[j++] = printf("\%%d\n", ++i);
	return_values[j++] = printf("%d\%\%\n", ++i);
	return_values[j++] = printf("\%%c\n", ++i);
*/
	setlocale(LC_ALL, "");
/*
	return_values[j++] = printf("%c\n", ++i);
	return_values[j++] = printf("momo\n\0momo\n"); //le \0 dans le fmt string casse le fmt string
	return_values[j++] = printf("momo\n\0momo %d\n", ++i);
	return_values[j++] = printf("%s gives %bd\n", "%bd", ++i);
	return_values[j++] = printf("%s gives %lld\n", "%lld", ++i);
	return_values[j++] = printf("%s gives %llld\n", "%llld", ++i); //why %ld ? => length flags are special
	return_values[j++] = printf("%s gives %jld\n", "%jld", ++i);
	return_values[j++] = printf("%s gives %ljd\n", "%ljd", ++i);
	return_values[j++] = printf("%s gives %jlld\n", "%jlld", ++i);
	return_values[j++] = printf("%s gives %jd\n", "%jd", ++i);
	return_values[j++] = printf("%s gives %j5d\n", "%j5d", ++i);
	return_values[j++] = printf("%s gives %5jd\n", "%5jd", ++i);
	return_values[j++] = printf("%s gives %.5j5d\n", "%.5j5d", ++i);
	return_values[j++] = printf("%s gives %5j.8d\n", "%5j.8d", ++i);
	return_values[j++] = printf("A \\0 for good measure %c, %s gives %5j.8d\n", 0, "%5j.8d", ++i);
*/
//"%2$0+-ld" "%D"
	return_values[j++] = printf("%c\n", L'é');
	return_values[j++] = printf("%lc\n", L'é');
	return_values[j++] = printf("%C\n", L'é');
	return_values[j++] = printf("%lC\n", L'é');
	return_values[j++] = printf("%s\n", L"résumé s");
	return_values[j++] = printf("%ls\n", L"résumé ls");
	return_values[j++] = printf("%S\n", L"résumé S");
	return_values[j++] = printf("%lS\n", L"résumé lS");
	return_values[j++] = printf("%jS\n", L"résumé jS");
	return_values[j++] = printf("%hhS\n", L"résumé hhS");
	return_values[j++] = printf("%hhs\n", L"résumé hhs");
	return_values[j++] = printf("%hhs\n", "rasuma hhs");


	return_values[j++] = printf("%s gives %.5s\n", "%.5s", "ft_printf");
	return_values[j++] = printf("%s gives %12s\n", "%12s", "ft_printf");
	return_values[j++] = printf("%s gives %12.5s\n", "%12.5s", "ft_printf");
	return_values[j++] = printf("%s gives %-12.5s\n", "%-12.5s", "ft_printf");
	return_values[j++] = printf("%s gives %#12.5s\n", "%#12.5s", "ft_printf");
	return_values[j++] = printf("%s gives %-12.5s\n", "%0-12.5s", "ft_printf");
	return_values[j++] = printf("%s gives %012.5s\n", "%012.5s", "ft_printf");

printf("\n\n");
//les é comptent pour pile 2 bytes. Remarquez que le .5 ne fait afficher que 2 é sur 3 par la suite
	return_values[j++] = printf("%s gives %.5ls\n", "%.5ls", L"éft_printf");
	return_values[j++] = printf("%s gives %12ls\n", "%12ls", L"éft_printf");
	return_values[j++] = printf("%s gives %12.5ls\n", "%12.5ls", L"éft_printf");
	return_values[j++] = printf("%s gives %-12.5ls\n", "%-12.5ls", L"éft_printf");
	return_values[j++] = printf("%s gives %#12.5ls\n", "%#12.5ls", L"éft_printf");
	return_values[j++] = printf("%s gives %-12.5ls\n", "%0-12.5ls", L"éft_printf");
	return_values[j++] = printf("%s gives %012.5ls\n", "%012.5ls", L"éft_printf");

printf("\n\n");


	return_values[j++] = printf("%s gives %.5ls\n", "%.5ls", L"éééft_printf");
	return_values[j++] = printf("%s gives %12ls\n", "%12ls", L"éééft_printf");
	return_values[j++] = printf("%s gives %12.5ls\n", "%12.5ls", L"éééft_printf");
	return_values[j++] = printf("%s gives %-12.5ls\n", "%-12.5ls", L"éééft_printf");
	return_values[j++] = printf("%s gives %#12.5ls\n", "%#12.5ls", L"éééft_printf");
	return_values[j++] = printf("%s gives %-12.5ls\n", "%0-12.5ls", L"éééft_printf");
	return_values[j++] = printf("%s gives %012.5ls\n", "%012.5ls", L"éééft_printf");


printf("\n\n");

	return_values[j++] = printf("%s gives %p\n", "%p", &i);
	return_values[j++] = printf("%s gives %#p\n", "%#p", &i);

	return_values[j++] = printf("%s gives %x\n", "%x", &i);
	return_values[j++] = printf("%s gives %X\n", "%X", &i);
	return_values[j++] = printf("%s gives %lx\n", "%lx", &i);
	return_values[j++] = printf("%s gives %lX\n", "%lX", &i);

	return_values[j++] = printf("%s gives %#x\n", "%#x", &i);
	return_values[j++] = printf("%s gives %#X\n", "%#X", &i);
	return_values[j++] = printf("%s gives %#lx\n", "%#lx", &i);
	return_values[j++] = printf("%s gives %#lX\n", "%#lX", &i);

printf("\n\n");

	return_values[j++] = printf("%s gives %2d\n", "%2d", 123456789);
	return_values[j++] = printf("%s gives %.3d\n", "%.3d", 123456789);
	return_values[j++] = printf("%s gives %2.3d\n", "%2.3d", 123456789);
	return_values[j++] = printf("%s gives %4.3d\n", "%4.3d", 123456789);

	return_values[j++] = printf("%s gives %5d\n", "%5d", 123);
	return_values[j++] = printf("%s gives %.2d\n", "%.2d", 123);
	return_values[j++] = printf("%s gives %#.2d\n", "%#.2d", 123);
	return_values[j++] = printf("%s gives %.5d\n", "%.5d", 123);
	return_values[j++] = printf("%s gives %2.5d\n", "%2.5d", 123);
	return_values[j++] = printf("%s gives %4.5d\n", "%4.5d", 123);

	return_values[j++] = printf("%s gives %#4.5d\n", "%#4.5d", 123);
	return_values[j++] = printf("%s gives %#5d\n", "%#5d", 123);
	return_values[j++] = printf("%s gives %#06d\n", "%#06d", 123);
	return_values[j++] = printf("%s gives %#-06d\n", "%#-06d", 123);
	return_values[j++] = printf("%s gives %#0-6d\n", "%#0-6d", 123);

	return_values[j++] = printf("%s gives %#0-+6d\n", "%#0-+6d", 123);
	return_values[j++] = printf("%s gives %#+6d\n", "%#+6d", 123);
	return_values[j++] = printf("%s gives %#0-+d\n", "%#0-+d", 123);
	return_values[j++] = printf("%s gives %#0+d\n", "%#0+d", 123);
	return_values[j++] = printf("%s gives %#+d\n", "%#+d", 123);
	return_values[j++] = printf("%s gives %+d\n", "%+d", 123);

printf("\n\n");

	return_values[j++] = printf("%s gives %5o\n", "%5o", 123);
	return_values[j++] = printf("%s gives %.5o\n", "%.5o", 123);
	return_values[j++] = printf("%s gives %.2o\n", "%.2o", 123);
	return_values[j++] = printf("%s gives %#.2o\n", "%#.2o", 123);
	return_values[j++] = printf("%s gives %2.5o\n", "%2.5o", 123);
	return_values[j++] = printf("%s gives %4.5o\n", "%4.5o", 123);

	return_values[j++] = printf("%s gives %#4.5o\n", "%#4.5o", 123);
	return_values[j++] = printf("%s gives %#5o\n", "%#5o", 123);
	return_values[j++] = printf("%s gives %#06o\n", "%#06o", 123);
	return_values[j++] = printf("%s gives %#-06o\n", "%#-06o", 123);
	return_values[j++] = printf("%s gives %#0-6o\n", "%#0-6o", 123);

	return_values[j++] = printf("%s gives %#0-+6o\n", "%#0-+6o", 123);
	return_values[j++] = printf("%s gives %#+6o\n", "%#+6o", 123);
	return_values[j++] = printf("%s gives %#0-+o\n", "%#0-+o", 123);
	return_values[j++] = printf("%s gives %#0+o\n", "%#0+o", 123);
	return_values[j++] = printf("%s gives %#+o\n", "%#+o", 123);
	return_values[j++] = printf("%s gives %+o\n", "%+o", 123);

printf("\n\n");

	return_values[j++] = printf("%s gives %5x\n", "%5x", 123);
	return_values[j++] = printf("%s gives %.5x\n", "%.5x", 123);
	return_values[j++] = printf("%s gives %.2x\n", "%.2x", 123);
	return_values[j++] = printf("%s gives %#.2x\n", "%#.2x", 123);
	return_values[j++] = printf("%s gives %2.5x\n", "%2.5x", 123);
	return_values[j++] = printf("%s gives %4.5x\n", "%4.5x", 123);

	return_values[j++] = printf("%s gives %#4.5x\n", "%#4.5x", 123);
	return_values[j++] = printf("%s gives %#5x\n", "%#5x", 123);
	return_values[j++] = printf("%s gives %#06x\n", "%#06x", 123);
	return_values[j++] = printf("%s gives %#-06x\n", "%#-06x", 123);
	return_values[j++] = printf("%s gives %#0-6x\n", "%#0-6x", 123);

	return_values[j++] = printf("%s gives %#0-+6x\n", "%#0-+6x", 123);
	return_values[j++] = printf("%s gives %#+6x\n", "%#+6x", 123);
	return_values[j++] = printf("%s gives %#0-+x\n", "%#0-+x", 123);
	return_values[j++] = printf("%s gives %#0+x\n", "%#0+x", 123);
	return_values[j++] = printf("%s gives %#+x\n", "%#+x", 123);
	return_values[j++] = printf("%s gives %+x\n", "%+x", 123);

printf("\n\n");

	return_values[j++] = printf("%s gives %5X\n", "%5X", 123);
	return_values[j++] = printf("%s gives %.5X\n", "%.5X", 123);
	return_values[j++] = printf("%s gives %.2X\n", "%.2X", 123);
	return_values[j++] = printf("%s gives %#.2X\n", "%#.2X", 123);
	return_values[j++] = printf("%s gives %2.5X\n", "%2.5X", 123);
	return_values[j++] = printf("%s gives %4.5X\n", "%4.5X", 123);

	return_values[j++] = printf("%s gives %#4.5X\n", "%#4.5X", 123);
	return_values[j++] = printf("%s gives %#5X\n", "%#5X", 123);
	return_values[j++] = printf("%s gives %#06X\n", "%#06X", 123);
	return_values[j++] = printf("%s gives %#-06X\n", "%#-06X", 123);
	return_values[j++] = printf("%s gives %#0-6X\n", "%#0-6X", 123);

	return_values[j++] = printf("%s gives %#0-+6X\n", "%#0-+6X", 123);
	return_values[j++] = printf("%s gives %#+6X\n", "%#+6X", 123);
	return_values[j++] = printf("%s gives %#0-+X\n", "%#0-+X", 123);
	return_values[j++] = printf("%s gives %#0+X\n", "%#0+X", 123);
	return_values[j++] = printf("%s gives %#+X\n", "%#+X", 123);
	return_values[j++] = printf("%s gives %+X\n", "%+X", 123);

printf("\n\n");

	++i;
	return_values[j++] = printf("%d in octal : %o\n", i, i);
	return_values[j++] = printf("%#d in octal : %#o\n", i, i);
	i = -1;
	while (++i < j)
		printf("%d ; ", return_values[i]);
	printf("\n\n");
	return (0);
}
