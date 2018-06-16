/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 20:49:12 by osamoile          #+#    #+#             */
/*   Updated: 2018/03/21 20:53:23 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = 0;
	while (dst[len1])
		len1++;
	len2 = 0;
	while (src[len2])
		len2++;
	i = 0;
	if (size >= len1)
	{
		while (i < size - len1 - 1 && size - len1 > 0)
		{
			if (!src[i])
				break ;
			dst[len1 + i] = src[i];
			i++;
		}
		dst[len1 + i] = '\0';
		return (len1 + len2);
	}
	else
		return (size + len2);
}
