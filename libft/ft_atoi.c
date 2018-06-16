/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 19:24:26 by osamoile          #+#    #+#             */
/*   Updated: 2018/03/21 19:26:21 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define MAX 922337203685477580

int			ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	res;

	sign = 1;
	res = 0;
	i = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		if (sign == 1 && (res > MAX || (res == MAX && str[i] > '7')))
			return (-1);
		if (sign == -1 && (res > MAX || (res == MAX && str[i] > '8')))
			return (0);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (sign * (int)res);
}
