/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 08:24:14 by osamoile          #+#    #+#             */
/*   Updated: 2018/03/28 08:24:49 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*buf;

	if (!lst || !f)
		return (0);
	new = f(ft_lstnew(lst->content, lst->content_size));
	buf = new;
	lst = lst->next;
	while (lst)
	{
		new->next = f(ft_lstnew(lst->content, lst->content_size));
		lst = lst->next;
		new = new->next;
	}
	new->next = 0;
	return (buf);
}
