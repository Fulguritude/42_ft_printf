/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_bignb.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fulguritude <marvin@42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 05:44:23 by fulguritu         #+#    #+#             */
/*   Updated: 2018/03/20 04:23:47 by fulguritu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LIBFT_BIGNB_H
# define __LIBFT_BIGNB_H

# ifndef __LIBFT_H
#  include "libft.h"
# endif

/*

t_vlq gl_opptab[] = {{"-", &ft_sub}, \
{"+", &ft_add}, \
{"*", &ft_mul}, \
{"/", &ft_div}, \
{"%", &ft_mod}, \
{"", &ft_usage}};

as inspiration for global t
*/

/*
** TODO
** - Maybe add more checks that the first element of a vlq should be different
** from	_MSB_ ?
** - Maybe refactor NOT_MSB as OPP_MSB to avoid confusion for !NOT_MSB checks
** - Refactor bsl to bsl and bsr to bsr and inplace to acc for coherence
** - make more optimized bwa_acc and bwo_acc operators.
** - floating point arbitrary precision type, with appropriate operators.
** - Change the convention for the length of a vlq from t_u32 to t_u16 or t_u8 ?
** - optimize base conversion through a vlq_divmod function which we call with
**		radix^n where n is the largest power to which radix can be raised before
**		unsigned long overflow. It's that or Dragon4...
** - debug display and coherence checker for bignb ?
*/

# ifndef __BASES__
#  define __BASES__
#  define BINAR "01"
#  define OCTAL "01234567"
#  define DECIM "0123456789"
#  define HXLOW "0123456789abcdef"
#  define HXUPP "0123456789ABCDEF"
# endif

/*
** Variable Length Quantity (Very Long Unsigned Integer)
**
** Our VLQs are made to be used as follows:
**	- Dynamically allocated.
**	- Every number is used as its absolute (positive) value (the bignb type
**		below handles signs in its operations.
** 	- Every non-terminating t_u64 of the array starts with its MSB == 1 ;
**		the last allocated index in the array starts with its MSB == 0.
**	- The actual abstract value represented is in binary, where for each t_u64,
**		the remaining 63 bits are concatenated to represent it. LSB of the full
**		value must coincide with the LSB of the terminating t_u64. If the
**		array's LSB is 0, this is to signify a power of at least two.
**	- u64 with MSB == 0 can be recognized as t_vlq by address; behavior for
**		any t_u64 > 2^63 or negative signed longs is undefined.
**
*/

# define _MSB_ 			0x8000000000000000
# define MSB(x) 		((x) >> 63)
# define _NOT_MSB_		0x7FFFFFFFFFFFFFFF
# define NOT_MSB(x) 	((x) & _NOT_MSB_)
# define _ALLBITS_		0xFFFFFFFFFFFFFFFF

typedef t_u64*	t_vlq;
typedef t_vlq	t_vlui;

/*
** ============= VLQ functions ============
**
** Since VLQs are strictly positive, all functions work with them being so.
** is_zero is unnecessary as it suffises to check vlq[0] == 0 for well-formed
** vlqs.
*/

/*
** ~~~~~~~~~ VLQ Utils ~~~~~~~~~~
*/

/*
** Returns a u64 array of size 'size', with every leading bit set to work with
** the VLQ format. To set a value in an index, use "result[i] |= NOT_MSB(ul);"
*/
t_vlq			ft_vlqnew(t_u32 size);

/*
** Returns a newly-allocated copy of the vlq.
*/
t_vlq			ft_vlqdup(t_vlq const vlq);

/*
** Makes a VLQ from a string representing a number in a given base.
** 		- nbstr in input is to be given normal order, not rev.
** 		- leading + and - are ignored; internal + and - cause error.
*/
t_vlq			ft_atovlq(char const *nbstr, char const *base);

/*
** Returns the difference in array size or the difference within the chunk to
** function like other cmp function (ie, vlq1 < vlq2 <=> cmp(vlq1, vlq2) < 0)
*/
long			ft_vlqcmp(t_vlq const vlq1, t_vlq const vlq2);

/*
** Returns the length of a given vlq.
*/
t_u32			ft_vlqlen(t_vlq const vlq);

/*
** Returns the power to which two must be raised to obtain the leading bit of
** the actual value contained in the t_vlq.
*/
t_u32			ft_vlq_log2(t_vlq const vlq);

/*
** Returns a newly allocated vlq with a single bit set to 1 (other than the
** MSBs' 1s which allow for null-termination) at the appropriate position
** for the return value to be equal to pow(2, pow)
*/
t_vlq			ft_pow_2_to_vlq(t_u32 pow);

/*
** Returns a string in 'base' representing the value vlq.
*/
//char			*ft_vlq_to_base_revns(t_vlq const vlq, char const *base);

/*
** Counts the minimal number one must give a right shift to send vlq_p to zero,
** ignoring the format MSB.
*/
t_u8			ft_vlq_count_sigbit_of_part(t_u64 vlq_p);

/*
** Returns the number of significant bits in our whole vlq, or 0 if the vlq 
** is improperly formatted. The number 0 has 1 significant bit.
*/
t_u32			ft_vlq_count_sigbit(t_vlq vlq);

