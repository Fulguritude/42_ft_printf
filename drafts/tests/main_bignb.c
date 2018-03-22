#include "../ft_printf.h"
#include <assert.h>
#include <stdio.h>

void	ft_vlqdelmul(t_u32 nb_to_delete, ...)
{
	va_list	args;
	t_u32	i;
	t_vlq	*tmp;

	va_start(args, nb_to_delete);
	i = 0;
	while (i < nb_to_delete)
	{
		tmp = (t_vlq*)va_arg(args, t_vlq*);
		ft_vlqdel(tmp);
		++i;
	}
	va_end(args);
}

void	ft_strdelmul(t_u32 nb_to_delete, ...)
{
	va_list	args;
	t_u32	i;
	char	**tmp;

	va_start(args, nb_to_delete);
	i = 0;
	while (i < nb_to_delete)
	{
		tmp = (char**)va_arg(args, char**);
		ft_strdel(tmp);
		++i;
	}
	va_end(args);
}

int		main(void)
{
	t_vlq	vlq1;
	t_vlq	vlq2;
	t_vlq	vlqe;
	t_vlq	vlqr;
	char	*str1;
	char	*str2;
	char	*stre;
	char	*strr;

	int		i = 0;

//vlqnew, vlqdel
printf("Test %d: vlqnew, vlqdel\n", ++i);
	vlq1 = ft_vlqnew(0);
		assert(vlq1 == NULL);

	ft_vlqdel(&vlq1);
		assert(vlq1 == NULL);

	vlq1 = ft_vlqnew(1);
		assert(vlq1[0] == 0);

	ft_vlqdel(&vlq1);
		assert(vlq1 == NULL);

	vlq1 = ft_vlqnew(3);
		assert(vlq1[0] == _MSB_);
		assert(vlq1[1] == _MSB_);
		assert(vlq1[2] == 0);
	ft_vlqdel(&vlq1);

//basic operations
//addition without carry, atovlq binary
printf("Test %d: atovlq binary, addition without carry.\n", ++i);
	vlq1 = ft_atovlq("10101010101010101010101010101010101010101010101010101010101010101010101010101010", BINAR);
	vlq2 =  ft_atovlq("1010101010101010101010101010101010101010101010101010101010101010101010101010101", BINAR);
	vlqe = ft_atovlq("11111111111111111111111111111111111111111111111111111111111111111111111111111111", BINAR);
	vlqr = ft_vlq_add(vlq1, vlq2);
		str1 = ft_vlqhex(vlq1);
		str2 = ft_vlqhex(vlq2);
		stre = ft_vlqhex(vlqe);
		strr = ft_vlqhex(vlqr);
		ft_printf("str1 = %s\nstr2 = %s\nstre = %s\nstrr = %s\n\n", str1, str2, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(4, &vlq1, &vlq2, &vlqe, &vlqr);
	ft_strdelmul(4, &str1, &str2, &stre, &strr);

//addition with accumulator and carry and different sizes, atovlq binary with leading zeros, vlqdup
printf("Test %d: vlqdup, addition with acc, carry and different size vlqs, leading zeros in atovlq\n", ++i);
	vlq1 = ft_atovlq( "11111111111111111111111111111111111111111111111111111111111111111111111111111111", BINAR);
	vlq2 = ft_atovlq( "00000000000000000000000000000000000000000000000000000000000000000000000000000001", BINAR);
	vlqe = ft_atovlq("100000000000000000000000000000000000000000000000000000000000000000000000000000000", BINAR);
	vlqr = ft_vlqdup(vlq1);
	ft_vlq_add_acc(&vlqr, vlq2);
		str1 = ft_vlqhex(vlq1);
		str2 = ft_vlqhex(vlq2);
		stre = ft_vlqhex(vlqe);
		strr = ft_vlqhex(vlqr);
		ft_printf("str1 = %s\nstr2 = %s\nstre = %s\nstrr = %s\n\n", str1, str2, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(4, &vlq1, &vlq2, &vlqe, &vlqr);
	ft_strdelmul(4, &str1, &str2, &stre, &strr);

//multiplication
printf("Test %d: multiplication\n", ++i);
	vlq1 = ft_atovlq( "11111111111111111111111111111111111111111111111111111111111111111111111111111111", BINAR);
	vlq2 = ft_atovlq("100000000000000000000000000000000000000000000000000000000000000000000000000000001", BINAR);
	vlqe = ft_atovlq("1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111", BINAR);
	vlqr = ft_vlqdup(vlq1);
	ft_vlq_add_acc(&vlqr, vlq2);
		str1 = ft_vlqhex(vlq1);
		str2 = ft_vlqhex(vlq2);
		stre = ft_vlqhex(vlqe);
		strr = ft_vlqhex(vlqr);
		ft_printf("str1 = %s\nstr2 = %s\nstre = %s\nstrr = %s\n\n", str1, str2, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(4, &vlq1, &vlq2, &vlqe, &vlqr);
	ft_strdelmul(4, &str1, &str2, &stre, &strr);

//atovlq decimal, hexadecimal
printf("Test %d: atovlq decimal, hexadecimal\n", ++i);
	vlq1 = ft_atovlq("FFFF0000AAAABBBBCCCCDDDDEEEEFFFF", HXUPP);
	vlq2 = ft_atovlq("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", HXLOW);
	vlqe = ft_atovlq("11111111111", DECIM);
	vlqr = ft_atovlq("11111111111111111111111111111111111111111111111111111111", DECIM);
		str1 = ft_vlqhex(vlq1);
		str2 = ft_vlqhex(vlq2);
		stre = ft_vlqhex(vlqe);
		strr = ft_vlqhex(vlqr);
		ft_printf("str1 = %s\nstr2 = %s\nstre = %s\nstrr = %s\n\n", str1, str2, stre, strr);
//		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(4, &vlq1, &vlq2, &vlqe, &vlqr);
	ft_strdelmul(4, &str1, &str2, &stre, &strr);

//subtraction, a < b, a > b.
printf("Test %d.1: subtraction a > b\n", ++i);
	vlq1 = ft_atovlq("11111111111111111111111111111111111111111111111111111111111111111111111111111111", BINAR);
	vlq2 = ft_atovlq("10101010101010101010101010101010101010101010101010101010101010101010101010101010", BINAR);
	vlqe = ft_atovlq( "1010101010101010101010101010101010101010101010101010101010101010101010101010101", BINAR);
	vlqr = ft_vlq_sub(vlq1, vlq2);
		str1 = ft_vlqhex(vlq1);
		str2 = ft_vlqhex(vlq2);
		stre = ft_vlqhex(vlqe);
		strr = ft_vlqhex(vlqr);
		ft_printf("str1 = %s\nstr2 = %s\nstre = %s\nstrr = %s\n\n", str1, str2, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(4, &vlq1, &vlq2, &vlqe, &vlqr);
	ft_strdelmul(4, &str1, &str2, &stre, &strr);

printf("Test %d.2: subtraction a < b\n", i);
	vlq2 = ft_atovlq("987654321987654321987654321", DECIM);
	vlq1 = ft_atovlq("876543210876543210876543210", DECIM);
	vlqe = ft_atovlq("111111111111111111111111111", DECIM);
	vlqr = ft_vlq_sub(vlq1, vlq2);
		str1 = ft_vlqhex(vlq1);
		str2 = ft_vlqhex(vlq2);
		stre = ft_vlqhex(vlqe);
		strr = ft_vlqhex(vlqr);
		ft_printf("str1 = %s\nstr2 = %s\nstre = %s\nstrr = %s\n\n", str1, str2, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(4, &vlq1, &vlq2, &vlqe, &vlqr);
	ft_strdelmul(4, &str1, &str2, &stre, &strr);

//subtraction with accumulator and carry
	vlq1 = ft_atovlq("987654321987654321987654321", DECIM);
	vlq2 = ft_atovlq("876543210876543210876543210", DECIM);
	vlqe = ft_atovlq("111111111111111111111111111", DECIM);
	vlqr = ft_vlqdup(vlq1);
	ft_vlq_sub_acc(&vlqr, vlq2);
		str1 = ft_vlqhex(vlq1);
		str2 = ft_vlqhex(vlq2);
		stre = ft_vlqhex(vlqe);
		strr = ft_vlqhex(vlqr);
		ft_printf("str1 = %s\nstr2 = %s\nstre = %s\nstrr = %s\n\n", str1, str2, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(4, &vlq1, &vlq2, &vlqe, &vlqr);
	ft_strdelmul(4, &str1, &str2, &stre, &strr);

	return (0);
}
