#include "../ft_printf.h"
#include <stdio.h>

int main()
{
	printf("\n\n\ntest printf\n");
	ft_printf("test ft_printf\n");

	printf("\n\n\ntest printf %%\n");
	ft_printf("test ft_printf %%\n");

	printf("\n\n\ntest printf %d\n", 10);
	ft_printf("test ft_printf %d\n", 10);

	printf("\n\n\ntest %sf\n", "print");
	ft_printf("test ft_%sf\n", "print");

	printf("\n\n\ntest printf %#x\n", 123);
	ft_printf("test ft_printf %#x\n", 123);

	//printf("\n\n\ntest printf %#-+05.5d and %#-+06.5d\n", 123456, 123);
	ft_printf("test ft_printf %#-+05.5d and %#-+06.5d\n", 123456, 123);

	return (0);
}