/*
** Returns a string of all the u64 in a vlq, as they are (with MSB) in 0xHXLOW.
*/
char			*ft_vlqhex(t_vlq const vlq);

/*
** Returns the vlq without its leading zeros. This version reallocates to avoid
** future problems with free on *a_vlq.
*/ 
void			ft_vlqtrim(t_vlq *a_vlq);

/*
** Checks if vlq is allocated, if so, cleans and frees memory.
*/
void			ft_vlqdel(t_vlq *a_vlq);

/*
** ~~~~~~~~~ VLQ operators ~~~~~~~~~
*/
/*
** Returns a + b.
*/
t_vlq			ft_vlq_add(t_vlq const a, t_vlq const b);

/*
** Returns ABS(a - b).
*/
t_vlq			ft_vlq_sub(t_vlq const a, t_vlq const b);

/*
** Returns a * b.
*/
t_vlq			ft_vlq_mul(t_vlq const a, t_vlq const b);

/*
** Returns a / b.
*/
t_vlq			ft_vlq_div(t_vlq const a, t_vlq const b);

/*
** Returns a / b and a % b through pointers.
*/
void			ft_vlq_divmod(t_vlq const a, t_vlq const b,
							t_vlq *div, t_vlq *mod);

/*
** Returns vlq multiplied by 2^shift.
*/
t_vlq			ft_vlq_bsl(t_vlq const vlq, t_u32 shift);

/*
** Returns vlq (euclidean) divided by 2^shift.
*/
t_vlq			ft_vlq_bsr(t_vlq const vlq, t_u32 shift);

/*
** Returns (a & b) then trims if needed.
*/
//t_vlq			ft_vlq_bwa(t_vlq const a, t_vlq const b);

/*
** Returns (a | b).
*/
//t_vlq			ft_vlq_bwo(t_vlq const a, t_vlq const b);

/*
** Uses exponentiation by squares to return a ^ exp.
*/
t_vlq			ft_vlq_pow(t_vlq const a, t_vlq exp);

/*
** Replaces 'acc' with the value a + b.
*/
void			ft_vlq_add_acc(t_vlq *acc, t_vlq const vlq);

/*
** Replaces 'acc' with the value ABS(a - b).
*/
void			ft_vlq_sub_acc(t_vlq *acc, t_vlq const vlq);

/*
** Replaces 'acc' with the value a * b.
*/
void			ft_vlq_mul_acc(t_vlq *acc, t_vlq const vlq);

/*
** Replaces 'acc' with the value a / b.
*/
void			ft_vlq_div_acc(t_vlq *acc, t_vlq const vlq);
/*
** Replaces vlq with the value "vlq multiplied by 2^shift".
*/
void			ft_vlq_bsl_acc(t_vlq *vlq, t_u32 shift);

/*
** Replaces vlq with the value "vlq (euclidian) divided by 2^shift".
*/
void			ft_vlq_bsr_acc(t_vlq *vlq, t_u32 shift);

/*
** TODO bwa bwa_acc bwo bwo_acc
*/

/*
** Big Number
**
** Our BigNb type is to be used as follows:
**		- vlq:		the absolute value of our nb, stored as a specially handled
**					array of unsigned long (t_u64) (dynamically allocated);
**		- rev_ns:	the absolute value of our nb, reversed for ease of iteration
**					(dynamically allocated);
**		- digits: 	ft_strlen(rev_ns);
**		- base:		the base rev_ns is expressed in. Operators do not check
**					for validity (statically allocated).
**		- radix:	ft_strlen(base), the number of symbols.
**		- neg:		true iff the value is considered to be negative.
**
** Call ft_bignb_to_str for conversion to human-readable.
*/

typedef struct	s_bignb
{
	t_vlq			vlq;
	char			*rev_ns;
	t_u32			digits;
	char const		*base;
	t_u8			radix;
	t_u8			neg;
}				t_bignb;

/*
** =========== BigNb Functions ==========
**
** This was made mostly for ease-of-use when formatting strings representing
** very large numbers. Behavior on base incoherence in str_op() functions is
** undefined. bn_str_op and bn_op functions update both vlq and rev_ns, unlike
** bn_op_acc functions which do not update the format string, but instead leave
** it null.
**
** NB: str_op < op < op_acc ; however, some operations will need str_op, and
**		op_acc functions need to be followed by a call to vlq_updates_revns().
**		Also note that str_op always update the vlq.
** NB: str_op functions do not check for sign.
*/
/*
** TODO verify that all bignb_ops_acc functions act on vlq rather than reallocating a full bignb with rev_ns included
** TODO check all calls to ops_acc functions to verify this convention is applied.
*/

/*
** ~~~~~~~~~ BigNb Utils ~~~~~~~~~
*/
/*
** Returns a well allocated/instantiate bignb struct. rev_ns is filled with
** '0' chars. If size == 0, a NULL string is returned for rev_ns. Else 
** (meaning size > 0), a string of size 'size' is filled with base[0].
*/
t_bignb					ft_bignbnew(t_u32 size, char const *base);

