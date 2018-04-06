#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#include "../ft_printf.h"
#include <stdio.h>
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
# define SHOW_CORRECT_RESULT_COMPARISON 	1

# define _SMALL_BONUSES_					0
#  define PERCENT_b							1
#  define PERCENT_B							1
#  define PERCENT_r							1
#  define COLOR_BONUS						1
# define SMALL_BONUSES 						_SMALL_BONUSES_ && (PERCENT_b || PERCENT_B || PERCENT_r)

# define _FLOAT_BONUSES_					1
#  define PERCENT_aA						1
#  define PERCENT_eE						1
#  define PERCENT_fF						1
#  define PERCENT_gG						0
#  define SPECIAL_CASES						1 && (PERCENT_aA || PERCENT_eE || PERCENT_fF || PERCENT_gG)
#  define NORMAL_CASES						1 && (PERCENT_aA || PERCENT_eE || PERCENT_fF || PERCENT_gG)
# define FLOAT_BONUSES						_FLOAT_BONUSES_ && (NORMAL_CASES || SPECIAL_CASES)
/*
** ---------------------------------------------------------------------------
**
**		FT_PRINTF BONUS FUNCTIONS TESTER	
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
**	 -	Consider special case mentioned in: 
**		https://ryanstutorials.net/binary-tutorial/binary-floating-point.php
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
**	 -	Normalized floats refer to floats expressed as sign-exp-mantissa.
**		Denormalized floats are reserved, special values (NaN, +Inf, -Inf, etc).
**		Subnormal floats are floats with an exponent field of 0 which behave 
**			strangely.
**		https://randomascii.wordpress.com/2012/03/08/float-precisionfrom-zero-to-100-digits-2/ 
**
**	 -	Calling a va_arg() on a non-existing argument always causes a segfault.
**
**	 -	Useful links:
**			- https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html
**			- Steele, White, 1990 (Dragon4) ; Doitsch, 2004 (Grisu)
**			- https://github.com/libtom/libtommath
**			- D. Knuth AoCP, vol 2, chap 4, sec 4.2 & 4.3.
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

int		main()
{
	char	*str1 = NULL;
	char	*str2 = NULL;

#if FLOAT_BONUSES
	int		i = -1;
	int		j = 0;
	int		return_values[400];
	int		str_fails = -1;

	printf(C_BLUE"\nTesting bonuses that can be compared to printf."C_RESET); printf("\n");

/*
** TODO Verify all values
** TODO add subnormal checks
*/

# if SPECIAL_CASES
	double	plus_inf = 1./0.;
	double	plus_zero = 0x0.000000000000p+0;
	double	dbl_max = DBL_MAX;
	double	minus_inf = -(1./0.);
	double	minus_zero = -0x0.000000000000p+0;
	double	dbl_min = -DBL_MAX;
	double	mach_err = DBL_EPSILON;
	double	not_a_nb = 0.0f / 0.0f; //NAN; //NAN == 0.0f / 0.0f

#  if PERCENT_fF
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-inf) gives %lf\n", "%lf", minus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-inf) gives %lf\n", "%lf", minus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+inf) gives %lf\n", "%lf", plus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+inf) gives %lf\n", "%lf", plus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (eps) gives %lf\n", "%lf", mach_err);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (eps) gives %lf\n", "%lf", mach_err);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %lf\n", "%lf", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %lf\n", "%lf", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %lf\n", "%lf", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %lf\n", "%lf", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %+lf\n", "%+lf", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %+lf\n", "%+lf", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %+lf\n", "%+lf", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %+lf\n", "%+lf", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (NaN) gives %lf\n", "%lf", not_a_nb);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (NaN) gives %lf\n", "%lf", not_a_nb);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-DBL_MAX) gives %lf\n", "%lf", dbl_min);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-DBL_MAX) gives %lf\n", "%lf", dbl_min);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (DBL_MAX) gives %lf\n", "%lf", dbl_max);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (DBL_MAX) gives %lf\n", "%lf", dbl_max);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);

	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-inf) gives %.300lf\n", "%.300lf", minus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-inf) gives %.300lf\n", "%.300lf", minus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+inf) gives %.300lf\n", "%.300lf", plus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+inf) gives %.300lf\n", "%.300lf", plus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (eps) gives %.300lf\n", "%.300lf", mach_err);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (eps) gives %.300lf\n", "%.300lf", mach_err);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %.300lf\n", "%.300lf", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %.300lf\n", "%.300lf", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %.300lf\n", "%.300lf", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %.300lf\n", "%.300lf", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %+.300lf\n", "%+.300lf", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %+.300lf\n", "%+.300lf", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %+.300lf\n", "%+.300lf", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %+.300lf\n", "%+.300lf", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (NaN) gives %.300lf\n", "%.300lf", not_a_nb);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (NaN) gives %.300lf\n", "%.300lf", not_a_nb);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-DBL_MAX) gives %.300lf\n", "%.300lf", dbl_min);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-DBL_MAX) gives %.300lf\n", "%.300lf", dbl_min);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (DBL_MAX) gives %.300lf\n", "%.300lf", dbl_max);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (DBL_MAX) gives %.300lf\n", "%.300lf", dbl_max);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#  endif


