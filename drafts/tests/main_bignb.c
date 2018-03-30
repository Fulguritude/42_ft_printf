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

void	ft_bignbdelmul(t_u32 nb_to_delete, ...)
{
	va_list	args;
	t_u32	i;
	t_bignb	*tmp;

	va_start(args, nb_to_delete);
	i = 0;
	while (i < nb_to_delete)
	{
		tmp = (t_bignb*)va_arg(args, t_bignb*);
		ft_bignbdel(tmp);
		++i;
	}
	va_end(args);
}

int		main(void)
{
	char*(*vlq_tostring)(t_vlq);
	t_vlq	vlq1;
	t_vlq	vlq2;
	t_vlq	vlqe;
	t_vlq	vlqr;
	char	*str1;
	char	*str2;
	char	*stre;
	char	*strr;
	t_u32	shift;

	vlq_tostring = &ft_vlqhex; //&ft_vlq_abstractval_as_hex;

	int		i = 0;


//VLQ tests
ft_printf("\n{blue_bg}VLQ test\n\n{eoc}");

//vlqnew, vlqdel
printf("Test %d: vlqnew, vlqdel\n\n", ++i);
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
		str1 = vlq_tostring(vlq1);
		str2 = vlq_tostring(vlq2);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstr1 = %s\n\tstr2 = %s\n\tstre = %s\n\tstrr = %s\n\n", str1, str2, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(4, &vlq1, &vlq2, &vlqe, &vlqr);
	ft_strdelmul(4, &str1, &str2, &stre, &strr);

printf("Test %d:addition with carry.\n", ++i);
	vlq1 = ft_atovlq("101010101010101010101010101010101010101010101010101010101010101010101010101010\
1010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010\
10101010101010101010101010101010101010101010101010101010101010", BINAR);
	vlq2 = ft_atovlq("111111111111111111111111111111111111111111111111111111111111111111111111111111\
1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111\
11111111111111111111111111111111111111111111111111111111111111", BINAR);
	vlqe = ft_atovlq("1101010101010101010101010101010101010101010101010101010101010101010101010101010\
1010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010\
10101010101010101010101010101010101010101010101010101010101001", BINAR);
	vlqr = ft_vlq_add(vlq1, vlq2);
		str1 = vlq_tostring(vlq1);
		str2 = vlq_tostring(vlq2);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstr1 = %s\n\tstr2 = %s\n\tstre = %s\n\tstrr = %s\n\n", str1, str2, stre, strr);
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
		str1 = vlq_tostring(vlq1);
		str2 = vlq_tostring(vlq2);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstr1 = %s\n\tstr2 = %s\n\tstre = %s\n\tstrr = %s\n\n", str1, str2, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(4, &vlq1, &vlq2, &vlqe, &vlqr);
	ft_strdelmul(4, &str1, &str2, &stre, &strr);

//bitshift left
printf("Test %d: bitshift left 1\n", ++i);
	vlq1 = ft_atovlq("11000100010001000100010001000100010001000100010001000100010001000100010001000\
1000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000\
10001000100010001000100010001000100010001000100010010100010001000100010001000100010001000100010001000\
1000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000\
1000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000", BINAR);
	shift = 140;
	vlqe = ft_atovlq("11000100010001000100010001000100010001000100010001000100010001000100010001000\
1000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000\
10001000100010001000100010001000100010001000100010010100010001000100010001000100010001000100010001000\
1000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000\
1000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000\
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", BINAR);
	vlqr = ft_vlq_bsl(vlq1, shift);
		str1 = vlq_tostring(vlq1);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstr1 = %s\n\tstre = %s\n\tstrr = %s\n\n", str1, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(3, &vlq1, &vlqe, &vlqr);
	ft_strdelmul(3, &str1, &stre, &strr);

printf("Test %d: bitshift left 2\n", ++i);
	vlq1 = ft_atovlq("11111111111111111111111111111111111111111111111111111111111111111110111111111111111111111111111111111111111111111111111111111111111111111111111111111111111", BINAR);
	shift = 59;
	vlqe = ft_atovlq("11111111111111111111111111111111111111111111111111111111111111111110111111111111111111111111111111111111111111111111111111111111111111111111111111111111111\
00000000000000000000000000000000000000000000000000000000000", BINAR);
	vlqr = ft_vlq_bsl(vlq1, shift);
		str1 = vlq_tostring(vlq1);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstr1 = %s\n\tstre = %s\n\tstrr = %s\n\n", str1, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(3, &vlq1, &vlqe, &vlqr);
	ft_strdelmul(3, &str1, &stre, &strr);

printf("Test %d: bitshift left 3\n", ++i);
	vlq1 = ft_atovlq("11111111111111111111111111111111111111111111111111111111111111111110111111111111111111111111111111111111111111111111111111111111111111111111111111111111111", BINAR);
	shift = 5;
	vlqe = ft_atovlq("1111111111111111111111111111111111111111111111111111111111111111111011111111111111111111111111111111111111111111111111111111111111111111111111111111111111100000", BINAR);
	vlqr = ft_vlq_bsl(vlq1, shift);
		str1 = vlq_tostring(vlq1);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstr1 = %s\n\tstre = %s\n\tstrr = %s\n\n", str1, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(3, &vlq1, &vlqe, &vlqr);
	ft_strdelmul(3, &str1, &stre, &strr);


printf("Test %d: bitshift left 4\n", ++i);
	vlq1 = ft_atovlq("11111111111111111111111111111111111111111111111111111111111111111\
110111111111111111111111111111111111111111111111111111111111111111111111111111111111111111", BINAR);
	shift = 63;
	vlqe = ft_atovlq("1111111111111111111111111111111111111111111111111111111111111111111\
01111111111111111111111111111111111111111111111111111111111111111111111111111111111111110\
00000000000000000000000000000000000000000000000000000000000000", BINAR);
	vlqr = ft_vlq_bsl(vlq1, shift);
		str1 = vlq_tostring(vlq1);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstr1 = %s\n\tstre = %s\n\tstrr = %s\n\n", str1, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(3, &vlq1, &vlqe, &vlqr);
	ft_strdelmul(3, &str1, &stre, &strr);

//bitshift right
printf("Test %d: bitshift right 1\n", ++i);
	vlq1 = ft_atovlq("11000100010001000100010001000100010001000100010001000100010001000100010001000\
1000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000\
1000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000\
1000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000\
1000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000", BINAR);
	shift = 141;
	vlqe = ft_atovlq("11000100010001000100010001000100010001000100010001000100010001000100010001000\
1000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000\
1000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000\
10001000100010001000100010001000100010001000100010001000100", BINAR);
	vlqr = ft_vlq_bsr(vlq1, shift);
		str1 = vlq_tostring(vlq1);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstr1 = %s\n\tstre = %s\n\tstrr = %s\n\n", str1, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(3, &vlq1, &vlqe, &vlqr);
	ft_strdelmul(3, &str1, &stre, &strr);

printf("Test %d: bitshift right 2\n", ++i);
	vlq1 = ft_atovlq("111111111111111111111111111111111111011111111111111111111111111111111111111111111", BINAR);
	shift = 5;
	vlqe = ft_atovlq("1111111111111111111111111111111111110111111111111111111111111111111111111111", BINAR);
	vlqr = ft_vlq_bsr(vlq1, shift);
		str1 = vlq_tostring(vlq1);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstr1 = %s\n\tstre = %s\n\tstrr = %s\n\n", str1, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(3, &vlq1, &vlqe, &vlqr);
	ft_strdelmul(3, &str1, &stre, &strr);

printf("Test %d: bitshift right 3\n", ++i);
	vlq1 = ft_atovlq("111111111111111111111111111111111011011111111111111111111111111111111111111111111111111111111111111111111111111111011011111111111111111111111111111111111111111111", BINAR);
	shift = 30;
	vlqe = ft_atovlq("111111111111111111111111111111111011011111111111111111111111111111111111111111111111111111111111111111111111111111011011111111111111", BINAR);
	vlqr = ft_vlq_bsr(vlq1, shift);
		str1 = vlq_tostring(vlq1);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstr1 = %s\n\tstre = %s\n\tstrr = %s\n\n", str1, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(3, &vlq1, &vlqe, &vlqr);
	ft_strdelmul(3, &str1, &stre, &strr);

printf("Test %d: bitshift right 4\n", ++i);
	vlq1 = ft_atovlq("11111111111111111111111111111111111111111111111111111111111111111110111111111111111111111111111111111111111111111111111111111111111111111101111111111111111", BINAR);
	shift = 63;
	vlqe = ft_atovlq("11111111111111111111111111111111111111111111111111111111111111111110111111111111111111111111", BINAR);
	vlqr = ft_vlq_bsr(vlq1, shift);
		str1 = vlq_tostring(vlq1);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstr1 = %s\n\tstre = %s\n\tstrr = %s\n\n", str1, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(3, &vlq1, &vlqe, &vlqr);
	ft_strdelmul(3, &str1, &stre, &strr);

//multiplication
printf("Test %d: multiplication 1\n", ++i);
	vlq1 = ft_atovlq( "11111111111111111111111111111111111011011111111111111111111111111111111111111111", BINAR);
	vlq2 = ft_atovlq("100000000000000000000000000000000000000000000000000000000000000000000000000000001", BINAR);
	vlqe = ft_atovlq("1111111111111111111111111111111111101101111111111111111111111111111111111111111111111111111111111111111111111111111011011111111111111111111111111111111111111111", BINAR);
	vlqr = ft_vlq_mul(vlq1, vlq2);
		str1 = vlq_tostring(vlq1);
		str2 = vlq_tostring(vlq2);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstr1 = %s\n\tstr2 = %s\n\tstre = %s\n\tstrr = %s\n\n", str1, str2, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(4, &vlq1, &vlq2, &vlqe, &vlqr);
	ft_strdelmul(4, &str1, &str2, &stre, &strr);

printf("Test %d: multiplication 2\n", ++i);
	vlq1 = ft_atovlq("11101010101010101010111111111111111111111111111111011011111111111111111111111111101010101011", BINAR);
	vlq2 = ft_atovlq("111000111000111111000111000111111000111000111111000111000111111000111000111111000111000111111000111000111", BINAR);
	vlqe = ft_atovlq("11010000100110010010010111101111111010111101111110110111101111110111011101111110101000\
110010100000000011100001111011101101001101000101111100101000101111101001000101111101000100101111101010111101101", BINAR);
	vlqr = ft_vlq_mul(vlq1, vlq2);
		str1 = vlq_tostring(vlq1);
		str2 = vlq_tostring(vlq2);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstr1 = %s\n\tstr2 = %s\n\tstre = %s\n\tstrr = %s\n\n", str1, str2, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(4, &vlq1, &vlq2, &vlqe, &vlqr);
	ft_strdelmul(4, &str1, &str2, &stre, &strr);

//multiplication with accumulator
printf("Test %d: multiplication with accumulator\n", ++i);
	vlq1 = ft_atovlq("101010101010101", BINAR);
	vlq2 = ft_atovlq("1010101010101010", BINAR);
	vlqe = ft_atovlq("111000111000110001110001110010", BINAR);
	vlqr = ft_vlqdup(vlq1);
	ft_vlq_mul_acc(&vlqr, vlq2);
		str1 = vlq_tostring(vlq1);
		str2 = vlq_tostring(vlq2);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstr1 = %s\n\tstr2 = %s\n\tstre = %s\n\tstrr = %s\n\n", str1, str2, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(4, &vlq1, &vlq2, &vlqe, &vlqr);
	ft_strdelmul(4, &str1, &str2, &stre, &strr);

//atovlq decimal, hexadecimal
printf("Test %d: atovlq hexadecimal 1\n", ++i);
	vlqr = ft_atovlq("FFFFEEEEDDDDCCCCBBBBAAAA0000AAAABBBBCCCCDDDDEEEEFFFF", HXUPP);
	vlqe = ft_atovlq("111111111111111111101110111011101101110111011101110011001100\
1100101110111011101110101010101010100000000000000000101010101010101010111011101110\
111100110011001100110111011101110111101110111011101111111111111111", BINAR);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstre = %s\n\tstrr = %s\n\n", stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(2, &vlqe, &vlqr);
	ft_strdelmul(2, &stre, &strr);

printf("Test %d: atovlq hexadecimal 2\n", ++i);
	vlqr = ft_atovlq("188888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888", HXLOW);
	vlqe = ft_atovlq("11000100010001000100010001000100010001000100010001000100010001000100010001000\
1000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000\
1000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000\
1000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000\
1000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000", BINAR);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstre = %s\n\tstrr = %s\n\n", stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(2, &vlqe, &vlqr);
	ft_strdelmul(2, &stre, &strr);

printf("Test %d: atovlq hexadecimal 3\n", ++i);
	vlqr = ft_atovlq("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", HXLOW);
	vlqe = ft_atovlq("1010101010101010101010101010101010101010101010101010101010101010101010101010\
10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010\
10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010\
1010101010101010101010101010101010101010101010101010101010101010101010101010101010101010", BINAR);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstre = %s\n\tstrr = %s\n\n", stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(2, &vlqe, &vlqr);
	ft_strdelmul(2, &stre, &strr);

printf("Test %d: atovlq decimal 1\n", ++i);
	vlqr = ft_atovlq("12345678901", DECIM);
	vlqe = ft_atovlq("1011011111110111000001110000110101", BINAR);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstre = %s\n\tstrr = %s\n\n", stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(2, &vlqe, &vlqr);
	ft_strdelmul(2, &stre, &strr);

printf("Test %d: atovlq decimal 2\n", ++i);
/*	vlqr = ft_atovlq("11111111111111111111111111111111111111111111111111111111", DECIM);
	vlqe = ft_atovlq("1110100000000010110001010111011000111100010100000111100111111\
11110001110001011000101011100110110001011110010110010101101100101011000111000111000\
111000111000111000111000111000111000111", BINAR);
*/
/*
11111111111111111111111111111111111111111111111111111111111111111111111111111
1890aa80be385102083701a2907066f8bd9f2a28b717671c71c71c71c71c71c7

111111111111111111111111111111111111111111111111111111111111111111111111111111111111111 to hex
3931f10be63df26e5e5c397c87b6ad33a1dc3cdf5b8e9d207ef1c71c71c71c71c71c71c7

*/
	vlqr = ft_atovlq("111111111111111111111111111111111111111111111111111111111111111111111111111111111111111", DECIM);
	vlqe = ft_atovlq("3931f10be63df26e5e5c397c87b6ad33a1dc3cdf5b8e9d207ef1c71c71c71c71c71c71c7", HXLOW);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstre = %s\n\tstrr = %s\n\n", stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(2, &vlqe, &vlqr);
	ft_strdelmul(2, &stre, &strr);

//subtraction, a < b, a > b.
printf("Test %d.1: subtraction a > b, no carry, same size\n", ++i);
	vlq1 = ft_atovlq("11111111111111111111111111111111111111111111111111111111111111111111111111111111", BINAR);
	vlq2 = ft_atovlq("10101010101010101010101010101010101010101010101010101010101010101010101010101010", BINAR);
	vlqe = ft_atovlq( "1010101010101010101010101010101010101010101010101010101010101010101010101010101", BINAR);
	vlqr = ft_vlq_sub(vlq1, vlq2);
		str1 = vlq_tostring(vlq1);
		str2 = vlq_tostring(vlq2);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstr1 = %s\n\tstr2 = %s\n\tstre = %s\n\tstrr = %s\n\n", str1, str2, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(4, &vlq1, &vlq2, &vlqr, &vlqe);
	ft_strdelmul(4, &str1, &str2, &strr, &stre);

printf("Test %d.2: subtraction a < b, no carry, same size\n", i);
	vlq2 = ft_atovlq("987654321987654321987654321", DECIM);
	vlq1 = ft_atovlq("876543210876543210876543210", DECIM);
	vlqe = ft_atovlq("111111111111111111111111111", DECIM);
	vlqr = ft_vlq_sub(vlq1, vlq2);
		str1 = vlq_tostring(vlq1);
		str2 = vlq_tostring(vlq2);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstr1 = %s\n\tstr2 = %s\n\tstre = %s\n\tstrr = %s\n\n", str1, str2, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(4, &vlq1, &vlq2, &vlqe, &vlqr);
	ft_strdelmul(4, &str1, &str2, &stre, &strr);

printf("Test %d.3: subtraction a > b, lots of carries, very different size\n", ++i);
	vlq1 = ft_atovlq("100000000000000000000000000000000000000000000000000000000000000000000000000000\
000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", BINAR);
	vlq2 = ft_atovlq(																							"1", BINAR);
	vlqe = ft_atovlq("111111111111111111111111111111111111111111111111111111111111111111111111111111\
11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111", BINAR);
	vlqr = ft_vlq_sub(vlq1, vlq2);
		str1 = vlq_tostring(vlq1);
		str2 = vlq_tostring(vlq2);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstr1 = %s\n\tstr2 = %s\n\tstre = %s\n\tstrr = %s\n\n", str1, str2, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(4, &vlq1, &vlq2, &vlqe, &vlqr);
	ft_strdelmul(4, &str1, &str2, &stre, &strr);

printf("Test %d.4: subtraction a > b, carry makes first index 0, and index 0 must be removed\n", ++i);
	vlq1 = ft_atovlq("100000000000000000000000000000000000000000000000000000000000000000000000000000\
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", BINAR);
	vlq2 = ft_atovlq(																						  "1", BINAR);
	vlqe = ft_atovlq("111111111111111111111111111111111111111111111111111111111111111111111111111111\
111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111", BINAR);
	vlqr = ft_vlq_sub(vlq1, vlq2);
		str1 = vlq_tostring(vlq1);
		str2 = vlq_tostring(vlq2);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstr1 = %s\n\tstr2 = %s\n\tstre = %s\n\tstrr = %s\n\n", str1, str2, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(4, &vlq1, &vlq2, &vlqe, &vlqr);
	ft_strdelmul(4, &str1, &str2, &stre, &strr);

//subtraction with accumulator and carry
printf("Test %d: subtraction with accumulator a > b\n", ++i);
	vlq1 = ft_atovlq("987654321987654321987654321", DECIM);
	vlq2 = ft_atovlq("876543210876543210876543210", DECIM);
	vlqe = ft_atovlq("111111111111111111111111111", DECIM);
	vlqr = ft_vlqdup(vlq1);
	ft_vlq_sub_acc(&vlqr, vlq2);
		str1 = vlq_tostring(vlq1);
		str2 = vlq_tostring(vlq2);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		ft_printf("\tstr1 = %s\n\tstr2 = %s\n\tstre = %s\n\tstrr = %s\n\n", str1, str2, stre, strr);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
	ft_vlqdelmul(4, &vlq1, &vlq2, &vlqe, &vlqr);
	ft_strdelmul(4, &str1, &str2, &stre, &strr);

//division
	t_vlq	vlqm = NULL;
	t_vlq	vlqf = NULL;
	char	*strf;
	char	*strm;

printf("Test %d: division 1\n", ++i);
	vlq1 = ft_atovlq("100000000000000000000000000000000000000000000000000000000000000000000000000000001", BINAR);
	vlq2 = ft_atovlq( "11111111111111111111111111111111111011011111111111111111111111111111111111111111", BINAR);
	vlqe = ft_atovlq(																				 "1", BINAR);
	vlqf = ft_atovlq(									 "100100000000000000000000000000000000000000010", BINAR);
	ft_vlq_divmod(vlq1, vlq2, &vlqr, &vlqm);
		str1 = vlq_tostring(vlq1);
		str2 = vlq_tostring(vlq2);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		strf = vlq_tostring(vlqf);
		strm = vlq_tostring(vlqm);
		ft_printf("\tstr1 = %s\n\tstr2 = %s\n\t{blue}stre = %s\n\tstrr = %s\n\t{cyan}strf = %s\n\tstrm = %s{eoc}\n\n", str1, str2, stre, strr, strf, strm);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
		assert(ft_vlqcmp(vlqf, vlqm) == 0);
	ft_vlqdelmul(6, &vlq1, &vlq2, &vlqe, &vlqr, &vlqf, &vlqm);
	ft_strdelmul(6, &str1, &str2, &stre, &strr, &strf, &strm);


printf("Test %d: division 2\n", ++i);
	vlq1 = ft_atovlq( "11111111111111111111111111111111111011011111111111111111111111111111111111111111", BINAR);
	vlq2 = ft_atovlq("100000000000000000000000000000000000000000000000000000000000000000000000000000001", BINAR);
	vlqe = ft_atovlq(																				 "0", BINAR);
	vlqf = ft_atovlq( "11111111111111111111111111111111111011011111111111111111111111111111111111111111", BINAR);
	ft_vlq_divmod(vlq1, vlq2, &vlqr, &vlqm);
		str1 = vlq_tostring(vlq1);
		str2 = vlq_tostring(vlq2);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		strf = vlq_tostring(vlqf);
		strm = vlq_tostring(vlqm);
		ft_printf("\tstr1 = %s\n\tstr2 = %s\n\t{blue}stre = %s\n\tstrr = %s\n\t{cyan}strf = %s\n\tstrm = %s{eoc}\n\n", str1, str2, stre, strr, strf, strm);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
		assert(ft_vlqcmp(vlqf, vlqm) == 0);
	ft_vlqdelmul(6, &vlq1, &vlq2, &vlqe, &vlqr, &vlqf, &vlqm);
	ft_strdelmul(6, &str1, &str2, &stre, &strr, &strf, &strm);
/*
36058579944795813131401201709511
/ 4539115051501886157277362859
= 7943
R 4389090716331384147108520474
*/
printf("Test %d: division 3\n", ++i);
	vlq1 = ft_atovlq("111000111000111111000111000111111000111000111111000111000111111000111000111111000111000111111000111000111", BINAR);
	vlq2 = ft_atovlq(			  "11101010101010101010111111111111111111111111111111011011111111111111111111111111101010101011", BINAR);
	vlqe = ft_atovlq("1111100000111"																							, BINAR);
	vlqf = ft_atovlq(			  "11100010111010010010000111000111111001111110110011000011000111111001100010010110001000011010", BINAR);
	ft_vlq_divmod(vlq1, vlq2, &vlqr, &vlqm);
		str1 = vlq_tostring(vlq1);
		str2 = vlq_tostring(vlq2);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		strf = vlq_tostring(vlqf);
		strm = vlq_tostring(vlqm);
		ft_printf("\tstr1 = %s\n\tstr2 = %s\n\t{blue}stre = %s\n\tstrr = %s\n\t{cyan}strf = %s\n\tstrm = %s{eoc}\n\n", str1, str2, stre, strr, strf, strm);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
		assert(ft_vlqcmp(vlqf, vlqm) == 0);
	ft_vlqdelmul(6, &vlq1, &vlq2, &vlqe, &vlqr, &vlqf, &vlqm);
	ft_strdelmul(6, &str1, &str2, &stre, &strr, &strf, &strm);
/*
36058579944795813131401201709511
/ 4345686920363545489324374699
= 8297
R 2415566539476206476864831908
*/

printf("Test %d: division 4\n", ++i);
	vlq1 = ft_atovlq("111000111000111111000111000111111000111000111111000111000111111000111000111111000111000111111000111000111", BINAR);
	vlq2 = ft_atovlq(			  "11100000101010101010111111111111111111111111111111011011111111111111111111111111101010101011", BINAR);
	vlqe = ft_atovlq("10000001101001"																							, BINAR);
	vlqf = ft_atovlq(			   "1111100111000011100000111000111111010000001111010001011000111111001100100001100000110100100", BINAR);
	ft_vlq_divmod(vlq1, vlq2, &vlqr, &vlqm);
		str1 = vlq_tostring(vlq1);
		str2 = vlq_tostring(vlq2);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		strf = vlq_tostring(vlqf);
		strm = vlq_tostring(vlqm);
		ft_printf("\tstr1 = %s\n\tstr2 = %s\n\t{blue}stre = %s\n\tstrr = %s\n\t{cyan}strf = %s\n\tstrm = %s{eoc}\n\n", str1, str2, stre, strr, strf, strm);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
		assert(ft_vlqcmp(vlqf, vlqm) == 0);
	ft_vlqdelmul(6, &vlq1, &vlq2, &vlqe, &vlqr, &vlqf, &vlqm);
	ft_strdelmul(6, &str1, &str2, &stre, &strr, &strf, &strm);

/*
36058579944795813131401201709504
/ 3592
= 10038580162805070470880067291
R 232
*/
printf("Test %d: division 5\n", ++i);
	vlq1 = ft_atovlq("111000111000111111000111000111111000111000111111000111000111111000111000111111000111000111111000111000000", BINAR);
	vlq2 = ft_atovlq(																							  "111000001000", BINAR);
	vlqe = ft_atovlq("1000000110111110111000000010010000111100100100111011101111011100110001101111100111111011011011"			, BINAR);
	vlqf = ft_atovlq(																								  "11101000", BINAR);
	ft_vlq_divmod(vlq1, vlq2, &vlqr, &vlqm);
		str1 = vlq_tostring(vlq1);
		str2 = vlq_tostring(vlq2);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		strf = vlq_tostring(vlqf);
		strm = vlq_tostring(vlqm);
		ft_printf("\tstr1 = %s\n\tstr2 = %s\n\t{blue}stre = %s\n\tstrr = %s\n\t{cyan}strf = %s\n\tstrm = %s{eoc}\n\n", str1, str2, stre, strr, strf, strm);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
		assert(ft_vlqcmp(vlqf, vlqm) == 0);
	ft_vlqdelmul(6, &vlq1, &vlq2, &vlqe, &vlqr, &vlqf, &vlqm);
	ft_strdelmul(6, &str1, &str2, &stre, &strr, &strf, &strm);

printf("Test %d: division 6\n", ++i);
	vlq1 = ft_atovlq("111000111000111111000111000111111000111000111111000111000111111000111000111111000111000111111000111000000", BINAR);
	vlq2 = ft_atovlq(																							  			 "1", BINAR);
	vlqe = ft_atovlq("111000111000111111000111000111111000111000111111000111000111111000111000111111000111000111111000111000000", BINAR);
	vlqf = ft_atovlq(																								 		 "0", BINAR);
	ft_vlq_divmod(vlq1, vlq2, &vlqr, &vlqm);
		str1 = vlq_tostring(vlq1);
		str2 = vlq_tostring(vlq2);
		stre = vlq_tostring(vlqe);
		strr = vlq_tostring(vlqr);
		strf = vlq_tostring(vlqf);
		strm = vlq_tostring(vlqm);
		ft_printf("\tstr1 = %s\n\tstr2 = %s\n\t{blue}stre = %s\n\tstrr = %s\n\t{cyan}strf = %s\n\tstrm = %s{eoc}\n\n", str1, str2, stre, strr, strf, strm);
		assert(ft_vlqcmp(vlqe, vlqr) == 0);
		assert(ft_vlqcmp(vlqf, vlqm) == 0);
	ft_vlqdelmul(6, &vlq1, &vlq2, &vlqe, &vlqr, &vlqf, &vlqm);
	ft_strdelmul(6, &str1, &str2, &stre, &strr, &strf, &strm);

//BIGNB tests
	t_bignb	bignb1;
	t_bignb	bignb2;
	t_bignb	bignbe;
	t_bignb bignbr;

ft_printf("{blue_bg}\n\nBigNb tests\n\n{eoc}");
//bignbnew, bignbdel
printf("Test %d: bignbnew, bignbdel\n\n", ++i);
	bignb1 = ft_bignbnew(0, NULL);
		assert(bignb1.vlq == NULL && bignb1.rev_ns == NULL && bignb1.base == NULL
			&& bignb1.neg == 2);
	ft_bignbdel(&bignb1);

	bignb1 = ft_bignbnew(2, BINAR);
		assert(bignb1.vlq[0] == 0 && ft_strequ(bignb1.rev_ns, "00"));
	ft_bignbdel(&bignb1);
		assert(bignb1.vlq == NULL && bignb1.rev_ns == NULL && bignb1.base == NULL
			&& bignb1.radix == 0 && bignb1.digits == 0 && bignb1.neg == 3);

//atobignb, bignb_to_str
printf("Test %d: atobignb, bignb_to_str (pos, neg)\n", ++i);
	bignb1 = ft_atobignb("36058579944795813131401201709504", DECIM);
	bignb2 = ft_atobignb("-4345686920363545489324374699", DECIM);

	str1 = ft_bignb_to_str(bignb1);
	str2 = ft_bignb_to_str(bignb2);

	ft_printf("\tstr1 = %s\n\tstr2 = %s\n\n", str1, str2);

assert(ft_strequ(str1, "36058579944795813131401201709504") && ft_strequ(str2, "-4345686920363545489324374699"));


//addition with (pos + pos), expected 36062925631716176676890526084203
	bignb2.neg = 0;
	//addition by vlq
printf("Test %d: bignb_add (pos pos)\n", ++i);
	bignbe = ft_atobignb("36062925631716176676890526084203", DECIM);
	bignbr = ft_bignb_add(bignb1, bignb2);
		stre = ft_bignb_to_str(bignbe);
		strr = ft_bignb_to_str(bignbr);
		ft_printf("\tstre = %s\n\tstrr = %s\n\n", stre, strr);
		assert(ft_vlqcmp(bignbe.vlq, bignbr.vlq) == 0);
	ft_bignbdelmul(2, &bignbe, &bignbr);
	ft_strdelmul(2, &stre, &strr);

	//addition with accumulator
printf("Test %d: bignb_add_acc (pos pos)\n", ++i);
	bignbe = ft_atobignb("36062925631716176676890526084203", DECIM);
	bignbr = ft_bignbdup(bignb1);
	ft_bignb_add_acc(&bignbr, bignb2);
	ft_bignb_vlq_updates_revns(&bignbr);
		stre = ft_bignb_to_str(bignbe);
		strr = ft_bignb_to_str(bignbr);
		ft_printf("\tstre = %s\n\tstrr = %s\n\n", stre, strr);
		assert(ft_vlqcmp(bignbe.vlq, bignbr.vlq) == 0);
	ft_bignbdelmul(2, &bignbe, &bignbr);
	ft_strdelmul(2, &stre, &strr);

	//addition by str, note that behavior is to call str_sub if signs are different
printf("Test %d: bignb_str_add (pos pos)\n", ++i);
	bignbe = ft_atobignb("36062925631716176676890526084203", DECIM);
	bignbr = ft_bignb_str_add(bignb1, bignb2);
		stre = ft_bignb_to_str(bignbe);
		strr = ft_bignb_to_str(bignbr);
		ft_printf("\tstre = %s\n\tstrr = %s\n\n", stre, strr);
		assert(ft_vlqcmp(bignbe.vlq, bignbr.vlq) == 0);
	ft_bignbdelmul(2, &bignbe, &bignbr);
	ft_strdelmul(2, &stre, &strr);


//addition with (pos + neg), expected 36054234257875449585911877334805
	bignb2.neg = 1;
	//addition by vlq
printf("Test %d: bignb_add (pos neg)\n", ++i);
	bignbe = ft_atobignb("36054234257875449585911877334805", DECIM);
	bignbr = ft_bignb_add(bignb1, bignb2);
		stre = ft_bignb_to_str(bignbe);
		strr = ft_bignb_to_str(bignbr);
		ft_printf("\tstre = %s\n\tstrr = %s\n\n", stre, strr);
		assert(ft_vlqcmp(bignbe.vlq, bignbr.vlq) == 0);
	ft_bignbdelmul(2, &bignbe, &bignbr);
	ft_strdelmul(2, &stre, &strr);

	//addition with accumulator
printf("Test %d: bignb_add_acc (pos neg)\n", ++i);
	bignbe = ft_atobignb("36054234257875449585911877334805", DECIM);
	bignbr = ft_bignbdup(bignb1);
	ft_bignb_add_acc(&bignbr, bignb2);
	ft_bignb_vlq_updates_revns(&bignbr);
		stre = ft_bignb_to_str(bignbe);
		strr = ft_bignb_to_str(bignbr);
		ft_printf("\tstre = %s\n\tstrr = %s\n\n", stre, strr);
		assert(ft_vlqcmp(bignbe.vlq, bignbr.vlq) == 0);
	ft_bignbdelmul(2, &bignbe, &bignbr);
	ft_strdelmul(2, &stre, &strr);

	//addition by str, note that behavior is to call str_sub if signs are different
printf("Test %d: bignb_str_add (pos neg)\n", ++i);
	bignbe = ft_atobignb("36054234257875449585911877334805", DECIM);
	bignbr = ft_bignb_str_add(bignb1, bignb2);
		stre = ft_bignb_to_str(bignbe);
		strr = ft_bignb_to_str(bignbr);
		ft_printf("\tstre = %s\n\tstrr = %s\n\n", stre, strr);
		assert(ft_vlqcmp(bignbe.vlq, bignbr.vlq) == 0);
	ft_bignbdelmul(2, &bignbe, &bignbr);
	ft_strdelmul(2, &stre, &strr);

//subtraction with negative number, expected 36062925631716176676890526084203
	//subtraction by vlq
printf("Test %d: bignb_sub\n", ++i);
	bignbe = ft_atobignb("36062925631716176676890526084203", DECIM);
	bignbr = ft_bignb_sub(bignb1, bignb2);
		stre = ft_bignb_to_str(bignbe);
		strr = ft_bignb_to_str(bignbr);
		ft_printf("\tstre = %s\n\tstrr = %s\n\n", stre, strr);
		assert(ft_vlqcmp(bignbe.vlq, bignbr.vlq) == 0);
	ft_bignbdelmul(2, &bignbe, &bignbr);
	ft_strdelmul(2, &stre, &strr);

	//subtraction with accumulator
printf("Test %d: bignb_sub_acc\n", ++i);
	bignbe = ft_atobignb("36062925631716176676890526084203", DECIM);
	bignbr = ft_bignbdup(bignb1);
	ft_bignb_sub_acc(&bignbr, bignb2);
	ft_bignb_vlq_updates_revns(&bignbr);
		stre = ft_bignb_to_str(bignbe);
		strr = ft_bignb_to_str(bignbr);
		ft_printf("\tstre = %s\n\tstrr = %s\n\n", stre, strr);
		assert(ft_vlqcmp(bignbe.vlq, bignbr.vlq) == 0);
	ft_bignbdelmul(2, &bignbe, &bignbr);
	ft_strdelmul(2, &stre, &strr);

	//subtraction by str, not that behavior is to fail if signs are the same, and return ABS(a - b) if signs are the same, so the result expected is different here.
printf("Test %d: bignb_str_sub\n", ++i);
	bignbe = ft_atobignb("36054234257875449585911877334805", DECIM);
	bignbr = ft_bignb_str_sub(bignb1, bignb2);
		stre = ft_bignb_to_str(bignbe);
		strr = ft_bignb_to_str(bignbr);
		ft_printf("\tstre = %s\n\tstrr = %s\n\n", stre, strr);
		assert(ft_vlqcmp(bignbe.vlq, bignbr.vlq) == 0);
	ft_bignbdelmul(2, &bignbe, &bignbr);
	ft_strdelmul(2, &stre, &strr);


//multiplication expected 156699299232982421286267321447241622119307779880214645439296

//div expected 8297


	ft_bignbdelmul(4, &bignb1, &bignb2, &bignbe, &bignbr);
	ft_strdelmul(4, &str1, &str2, &stre, &strr);
	return (0);
}
