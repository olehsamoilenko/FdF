/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 20:49:12 by osamoile          #+#    #+#             */
/*   Updated: 2018/03/21 20:53:23 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *big, const char *little)
{
	int		i;
	int		j;
	char	*a;

	a = (char*)big;
	if (little[0] == '\0')
		return (a);
	i = 0;
	while (big[i])
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (little[j] && little[j] == big[i + j])
			{
				if (little[j + 1] == '\0')
					return (&a[i]);
				j++;
			}
		}
		i++;
	}
	return (0);
}
