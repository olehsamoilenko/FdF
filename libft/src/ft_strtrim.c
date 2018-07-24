/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 14:30:02 by osamoile          #+#    #+#             */
/*   Updated: 2018/03/27 14:30:04 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isseparator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

char		*ft_strtrim(char const *s)
{
	int		i;
	int		first;
	int		last;
	char	*a;

	first = -1;
	last = -1;
	i = -1;
	if (!s)
		return (0);
	while (s[++i])
	{
		if (!isseparator(s[i]) && first == -1)
			first = i;
		if (!isseparator(s[i]))
			last = i;
	}
	a = (char*)malloc(sizeof(char) * (last - first + 2));
	if (!a)
		return (0);
	i = first - 1;
	while (++i <= last)
		a[i - first] = s[i];
	a[i - first] = '\0';
	return (a);
}