#  if PERCENT_eE
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-inf) gives %le\n", "%le", minus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-inf) gives %le\n", "%le", minus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+inf) gives %le\n", "%le", plus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+inf) gives %le\n", "%le", plus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (eps) gives %le\n", "%le", mach_err);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (eps) gives %le\n", "%le", mach_err);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %le\n", "%le", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %le\n", "%le", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %le\n", "%le", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %le\n", "%le", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %+le\n", "%+le", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %+le\n", "%+le", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %+le\n", "%+le", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %+le\n", "%+le", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (NaN) gives %le\n", "%le", not_a_nb);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (NaN) gives %le\n", "%le", not_a_nb);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-DBL_MAX) gives %le\n", "%le", dbl_min);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-DBL_MAX) gives %le\n", "%le", dbl_min);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (DBL_MAX) gives %le\n", "%le", dbl_max);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (DBL_MAX) gives %le\n", "%le", dbl_max);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#  endif


#  if PERCENT_gG
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-inf) gives %lg\n", "%lg", minus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-inf) gives %lg\n", "%lg", minus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+inf) gives %lg\n", "%lg", plus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+inf) gives %lg\n", "%lg", plus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (eps) gives %lg\n", "%lg", mach_err);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (eps) gives %lg\n", "%lg", mach_err);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %lg\n", "%lg", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %lg\n", "%lg", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %lg\n", "%lg", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %lg\n", "%lg", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %+lg\n", "%+lg", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %+lg\n", "%+lg", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %+lg\n", "%+lg", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %+lg\n", "%+lg", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (NaN) gives %lg\n", "%lg", not_a_nb);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (NaN) gives %lg\n", "%lg", not_a_nb);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-DBL_MAX) gives %lg\n", "%lg", dbl_min);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-DBL_MAX) gives %lg\n", "%lg", dbl_min);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (DBL_MAX) gives %lg\n", "%lg", dbl_max);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (DBL_MAX) gives %lg\n", "%lg", dbl_max);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#  endif


#  if PERCENT_aA
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-inf) gives %la\n", "%la", minus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-inf) gives %la\n", "%la", minus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+inf) gives %la\n", "%la", plus_inf);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+inf) gives %la\n", "%la", plus_inf);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (eps) gives %la\n", "%la", mach_err);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (eps) gives %la\n", "%la", mach_err);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %la\n", "%la", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %la\n", "%la", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %la\n", "%la", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %la\n", "%la", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-0.0) gives %+la\n", "%+la", minus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-0.0) gives %+la\n", "%+la", minus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (+0.0) gives %+la\n", "%+la", plus_zero);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (+0.0) gives %+la\n", "%+la", plus_zero);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (NaN) gives %la\n", "%la", not_a_nb);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (NaN) gives %la\n", "%la", not_a_nb);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (-DBL_MAX) gives %la\n", "%la", dbl_min);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (-DBL_MAX) gives %la\n", "%la", dbl_min);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s (DBL_MAX) gives %la\n", "%la", dbl_max);
	  return_values[j++] =    asprintf(&str2, "   printf: %s (DBL_MAX) gives %la\n", "%la", dbl_max);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#  endif
# endif



# if NORMAL_CASES
	float 	f = 0.55555; // 0xf.edcba012345p-64;		//other vals: 123.456789;
	double 	d = 16.125; //-0x1.123456789abcdp+1010;	//other vals: 1234567.8987654321; 0.000002432543654332000; 1e+23; 1e+20

#  if PERCENT_fF
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %f\n", "%f", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %f\n", "%f", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0f\n", "%.0f", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0f\n", "%.0f", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0f\n", "%.0f", 0.0);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0f\n", "%.0f", 0.0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+f\n", "%+f", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+f\n", "%+f", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);	
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0f\n", "%0f", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0f\n", "%0f", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#f\n", "%#f", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#f\n", "%#f", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.3f\n", "%-.3f", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.3f\n", "%-.3f", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.3f\n", "%.3f", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.3f\n", "%.3f", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15f\n", "%.15f", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15f\n", "%.15f", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20f\n", "%20f", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20f\n", "%20f", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020f\n", "%020f", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020f\n", "%020f", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15f\n", "%20.15f", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15f\n", "%20.15f", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020.15f\n", "%020.15f", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020.15f\n", "%020.15f", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.15f\n", "%-20.15f", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.15f\n", "%-20.15f", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.3f\n", "%-20.3f", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.3f\n", "%-20.3f", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#  endif


