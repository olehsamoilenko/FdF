/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 08:24:14 by osamoile          #+#    #+#             */
/*   Updated: 2018/03/28 08:24:49 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*lst;

	lst = (t_list*)malloc(sizeof(t_list));
	if (!lst)
		return (0);
	lst->content_size = content_size;
	if (content != 0)
	{
		lst->content = ft_strdup(content);
		if (!lst->content)
		{
			free(lst);
			return (0);
		}
		ft_strcpy(lst->content, content);
	}
	else
	{
		lst->content = 0;
		lst->content_size = 0;
	}
	lst->next = 0;
	return (lst);
}
