/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 14:15:59 by osamoile          #+#    #+#             */
/*   Updated: 2018/05/10 14:16:04 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		print_s(t_spaces spaces, t_pattern tmp, int num, int *str)
{
	int		res;
	int		i;

	res = 0;
	while (spaces.start-- > 0)
		res += ft_putchar(' ');
	while (spaces.zeroes-- > 0)
		res += ft_putchar('0');
	if (tmp.type == 'S' || tmp.cast == L)
	{
		i = -1;
		while (str[++i] && num-- > 0)
			res += ft_putchar(str[i]);
	}
	else
		res += ft_putstr((char*)str);
	while (spaces.end-- > 0)
		res += ft_putchar(' ');
	return (res);
}

static int		*precision_handler(t_pattern tmp, int *num, int *len, int *str)
{
	int		i;

	*len = 0;
	*num = 0;
	if (tmp.precision == -1)
		str = (int*)ft_strdup("");
	if ((tmp.type == 'S' || tmp.cast == L) && tmp.precision != -1)
	{
		i = -1;
		while (str[++i])
			if (*len + get_size(str[i]) <= tmp.precision || tmp.precision <= 0)
			{
				*len += get_size(str[i]);
				*num += 1;
			}
	}
	else
	{
		if (tmp.precision > 0)
			str = (int*)ft_strsub((char*)str, 0, tmp.precision);
		*len = ft_strlen((char*)str);
	}
	return (str);
}

static t_spaces	flags_handler(t_pattern tmp, int len)
{
	t_spaces	spaces;

	spaces = new_spaces();
	spaces.start = tmp.width - spaces.zeroes - len;
	if (spaces.start < 0)
		spaces.start = 0;
	if (tmp.minus == 1)
	{
		spaces.end = spaces.start;
		spaces.start = 0;
	}
	if (tmp.zero == 1)
	{
		spaces.zeroes = spaces.start;
		spaces.start = 0;
	}
	return (spaces);
}

static void		null_handler(t_pattern *tmp, int **str)
{
	if (*str == 0)
	{
		*str = (int*)"(null)";
		tmp->type = 's';
		tmp->cast = NONE;
	}
}

int				type_s(va_list argptr, t_pattern tmp)
{
	int			*str;
	t_spaces	spaces;
	int			len;
	int			num;

	str = va_arg(argptr, int*);
	null_handler(&tmp, &str);
	str = precision_handler(tmp, &num, &len, str);
	spaces = flags_handler(tmp, len);
	return (print_s(spaces, tmp, num, str));
}