#  if PERCENT_eE
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %e\n", "%e", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %e\n", "%e", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0e\n", "%.0e", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0e\n", "%.0e", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0e\n", "%.0e", 0.0);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0e\n", "%.0e", 0.0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+e\n", "%+e", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+e\n", "%+e", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);	
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0e\n", "%0e", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0e\n", "%0e", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#e\n", "%#e", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#e\n", "%#e", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.3e\n", "%-.3e", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.3e\n", "%-.3e", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.3e\n", "%.3e", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.3e\n", "%.3e", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15e\n", "%.15e", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15e\n", "%.15e", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20e\n", "%20e", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20e\n", "%20e", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020e\n", "%020e", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020e\n", "%020e", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15e\n", "%20.15e", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15e\n", "%20.15e", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020.15e\n", "%020.15e", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020.15e\n", "%020.15e", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.15e\n", "%-20.15e", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.15e\n", "%-20.15e", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.3e\n", "%-20.3e", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.3e\n", "%-20.3e", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#  endif


#  if PERCENT_aA
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %a\n", "%a", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %a\n", "%a", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0a\n", "%.0a", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0a\n", "%.0a", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0a\n", "%.0a", 0.0);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0a\n", "%.0a", 0.0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+a\n", "%+a", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+a\n", "%+a", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);	
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0a\n", "%0a", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0a\n", "%0a", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#a\n", "%#a", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#a\n", "%#a", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.3a\n", "%-.3a", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.3a\n", "%-.3a", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.3a\n", "%.3a", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.3a\n", "%.3a", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15a\n", "%.15a", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15a\n", "%.15a", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20a\n", "%20a", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20a\n", "%20a", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020a\n", "%020a", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020a\n", "%020a", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15a\n", "%20.15a", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15a\n", "%20.15a", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020.15a\n", "%020.15a", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020.15a\n", "%020.15a", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.15a\n", "%-20.15a", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.15a\n", "%-20.15a", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.3a\n", "%-20.3a", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.3a\n", "%-20.3a", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#  endif


#  if PERCENT_gG
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %g\n", "%g", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %g\n", "%g", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0g\n", "%.0g", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0g\n", "%.0g", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0g\n", "%.0g", 0.0);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0g\n", "%.0g", 0.0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+g\n", "%+g", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+g\n", "%+g", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);	
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0g\n", "%0g", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0g\n", "%0g", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#g\n", "%#g", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#g\n", "%#g", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.3g\n", "%-.3g", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.3g\n", "%-.3g", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.3g\n", "%.3g", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.3g\n", "%.3g", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15g\n", "%.15g", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15g\n", "%.15g", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20g\n", "%20g", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20g\n", "%20g", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020g\n", "%020g", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020g\n", "%020g", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15g\n", "%20.15g", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15g\n", "%20.15g", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020.15g\n", "%020.15g", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020.15g\n", "%020.15g", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.15g\n", "%-20.15g", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.15g\n", "%-20.15g", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.3g\n", "%-20.3g", f);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.3g\n", "%-20.3g", f);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#  endif

/*
** fl_l
*/

#  if PERCENT_fF
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %lf\n", "%lf", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %lf\n", "%lf", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0lf\n", "%.0lf", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0lf\n", "%.0lf", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0lf\n", "%.0lf", 0.0);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0lf\n", "%.0lf", 0.0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+lf\n", "%+lf", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+lf\n", "%+lf", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);	
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0lf\n", "%0lf", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0lf\n", "%0lf", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#lf\n", "%#lf", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#lf\n", "%#lf", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.3lf\n", "%-.3lf", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.3lf\n", "%-.3lf", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.3lf\n", "%.3lf", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.3lf\n", "%.3lf", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15lf\n", "%.15lf", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15lf\n", "%.15lf", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20lf\n", "%20lf", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20lf\n", "%20lf", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020lf\n", "%020lf", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020lf\n", "%020lf", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15lf\n", "%20.15lf", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15lf\n", "%20.15lf", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020.15lf\n", "%020.15lf", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020.15lf\n", "%020.15lf", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.15lf\n", "%-20.15lf", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.15lf\n", "%-20.15lf", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.3lf\n", "%-20.3lf", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.3lf\n", "%-20.3lf", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#  endif


