/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recognise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:30:58 by osamoile          #+#    #+#             */
/*   Updated: 2018/06/05 16:30:59 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_spaces	new_spaces(void)
{
	t_spaces tmp;

	tmp.start = 0;
	tmp.end = 0;
	tmp.zeroes = 0;
	tmp.prefix = 0;
	return (tmp);
}

t_pattern	new_value(void)
{
	t_pattern tmp;

	tmp.hash = 0;
	tmp.minus = 0;
	tmp.plus = 0;
	tmp.space = 0;
	tmp.zero = 0;
	tmp.width = 0;
	tmp.precision = 0;
	tmp.cast = NONE;
	tmp.type = 0;
	return (tmp);
}

int			is_type(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' ||
		c == 'D' || c == 'i' || c == 'o' || c == 'O' ||
		c == 'u' || c == 'U' || c == 'x' || c == 'X' ||
		c == 'c' || c == 'C')
		return (1);
	else
		return (0);
}

int			is_cast(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	else
		return (0);
}

int			is_flag(char c)
{
	if (c == '#' || c == '-' || c == '+' || c == '0' || c == ' ')
		return (1);
	else
		return (0);
}
