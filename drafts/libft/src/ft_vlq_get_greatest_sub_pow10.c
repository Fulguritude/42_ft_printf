/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlq_get_greatest_sub_pow10.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:37:24 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/23 15:37:37 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


/*

En gros: 
tu fais ton uitoa en commençant par le most significant digit. Comment faire pour un bigint ? Tu trouves la puissance de 10 juste en dessous.

Le procédé c'est en gros ça:
log2(nb) = exp_base_2
log10(nb) = exp_base_10
(tain je galère avec mes log sans la notation mathématique xd - note aussi que "base" c'est au sens de "base" d'une exponentielle ou d'un logarithme, pas de "base numérique")
on a nb * 2^eb2 = nb * 10^eb10 ssi 2^eb2 = 10^eb10
donc eb10 = eb2 * ln(2) / ln(10)

Disons qu'on tombe sur eb10 = 225.54343......
Il y a 226 digits en base 10 pour notre nombre.
Soit tu fais 225 multiplications de vlq pour trouver ta puissance de 10 juste en dessous.
Soit t'es malin, tu remarques que 10^225 = 10^(128 + 64 + 32 + 1) = 10^128 * 10^64 * 10^32 * 10
Et tu gardes en déjà calculé tes vlq contenant 10 ^ pow_of_2 jusqu'à la limite des float représentables (ici, 10^330 si je me souviens bien, donc on que besoin de 10^256 et les sous-puissances de 2)
et la tu réduis un algorithme de taille 0(n) en 0(log2(n))
C'est assez brillant xd
Sachant que le 'n' ici c'est le nombre de multiplications sur des vlq, donc ça coûte piquant



Precalculated stuff, source WolframAlpha:

10 ^ 256
1010101001111110111010111111101110011101111110011101111010001101110111011011
1011100100000001101110011000111111101110101010110111100001010001111001001100
1011111100111101111000101111100110001010101011100111100000001100011111111110
1010100000011100011110001000010110100110101101000011101000101010011011000100
1001010110111000110011001101011000000100110101100100111000101101110110101011
0010101110110000000111111001111010010100110111001110000011010111101111001010
0001100011000010010000101010010111110000111110110001101100110011111011100101
0111110110100111000011101011011100110000010111001111100000000010000000000000
0000000000000000000000000000000000000000000000000000000000000000000000000000
0000000000000000000000000000000000000000000000000000000000000000000000000000
0000000000000000000000000000000000000000000000000000000000000000000000000000
000000000000000

10 ^ 128
1001001110111010010001111100100110000000111010011000110011011111110001100110
1111001100110110110000110110101100010000000100110111000000100011010011110011
1111110101111011000010001101110100111001000010111100001111000101010011100011
1111010000001111011111100110010000100100101110100101010011111000000001000000
0000000000000000000000000000000000000000000000000000000000000000000000000000
0000000000000000000000000000000000000000000000
10 ^ 64
1100001001111000000111110100100111111111110011111010011011010101001111001011
1111011010110111000111000111011010110010010111111011010100001111100000001000
0000000000000000000000000000000000000000000000000000000000000
10^32
1001110111000101101011011010100000101011011100001011010110011101111100000010
0000000000000000000000000000000
10^16
100011100001101111001001101111110000010000000000000000


ln(2)/ln(10) in binary (approximate)
0.01 (MSB, so exp2 = -2[10])
0011 0100 0100 => 344
0001 0011 0101 => 135
0000 1001 1111 => 09F
0111 1001 1111 => 79F
1110		   => E
=> 0x1.34413509F79FEp-2

*/
static t_vlq	get_large_pow10(int pow)
{
	static t_u64	pow10_16[1] = {0x002386f26fc10000};
	static t_u64	pow10_32[2] = {0x800009dc5ada82b7, 0x05acef8100000000};
	static t_u64	pow10_64[4]	= {0x8000000000c2781f, 0xa4ffe7d36a9e5fb5,
									0xdc71dac97ed43e02, 0x0000000000000000};
	static t_u64	pow10_128[7] = {0x800093ba47c980e9, 0xc66fe33799b61b58,
									0xc04dc08d3cff5ec2, 0x9ba7217878a9c7e8,
									0x8f7e6424ba54f804, 0x8000000000000000,
									0x0000000000000000};
	static t_u64	pow10_256[14] = {0x80000000aa7eebfb, 0xcefcef46eeddc80d,
									0xe63fbaade147932f, 0xe7bc5f3155cf018f,
 									0xfea81c7885a6b43a, 0x953624adc666b026,
									0xd938b76acaec07e7, 0xd29b9c1af7943184,
									0xc2a5f0fb1b33ee57, 0xed3875b982e7c010,
									0x8000000000000000, 0x8000000000000000,
									0x8000000000000000, 0x0000000000000000};

	if (pow == 16)
		return (pow10_16);
	if (pow == 32)
		return (pow10_32);
	if (pow == 64)
		return (pow10_64);
	if (pow == 128)
		return (pow10_128);
	if (pow == 256)
		return (pow10_256);
	return (NULL);
}

/*
** 10^225 = 10^(128 + 64 + 32 + 1) = 10^128 * 10^64 * 10^32 * 10
** Just keep every radix^pow_of_2 where 0 <= pow_of_2 < log_radix(vlq) and 
** find the exponent to decompose it cleverly.
*/
static t_vlq	get_pow10(t_u32 exp10)
{
	t_vlq	result;
	t_u8	sub15_exp;

	if (exp10 >= 0x200)
	{
		ft_putendl_fd("Exp10 >= 512 in vlq_get_greatest_sub_pow10 subcall", 2);
		return (NULL);
	}
	sub15_exp = exp10 & 0xF;
	result = ft_vlqnew(1);
	result[0] = ft_ipowi(10, sub15_exp);
	if (exp10 & 0x10)
		ft_vlq_mul_acc(&result, get_large_pow10(16));
	if (exp10 & 0x20)
		ft_vlq_mul_acc(&result, get_large_pow10(32));
	if (exp10 & 0x40)
		ft_vlq_mul_acc(&result, get_large_pow10(64));
	if (exp10 & 0x80)
		ft_vlq_mul_acc(&result, get_large_pow10(128));
	if (exp10 & 0x100)
		ft_vlq_mul_acc(&result, get_large_pow10(256));
	return (result);
}

/*
** Note that exp10 is the exponent if scientific decimal notation is used;
**			 exp2  is the exponent if scientific binary  notation is used;
** 		=> Both represent "their number's corresponding number of digits - 1".
*/
t_vlq		ft_vlq_get_greatest_sub_pow10(t_vlq vlq)
{
	double			ln2_by_ln10;
	t_u32			exp2;
	t_u32			exp10;

	if (vlq[0] < 10)
		return (0);
	ln2_by_ln10 = 0x1.34413509F79FEp-2;
	exp2 = ft_vlq_count_sigbit(vlq) - 1;
	exp10 = ft_floor(ln2_by_ln10 * exp2);
	return (get_pow10(exp10));
}
