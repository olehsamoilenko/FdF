/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_unsigned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 17:11:49 by osamoile          #+#    #+#             */
/*   Updated: 2018/05/10 17:12:04 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		print_u(t_spaces spaces, char *str)
{
	int		res;

	res = 0;
	while (spaces.start-- > 0)
		res += ft_putchar(' ');
	res += ft_putstr(spaces.prefix);
	while (spaces.zeroes-- > 0)
		res += ft_putchar('0');
	res += ft_putstr(str);
	ft_strdel(&str);
	while (spaces.end-- > 0)
		res += ft_putchar(' ');
	return (res);
}

static intmax_t	cast_u(va_list argptr, t_pattern tmp)
{
	intmax_t	nbr;

	if (tmp.cast == L || tmp.type == 'U')
		nbr = va_arg(argptr, unsigned long);
	else if (tmp.cast == H)
		nbr = (unsigned short)va_arg(argptr, unsigned int);
	else if (tmp.cast == HH)
		nbr = (unsigned char)va_arg(argptr, unsigned int);
	else if (tmp.cast == LL)
		nbr = va_arg(argptr, unsigned long long);
	else if (tmp.cast == J)
		nbr = va_arg(argptr, uintmax_t);
	else if (tmp.cast == Z)
		nbr = va_arg(argptr, size_t);
	else
		nbr = va_arg(argptr, unsigned int);
	return (nbr);
}

static t_spaces	flags_handler(t_pattern tmp, char *str)
{
	t_spaces	spaces;

	spaces = new_spaces();
	spaces.zeroes = tmp.precision - ft_strlen(str);
	if (spaces.zeroes < 0)
		spaces.zeroes = 0;
	spaces.start = tmp.width - spaces.zeroes
			- ft_strlen(str) - ft_strlen(spaces.prefix);
	if (spaces.start < 0)
		spaces.start = 0;
	if (tmp.minus == 1)
	{
		spaces.end = spaces.start;
		spaces.start = 0;
	}
	if (tmp.zero == 1 && tmp.precision == 0)
	{
		spaces.zeroes += spaces.start;
		spaces.start = 0;
	}
	return (spaces);
}

int				type_unsigned(va_list argptr, t_pattern tmp)
{
	intmax_t	nbr;
	char		*str;
	t_spaces	spaces;

	nbr = cast_u(argptr, tmp);
	if (nbr == 0 && tmp.precision == -1)
		str = ft_strdup("");
	else
		str = ft_itoa_base(nbr, 10, 1);
	spaces = flags_handler(tmp, str);
	return (print_u(spaces, str));
}
