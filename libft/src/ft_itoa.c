/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 14:30:02 by osamoile          #+#    #+#             */
/*   Updated: 2018/03/27 14:30:04 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		fill(intmax_t number, char *a, int len)
{
	if (number == 0)
		a[0] = '0';
	a[len--] = '\0';
	while (number > 0)
	{
		a[len] = number % 10 + '0';
		number /= 10;
		len--;
	}
}

char			*ft_itoa(intmax_t number)
{
	char	*a;
	int		sign;
	int		len;

	sign = 0;
	if (number < -9223372036854775807)
		return (ft_strdup("-9223372036854775808"));
	if (number < 0)
	{
		number *= -1;
		sign = 1;
	}
	len = ft_countdigits(number);
	a = ft_strnew(len + sign);
	if (!a)
		return (0);
	if (sign == 1)
	{
		a[0] = '-';
		len++;
	}
	fill(number, a, len);
	return (a);
}
