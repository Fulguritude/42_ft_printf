#include "ft_printf.h"


//TODO remove
#include <stdio.h>

void		del_t_str(void *content, size_t content_size)
{
	t_str	*tstr;

	if (content)
	{
		tstr = (t_str*)content;
		ft_strdel(&(tstr->data));
		ft_delete(content, content_size);
	}
}

t_str		*str_to_t_str(char const *str)
{
	t_str	*result;

	if (!str || !(result = (t_str*)malloc(sizeof(t_str))))
		return (NULL);
	result->data = ft_strdup(str);
	result->len = ft_strlen(str);
//printf("str_to_t_str : %s, %s\n", str, result.data);
	return (result);
}

static void	t_str_append(void *s1, void *s2)
{
	int		len;
	char	*tmp;
	t_str	*acc;
	t_str	*next;

	if (!s1 || !s2)
		return ;
	acc = (t_str*)s1;
	next = (t_str*)s2;
	len = acc->len + next->len;
	tmp = ft_strnew(len);
	ft_memcpy(tmp, acc->data, acc->len);
	ft_memcpy(tmp + acc->len, next->data, next->len);
	free(acc->data);
	acc->len = len;
	acc->data = tmp;
}

t_str		to_single_t_str(t_list *lststr)
{
	t_str	acc;

//	if (!(acc = (t_str*)malloc(sizeof(t_str))))
//		return (NULL);
	acc.data = ft_strnew(0);
	acc.len = 0;
	ft_lstfold(lststr, &acc, &t_str_append);
	return (acc);
}
