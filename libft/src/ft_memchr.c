/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 20:49:12 by osamoile          #+#    #+#             */
/*   Updated: 2018/03/21 20:53:23 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*a;
	size_t	i;

	a = (char*)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)a[i] == (unsigned char)c)
			return (&a[i]);
		i++;
	}
	return (0);
}
