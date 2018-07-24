/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 14:30:02 by osamoile          #+#    #+#             */
/*   Updated: 2018/03/27 14:30:04 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*a;

	if (!s)
		return (0);
	a = ft_strnew(len);
	if (!a)
		return (0);
	i = 0;
	while (i < len)
	{
		a[i] = s[i + start];
		i++;
	}
	a[i] = '\0';
	return (a);
}
