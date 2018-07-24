/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 14:30:02 by osamoile          #+#    #+#             */
/*   Updated: 2018/03/27 14:30:04 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	len_words(char **a, char const *s, char c)
{
	int i;
	int count;
	int len;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		len = 0;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			len++;
		}
		a[count] = (char*)malloc(sizeof(char) * (len + 1));
		if (!a[count])
			ft_arrclr(a);
		a[count][len] = '\0';
		count++;
	}
}

static void	fill(char **a, char const *s, char c)
{
	int i;
	int count;
	int len;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		len = 0;
		while (s[i] != c && s[i] != '\0')
		{
			a[count][len] = s[i];
			i++;
			len++;
		}
		count++;
	}
}

char		**ft_strsplit(char const *s, char c)
{
	char **a;

	if (!s)
		return (0);
	a = (char**)malloc(sizeof(char*) * (ft_wordscount(s, c) + 1));
	if (!a)
		return (0);
	a[ft_wordscount(s, c)] = 0;
	len_words(a, s, c);
	fill(a, s, c);
	return (a);
}
