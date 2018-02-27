#include "../ft_printf.h"
#include <stdio.h>


#define C_RED     "\x1b[31m"
#define C_GREEN   "\x1b[32m"
#define C_YELLOW  "\x1b[33m"
#define C_BLUE    "\x1b[34m"
#define C_MAGENTA "\x1b[35m"
#define C_CYAN    "\x1b[36m"
#define RESET     "\x1b[0m"

int		main()
{
	float f	= 123.456789;
	double d = 1234567.8987654321;

	int i = -1;
	int j = 0;
	int return_values[400];

	printf(C_BLUE"\nTesting bonuses that can be compared to printf."RESET); printf("\n");
	
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %f\n", "%f", f);
	  return_values[j++] =    printf("   printf: %s gives %f\n", "%f", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.0f\n", "%.0f", f);
	  return_values[j++] =    printf("   printf: %s gives %.0f\n", "%.0f", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.0f\n", "%.0f", 0);
	  return_values[j++] =    printf("   printf: %s gives %.0f\n", "%.0f", 0);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %+f\n", "%+f", f);
	  return_values[j++] =    printf("   printf: %s gives %+f\n", "%+f", f);
	check_retvals(j, return_values);	
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %0f\n", "%0f", f);
	  return_values[j++] =    printf("   printf: %s gives %0f\n", "%0f", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#f\n", "%#f", f);
	  return_values[j++] =    printf("   printf: %s gives %#f\n", "%#f", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %-.3f\n", "%-.3f", f);
	  return_values[j++] =    printf("   printf: %s gives %-.3f\n", "%-.3f", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.3f\n", "%.3f", f);
	  return_values[j++] =    printf("   printf: %s gives %.3f\n", "%.3f", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.15f\n", "%.15f", f);
	  return_values[j++] =    printf("   printf: %s gives %.15f\n", "%.15f", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %20f\n", "%20f", f);
	  return_values[j++] =    printf("   printf: %s gives %20f\n", "%20f", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %20.15f\n", "%20.15f", f);
	  return_values[j++] =    printf("   printf: %s gives %20.15f\n", "%20.15f", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %020.15f\n", "%020.15f", f);
	  return_values[j++] =    printf("   printf: %s gives %020.15f\n", "%020.15f", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %-20.15f\n", "%-20.15f", f);
	  return_values[j++] =    printf("   printf: %s gives %-20.15f\n", "%-20.15f", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %-20.3f\n", "%-20.3f", f);
	  return_values[j++] =    printf("   printf: %s gives %-20.3f\n", "%-20.3f", f);
	check_retvals(j, return_values);




	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %e\n", "%e", f);
	  return_values[j++] =    printf("   printf: %s gives %e\n", "%e", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.0e\n", "%.0e", f);
	  return_values[j++] =    printf("   printf: %s fives %.0e\n", "%.0e", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.0e\n", "%.0e", 0);
	  return_values[j++] =    printf("   printf: %s gives %.0e\n", "%.0e", 0);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %+e\n", "%+e", f);
	  return_values[j++] =    printf("   printf: %s gives %+e\n", "%+e", f);
	check_retvals(j, return_values);	
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %0e\n", "%0e", f);
	  return_values[j++] =    printf("   printf: %s gives %0e\n", "%0e", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#e\n", "%#e", f);
	  return_values[j++] =    printf("   printf: %s gives %#e\n", "%#e", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %-.3e\n", "%-.3e", f);
	  return_values[j++] =    printf("   printf: %s gives %-.3e\n", "%-.3e", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.3e\n", "%.3e", f);
	  return_values[j++] =    printf("   printf: %s gives %.3e\n", "%.3e", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.15e\n", "%.15e", f);
	  return_values[j++] =    printf("   printf: %s gives %.15e\n", "%.15e", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %20e\n", "%20e", f);
	  return_values[j++] =    printf("   printf: %s gives %20e\n", "%20e", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %20.15e\n", "%20.15e", f);
	  return_values[j++] =    printf("   printf: %s gives %20.15e\n", "%20.15e", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %020.15e\n", "%020.15e", f);
	  return_values[j++] =    printf("   printf: %s gives %020.15e\n", "%020.15e", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %-20.15e\n", "%-20.15e", f);
	  return_values[j++] =    printf("   printf: %s gives %-20.15e\n", "%-20.15e", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %-20.3e\n", "%-20.3e", f);
	  return_values[j++] =    printf("   printf: %s gives %-20.3e\n", "%-20.3e", f);
	check_retvals(j, return_values);




	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %a\n", "%a", f);
	  return_values[j++] =    printf("   printf: %s gives %a\n", "%a", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.0a\n", "%.0a", f);
	  return_values[j++] =    printf("   printf: %s gives %.0a\n", "%.0a", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.0a\n", "%.0a", 0);
	  return_values[j++] =    printf("   printf: %s gives %.0a\n", "%.0a", 0);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %+a\n", "%+a", f);
	  return_values[j++] =    printf("   printf: %s gives %+a\n", "%+a", f);
	check_retvals(j, return_values);	
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %0a\n", "%0a", f);
	  return_values[j++] =    printf("   printf: %s gives %0a\n", "%0a", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#a\n", "%#a", f);
	  return_values[j++] =    printf("   printf: %s gives %#a\n", "%#a", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %-.3a\n", "%-.3a", f);
	  return_values[j++] =    printf("   printf: %s gives %-.3a\n", "%-.3a", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.3a\n", "%.3a", f);
	  return_values[j++] =    printf("   printf: %s gives %.3a\n", "%.3a", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.15a\n", "%.15a", f);
	  return_values[j++] =    printf("   printf: %s gives %.15a\n", "%.15a", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %20a\n", "%20a", f);
	  return_values[j++] =    printf("   printf: %s gives %20a\n", "%20a", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %20.15a\n", "%20.15a", f);
	  return_values[j++] =    printf("   printf: %s gives %20.15a\n", "%20.15a", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %020.15a\n", "%020.15a", f);
	  return_values[j++] =    printf("   printf: %s gives %020.15a\n", "%020.15a", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %-20.15a\n", "%-20.15a", f);
	  return_values[j++] =    printf("   printf: %s gives %-20.15a\n", "%-20.15a", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %-20.3a\n", "%-20.3a", f);
	  return_values[j++] =    printf("   printf: %s gives %-20.3a\n", "%-20.3a", f);
	check_retvals(j, return_values);



	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %g\n", "%g", f);
	  return_values[j++] =    printf("   printf: %s gives %g\n", "%g", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.0g\n", "%.0g", f);
	  return_values[j++] =    printf("   printf: %s gives %.0g\n", "%.0g", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.0g\n", "%.0g", 0);
	  return_values[j++] =    printf("   printf: %s gives %.0g\n", "%.0g", 0);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %+g\n", "%+g", f);
	  return_values[j++] =    printf("   printf: %s gives %+g\n", "%+g", f);
	check_retvals(j, return_values);	
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %0g\n", "%0g", f);
	  return_values[j++] =    printf("   printf: %s gives %0g\n", "%0g", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %#g\n", "%#g", f);
	  return_values[j++] =    printf("   printf: %s gives %#g\n", "%#g", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %-.3g\n", "%-.3g", f);
	  return_values[j++] =    printf("   printf: %s gives %-.3g\n", "%-.3g", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.3g\n", "%.3g", f);
	  return_values[j++] =    printf("   printf: %s gives %.3g\n", "%.3g", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %.15g\n", "%.15g", f);
	  return_values[j++] =    printf("   printf: %s gives %.15g\n", "%.15g", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %20g\n", "%20g", f);
	  return_values[j++] =    printf("   printf: %s gives %20g\n", "%20g", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %20.15g\n", "%20.15g", f);
	  return_values[j++] =    printf("   printf: %s gives %20.15g\n", "%20.15g", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %020.15g\n", "%020.15g", f);
	  return_values[j++] =    printf("   printf: %s gives %020.15g\n", "%020.15g", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %-20.15g\n", "%-20.15g", f);
	  return_values[j++] =    printf("   printf: %s gives %-20.15g\n", "%-20.15g", f);
	check_retvals(j, return_values);
	printf(C_BLUE"\n\nTest %d:"RESET, ++i); printf("\n");
	  return_values[j++] = ft_printf("ft_printf: %s gives %-20.3g\n", "%-20.3g", f);
	  return_values[j++] =    printf("   printf: %s gives %-20.3g\n", "%-20.3g", f);
	check_retvals(j, return_values);


//add color and color tests ?

printf("\n\n");
printf(C_BLUE"\nTests on return values :"RESET);
printf("\n\n");


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
		printf(C_GREEN"\nThere are 0 failed tests based on return values. Do however check that output values are adequate on tests where a width flag might return strings of equal lengths.\n"RESET) :
		printf(C_RED"\nThere are %d failed tests based on return values.\n"RESET, fails);
	printf("\n");

printf("\n\n");
printf(C_BLUE"\nTests on functionalities not available in printf :"RESET);
printf("\n\n");

	printf(C_BLUE"Testing binary %b: "RESET); prinft("\n");
	ft_printf("\t%b\n", 0xAAAAAAAA);
	printf("Expected :\n\t10101010101010101010101010101010\n\n"); 

# if 0
	printf(C_BLUE"Testing non-printables %r: "RESET); prinft("\n");
	ft_printf("\t%r\n", );
	printf("Expected :\n\t\n\n"); 
# endif

	return (0);
}