#  if PERCENT_eE
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %le\n", "%le", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %le\n", "%le", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0le\n", "%.0le", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0le\n", "%.0le", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0le\n", "%.0le", 0.0);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0le\n", "%.0le", 0.0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+le\n", "%+le", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+le\n", "%+le", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);	
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0le\n", "%0le", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0le\n", "%0le", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#le\n", "%#le", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#le\n", "%#le", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.3le\n", "%-.3le", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.3le\n", "%-.3le", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.3le\n", "%.3le", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.3le\n", "%.3le", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15le\n", "%.15le", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15le\n", "%.15le", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20le\n", "%20le", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20le\n", "%20le", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020le\n", "%020le", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020le\n", "%020le", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15le\n", "%20.15le", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15le\n", "%20.15le", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020.15le\n", "%020.15le", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020.15le\n", "%020.15le", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.15le\n", "%-20.15le", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.15le\n", "%-20.15le", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.3le\n", "%-20.3le", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.3le\n", "%-20.3le", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#  endif


#  if PERCENT_aA
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %la\n", "%la", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %la\n", "%la", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0la\n", "%.0la", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0la\n", "%.0la", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0la\n", "%.0la", 0.0);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0la\n", "%.0la", 0.0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+la\n", "%+la", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+la\n", "%+la", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);	
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0la\n", "%0la", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0la\n", "%0la", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#la\n", "%#la", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#la\n", "%#la", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.3la\n", "%-.3la", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.3la\n", "%-.3la", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.3la\n", "%.3la", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.3la\n", "%.3la", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15la\n", "%.15la", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15la\n", "%.15la", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20la\n", "%20la", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20la\n", "%20la", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020la\n", "%020la", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020la\n", "%020la", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15la\n", "%20.15la", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15la\n", "%20.15la", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020.15la\n", "%020.15la", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020.15la\n", "%020.15la", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.15la\n", "%-20.15la", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.15la\n", "%-20.15la", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.3la\n", "%-20.3la", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.3la\n", "%-20.3la", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
#  endif


#  if PERCENT_gG
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %lg\n", "%lg", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %lg\n", "%lg", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0lg\n", "%.0lg", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0lg\n", "%.0lg", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.0lg\n", "%.0lg", 0.0);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.0lg\n", "%.0lg", 0.0);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %+lg\n", "%+lg", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %+lg\n", "%+lg", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);	
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %0lg\n", "%0lg", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %0lg\n", "%0lg", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %#lg\n", "%#lg", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %#lg\n", "%#lg", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-.3lg\n", "%-.3lg", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-.3lg\n", "%-.3lg", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.3lg\n", "%.3lg", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.3lg\n", "%.3lg", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %.15lg\n", "%.15lg", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %.15lg\n", "%.15lg", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20lg\n", "%20lg", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20lg\n", "%20lg", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020lg\n", "%020lg", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020lg\n", "%020lg", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %20.15lg\n", "%20.15lg", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %20.15lg\n", "%20.15lg", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %020.15lg\n", "%020.15lg", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %020.15lg\n", "%020.15lg", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.15lg\n", "%-20.15lg", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.15lg\n", "%-20.15lg", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
	printf(C_BLUE"\n\nTest %d:"C_RESET, ++i); printf("\n");
	  return_values[j++] = ft_asprintf(&str1, "ft_printf: %s gives %-20.3lg\n", "%-20.3lg", d);
	  return_values[j++] =    asprintf(&str2, "   printf: %s gives %-20.3lg\n", "%-20.3lg", d);
	str_fails = check_retvals(j, return_values, &str1, str2); ft_strdel(&str1); ft_strdel(&str2);
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

#if 0
	tmp = NULL;

	ft_asprintf(&tmp, "{red}red{eoc} ; {yellow}yellow{eoc} ; {green}green{eoc} ; {cyan}cyan{eoc} ; {blue}blue{eoc} ; {magenta}magenta{eoc}\n");
	ft_putmem(tmp);
	ft_strdel(&tmp);

	printf("\n");

	ft_asprintf(&tmp, "{red}%s{eoc} ; {yellow}%s {eoc} ; {green}green, null_%c_char{eoc} ; {cyan}cyan, fake_eoc_%s_in_a_%%s{eoc} ; {blue}blue, %#+09x{eoc} ; {magenta} %s{eoc}\n", "red, {}only_a_%s_between{}", "yellow, {}trailing_space {}", 1, "{eoc}", 0x123456, "magenta, {} leading_space{}");
	ft_putmem(tmp);
	ft_strdel(&tmp);
#endif
# endif


#endif

	return (0);
}
