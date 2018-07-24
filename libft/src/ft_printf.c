/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 14:05:44 by osamoile          #+#    #+#             */
/*   Updated: 2018/05/01 14:05:48 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print(va_list argptr, t_pattern tmp)
{
	if (tmp.type == 's' || tmp.type == 'S')
		return (type_s(argptr, tmp));
	else if (tmp.type == 'c' || tmp.type == 'C')
		return (type_c(argptr, tmp));
	else if (tmp.type == 'd' || tmp.type == 'i' || tmp.type == 'D')
		return (type_integer(argptr, tmp));
	else if (tmp.type == 'u' || tmp.type == 'U')
		return (type_unsigned(argptr, tmp));
	else if (tmp.type == 'o' || tmp.type == 'O')
		return (type_o(argptr, tmp));
	else if (tmp.type == 'x' || tmp.type == 'X' || tmp.type == 'p')
		return (type_hex(argptr, tmp));
	else
		return (0);
}

int	type_flag(char cur, t_pattern tmp, int *sum, va_list argptr)
{
	int		stop;

	stop = 0;
	if (is_type(cur))
	{
		tmp.type = cur;
		*sum += print(argptr, tmp);
		stop = 1;
	}
	if (!is_flag(cur) && !ft_isdigit(cur) &&
		!is_cast(cur) && !is_type(cur) && cur != '.' && cur != '\0')
	{
		*sum += print_c(cur, tmp);
		stop = 1;
	}
	return (stop);
}

int	ft_printf(const char *format, ...)
{
	va_list		argptr;
	int			i;
	t_pattern	tmp;
	int			sum;

	va_start(argptr, format);
	i = -1;
	sum = 0;
	while (format[++i])
		if (format[i] == '%')
		{
			tmp = new_value();
			i++;
			while (!type_flag(format[i], tmp, &sum, argptr))
			{
				flags_width_prec_cast(format, &i, &tmp);
				if (format[i] == '\0')
					return (sum);
			}
		}
		else
			sum += ft_putchar(format[i]);
	return (sum);
}
