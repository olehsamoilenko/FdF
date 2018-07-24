/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 14:30:02 by osamoile          #+#    #+#             */
/*   Updated: 2018/03/27 14:30:04 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_size(int c)
{
	if (c <= _7BITS || MB_CUR_MAX != 4)
		return (1);
	else if (c <= _11BITS)
		return (2);
	else if (c <= _16BITS)
		return (3);
	else
		return (4);
}

int		ft_putchar(int c)
{
	unsigned char	code[4];

	if (c <= _7BITS || MB_CUR_MAX != 4)
		code[0] = c;
	else if (c <= _11BITS)
	{
		code[0] = (c >> 6 & _00011111) | _11000000;
		code[1] = (c & _00111111) | _10000000;
	}
	else if (c <= _16BITS)
	{
		code[0] = (c >> 12 & _00001111) | _11100000;
		code[1] = (c >> 6 & _00111111) | _10000000;
		code[2] = (c & _00111111) | _10000000;
	}
	else
	{
		code[0] = (c >> 18 & _00000111) | _11110000;
		code[1] = (c >> 12 & _00111111) | _10000000;
		code[2] = (c >> 6 & _00111111) | _10000000;
		code[3] = (c & _00111111) | _10000000;
	}
	write(1, &code, get_size(c));
	return (get_size(c));
}
