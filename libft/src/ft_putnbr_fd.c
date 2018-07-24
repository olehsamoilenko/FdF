/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 14:30:02 by osamoile          #+#    #+#             */
/*   Updated: 2018/03/27 14:30:04 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_and_put(int n, char *buf, int fd)
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
		ft_putchar_fd(buf[i], fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	char	buf[20];
	int		i;

	i = 0;
	if (n == -2147483648)
	{
		ft_putnbr_fd(-214748364, fd);
		ft_putnbr_fd(8, fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	fill_and_put(n, buf, fd);
}
