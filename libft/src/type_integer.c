/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_integer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 11:21:07 by osamoile          #+#    #+#             */
/*   Updated: 2018/05/04 11:21:10 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static intmax_t	cast_int(t_pattern tmp, va_list argptr)
{
	intmax_t	nbr;

	if (tmp.cast == L || tmp.type == 'D')
		nbr = va_arg(argptr, long);
	else if (tmp.cast == H)
		nbr = (short)va_arg(argptr, int);
	else if (tmp.cast == HH)
		nbr = (char)va_arg(argptr, int);
	else if (tmp.cast == LL)
		nbr = va_arg(argptr, long long);
	else if (tmp.cast == J)
		nbr = va_arg(argptr, intmax_t);
	else if (tmp.cast == Z)
		nbr = va_arg(argptr, size_t);
	else
		nbr = va_arg(argptr, int);
	return (nbr);
}

static int		print_int(t_spaces spaces, char *str)
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

static void		handle_flags(t_spaces *sp, t_pattern tmp,
					intmax_t nbr, char *str)
{
	sp->zeroes = tmp.precision - ft_strlen(str);
	sp->zeroes < 0 ? sp->zeroes = 0 : 0;
	sp->start = tmp.width - sp->zeroes
			- ft_strlen(str) - ft_strlen(sp->prefix);
	sp->start < 0 ? sp->start = 0 : 0;
	if (tmp.plus == 1 && nbr >= 0)
	{
		sp->prefix = "+";
		sp->start -= ft_strlen(sp->prefix);
	}
	if (tmp.space == 1 && nbr >= 0 && sp->prefix == 0)
	{
		sp->prefix = " ";
		sp->start -= ft_strlen(sp->prefix);
	}
	if (tmp.minus == 1)
	{
		sp->end = sp->start;
		sp->start = 0;
	}
	if (tmp.zero == 1 && tmp.precision == 0)
	{
		sp->zeroes += sp->start;
		sp->start = 0;
	}
}

int				type_integer(va_list argptr, t_pattern tmp)
{
	intmax_t	nbr;
	char		*str;
	t_spaces	spaces;
	char		*buf;

	nbr = cast_int(tmp, argptr);
	spaces = new_spaces();
	if (nbr == 0 && tmp.precision == -1)
		str = ft_strdup("");
	else
		str = ft_itoa(nbr);
	if (nbr < 0)
	{
		spaces.prefix = "-";
		buf = str;
		str = ft_strsub(str, 1, ft_strlen(str) - 1);
		ft_strdel(&buf);
	}
	handle_flags(&spaces, tmp, nbr, str);
	return (print_int(spaces, str));
}
