#include <stdio.h>

int		main()
{
	printf("%\n");
	printf("\%\n");
	printf("%\%\n");
	printf("\%\%\n");
	printf("%\%\%\n");
	printf("\%\%\%\n");
	printf("%\n");
	printf("%%\n");
	printf("%%%\n");
	printf("%%%%\n");
	printf("%\n");
	printf("%\\\n");
	printf("\\%\n");
	printf("\%\%\n");
	printf("\%d\n", 40);
	printf("\%%d\n", 41);
	printf("%d\%\%\n", 42);
	printf("\%%c\n", 0);
	printf("%c\n", 0);
	printf("momo\n\0momo\n"); //le \0 dans le fmt string casse le fmt string
	printf("20 in octal : %o\n", 20);

	return (0);
}
