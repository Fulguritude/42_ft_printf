#include "libft.h"

/*
** Returns 2^pow as a vlq.
*/
t_vlq			ft_pow_2_to_vlq(t_u32 pow)
{
	t_vlq		result;
	t_u32		arr_size;
	t_u8		bit_pos;
	t_u32		i;

	arr_size = (pow / 63) + 1;
	bit_pos = pow % 63;
	result = ft_vlqnew(arr_size);
	result[0] = (arr_size > 1 ? _MSB_ : 0) | (0x1 << bit_pos); 
	i = 1;
	while (i < arr_size - 1)
	{
		result[i] = _MSB_;
		++i;
	}
	result[i] &= _MSB_;
	return (result);	
}

