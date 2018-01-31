#include "../libft/libft.h"
#include <stdarg.h>
#include <stdio.h>

int		test_function(int test, ...)
{
	va_list		args;
	int			status;

	va_start(args, format);
	printf("Test is %d | Expected : %d\n", ft_ptrarrlen(args), test);
	va_end(args);
	return (status);
}

int		main()
{
	
}
