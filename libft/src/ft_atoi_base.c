/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 09:51:44 by osamoile          #+#    #+#             */
/*   Updated: 2018/07/26 09:51:46 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		convert(char c, int base)
{
	int		res;

	res = 0;
	if (c >= '0' && c <= '9')
		res = c - '0';
	else if (c >= 'A' && c <= 'F')
		res = c - 'A' + 10;
	else if (c >= 'a' && c <= 'f')
		res = c - 'a' + 10;
	if (res >= base)
		res = 0;
	return (res);
}

int		power(int nb, int power)
{
	int		res;

	res = 1;
	while (power-- > 0)
		res *= nb;
	return (res);
}

int		ft_atoi_base(char *nb, int base)
{
	int		len;
	int		position;
	int		res;

	len = ft_strlen(nb);
	position = 0;
	res = 0;
	while (len-- > 0)
		res += convert(nb[len], base) * power(base, position++);
	return (res);
}
