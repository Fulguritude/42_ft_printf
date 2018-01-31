#include <stdio.h>

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
//"%2$0+-ld"
	++i;
	return_values[j++] = printf("%d in octal : %o\n", i, i);
	i = -1;
	while (++i < j)
		printf("%d\n", return_values[i]);
	return (0);
}
