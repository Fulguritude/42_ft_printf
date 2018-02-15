/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduquesn <tduquesn@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 15:51:47 by tduquesn          #+#    #+#             */
/*   Updated: 2018/01/05 15:52:08 by tduquesn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf_fd(int fd, const char *format, ...)
{
	va_list		args;
	int			status;

	va_start(args, format);
	status = ft_vprintf_fd(fd, format, args);
	va_end(args);
	return (status);
}

int				ft_printf(const char *format, ...)
{
	va_list		args;
	int			status;

	va_start(args, format);
	status = ft_vprintf_fd(1, format, args);
	va_end(args);
	return (status);
}

int				ft_vprintf_fd(int fd, const char *format, va_list args)
{
	char	*str;
	int		status;

	status = ft_vasprintf(&str, format, args);
	if (status >= 0)
	{
		if (write(fd, str, status) == -1)
			return (-1);
		free(str);
	}
	return (status);
}

int				ft_asprintf(char **res, const char *format, ...)
{
	va_list		args;
	int			status;

	va_start(args, format);
	status = ft_vasprintf(res, format, args);
	va_end(args);
	return (status);
}

int				ft_vasprintf(char **res, const char *format, va_list args)
{
	char	**fmt_strls;
	t_list	*res_lststr;
	int		i;
	t_str	tmp_res;

//ft_putstr("\nformat_to_strls\n");
	if (!(fmt_strls = format_to_strls(format)))
		return (-1);
//ft_putendl("fmt_strls");
//ft_putstrls((const char **)fmt_strls);
	i = -1;
	while (fmt_strls[++i])
	{
/*  //supprimer vu que printf ne considere pas cela comme une erreur vraiment 
		if (convert_str(fmt_strls[i], res_lststr, args) == -1)
		{
			ft_strlsdel(&fmt_strls);
			ft_lstdel(&res_lststr);
			return (-1);
		}
*/
ft_putstr("\n\t--Called fmt_str : \n\t++");
ft_putendl(fmt_strls[i]);
		convert_str(fmt_strls[i], &res_lststr, args);
ft_putstr("\n\t--Reslst_str : \n\t++");
ft_putendl(((t_str*)(ft_lstget(res_lststr, i)->content))->data);
	}
	tmp_res = to_single_t_str(res_lststr);
	*res = tmp_res.data;
	ft_strlsdel(&fmt_strls);
	ft_lstdel(&res_lststr, ft_delete);
	return (tmp_res.len);
}