/*
** Returns a bignb from a string "a" representing a number in 'base'.
** Checks for base validity before operating. Allocates both rev_ns and vlq.
*/
t_bignb					ft_atobignb(char const *a, char const *base);

/*
** Compares the absolute value of two bignb.
*/
int						ft_bignb_strcmp(t_bignb const bn1, t_bignb const bn2);

/*
** Returns true if bn is coherently zero, false otherwise.
** This function accepts untrimmed rev_ns, but not untrimmed vlq.
*/
int						ft_bignb_iszero(t_bignb const bn);

/*
** Returns a human-readable string of the rev_ns stored in nbstr.
** TODO check for coherence first ?
*/
char					*ft_bignb_to_str(t_bignb const bn);

/*
** Uses vlq to redefine rev_ns.
** TODO many things to fix
*/
void					ft_bignb_vlq_updates_revns(t_bignb *bn);

/*
** Uses rev_ns to redefine vlq.
*/
void					ft_bignb_revns_updates_vlq(t_bignb *bn);

/*
** Alters 'rev_ns' so that it represents the same value in another 'base', with
** all fields updated adequately. Fails if ns.rev_ns contains anything other
** than a 0 or a 1.
*/
void					ft_bignb_str_bin2base_inplace(t_bignb *a_ns,
													char const *base);

/*
** Alters 'rev_ns' so that it represents its number in binary, all other fields
** change accordingly.
*/
void					ft_bignb_str_base2bin_inplace(t_bignb *a_ns);

/*
** Checks if memory is allocated, if so, cleans and frees memory.
*/
void					ft_bignbdel(t_bignb *a_bn);

/*
** ~~~~~~~~~ BigNb operators ~~~~~~~~~
*/

/*
** Returns a + b and updates all fields of said result.
*/
t_bignb					ft_bignb_add(t_bignb const a, t_bignb const b);

/*
** Returns a - b with negative output handled correctly. Updates all fields.
** Not for speedy use.
*/
t_bignb					ft_bignb_sub(t_bignb const a, t_bignb const b);

/*
** Returns a * b with negative output handled correctly. Update all fields.
** Not for speedy use.
*/
t_bignb					ft_bignb_mul(t_bignb const a, t_bignb const b);

/*
** Returns the addition of two rev_ns's stored as number strings in the same
** base. Handles any combination of positive and negative inputs. Minimal
** optimisation if largest number is given first. Updates vlq.
*/
t_bignb					ft_bignb_str_add(t_bignb const a, t_bignb const b);

/*
** Returns the subtraction of two rev_ns's stored as number strings in a same
** base b. Will return a t_bignb with empty base in case of error. Only works
** with both inputs having different signs. Returns ABS(a - b). Updates vlq.
*/
t_bignb					ft_bignb_str_sub(t_bignb const a, t_bignb const b);

/*
** Returns the multiplication of two rev_ns's written in the same 
** base b. Will return a t_bignb with empty base in case of error. Handles
** negatives. Updates vlq.
*/
t_bignb					ft_bignb_str_mul(t_bignb const a, t_bignb const b);

/*
** Returns the division of two VLQs stored as number strings in a same base b.
** Will return a t_bignb with empty base in case of error.
*/
t_bignb					ft_bignb_str_div(t_bignb const a, t_bignb const b);

/*
** Reallocates the result of nbstr_add into acc, and updates acc fields except
** for rev_ns and digits.
*/
void					ft_bignb_add_acc(t_bignb *acc, t_bignb const bn);

/*
** Reallocates the result of nbstr_sub into acc, and updates acc fields except
** for rev_ns and digits.
*/
void					ft_bignb_sub_acc(t_bignb *acc, t_bignb const bn);

/*
** Reallocates the result of nbstr_div into acc, and updates acc fields, except
** for rev_ns and digits.
*/
void					ft_bignb_mul_acc(t_bignb *acc, t_bignb const bn);

/*
** Reallocates the result of nbstr_div into acc, and updates acc fields, except
** for rev_ns and digits.
*/
void					ft_bignb_div_acc(t_bignb *acc, t_bignb const bn);

/*
** Very Long Float / Variable length float
**
** Abstract value represented = mantissa[2] * 2 ^ exp_b2[2]
**		this means exp_b2 <=> movements of floating point
**
**	- 	mantissa :	all significant digits in binary as a vlq; the point is
**					  considered to be set after the LSB of the abstract value.
**	-	exp_b2 :	the movement of the floating point; a negative value n is a
**					  bitshift right with appropriate understanding of the
**					  fractional parts in the vlf_ops(); a positive value is a
**					  bitshift left (appendding zeros);
**	-	max_prec :	how many of the digits of the binary fraction we should care
**					  for.
**	-	neg :		true if vlf < 0, false otherwise.
*/

typedef struct	s_vlf
{
	t_vlq			mantissa;
	int				exp_b2;
	t_u32			max_prec;
	t_u8			neg;
}				t_vlf;

/*
** =========== VLF Functions ==========
*/

//TODO

//div = mul by inverse ? If so, how does one compute the inverse ? Make sure to warn if infinite fraction !

#endif
