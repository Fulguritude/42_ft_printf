#include "ft_printf.h"

t_str	*str_to_t_str(char *str)
{
	t_str	*result;

	if (!str || !(result = (t_str*)malloc(sizeof(t_str))))
		return (NULL);
	result->data = ft_strdup(str);
	result->len = ft_strlen(str);
}

static void	t_str_append(t_str *acc, t_str *next)
{
	int		len;
	char	*tmp;

	len = acc->len + next->len;
	tmp = ft_strnew(len);
	ft_memcpy(tmp, acc->data, acc->len);
	ft_memcpy(tmp + acc->len, next->data, next->len);
	free(acc->data);
	acc->len = len;
	acc->data = tmp;
}

t_str	to_single_t_str(t_list *lststr)
{
	t_str	acc;

	acc.data = ft_strnew(0);
	acc.len = 0;
	ft_lstfold(lststr, &acc, &t_str_append);
	return (acc);
}
