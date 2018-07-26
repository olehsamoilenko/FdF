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
	if (c <= BIN("01111111") || MB_CUR_MAX != 4)
		return (1);
	else if (c <= BIN("0000011111111111"))
		return (2);
	else if (c <= BIN("1111111111111111"))
		return (3);
	else
		return (4);
}

int		ft_putchar(int c)
{
	unsigned char	code[4];

	if (c <= BIN("01111111") || MB_CUR_MAX != 4)
		code[0] = c;
	else if (c <= BIN("0000011111111111"))
	{
		code[0] = (c >> 6 & BIN("00011111")) | BIN("11000000");
		code[1] = (c & BIN("00111111")) | BIN("10000000");
	}
	else if (c <= BIN("1111111111111111"))
	{
		code[0] = (c >> 12 & BIN("00001111")) | BIN("11100000");
		code[1] = (c >> 6 & BIN("00111111")) | BIN("10000000");
		code[2] = (c & BIN("00111111")) | BIN("10000000");
	}
	else
	{
		code[0] = (c >> 18 & BIN("00000111")) | BIN("11110000");
		code[1] = (c >> 12 & BIN("00111111")) | BIN("10000000");
		code[2] = (c >> 6 & BIN("00111111")) | BIN("10000000");
		code[3] = (c & BIN("00111111")) | BIN("10000000");
	}
	write(1, &code, get_size(c));
	return (get_size(c));
}
