/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 14:30:02 by osamoile          #+#    #+#             */
/*   Updated: 2018/03/27 14:30:04 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_and_put(int n, char *buf)
{
	int i;

	i = 0;
	while (n > 0)
	{
		buf[i] = n % 10 + '0';
		n /= 10;
		i++;
	}
	while (--i >= 0)
		ft_putchar(buf[i]);
}

void		ft_putnbr(int n)
{
	char	buf[10000];
	int		i;

	i = 0;
	if (n == -2147483648)
	{
		ft_putnbr(-214748364);
		ft_putnbr(8);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr(-n);
	}
	if (n == 0)
	{
		ft_putchar('0');
		return ;
	}
	fill_and_put(n, buf);
}
