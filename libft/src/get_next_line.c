/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 16:19:24 by osamoile          #+#    #+#             */
/*   Updated: 2018/04/12 16:19:26 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*find_elem(t_list **lst, int fd)
{
	t_list	*tmp;
	char	*s;

	if (*lst == 0)
	{
		s = ft_strdup("");
		*lst = ft_lstnew(s, fd);
		ft_strdel(&s);
		return (*lst);
	}
	tmp = *lst;
	while (tmp->next)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if ((int)tmp->content_size == fd)
		return (tmp);
	s = ft_strdup("");
	tmp->next = ft_lstnew(s, fd);
	ft_strdel(&s);
	return (tmp->next);
}

static void		cut_line(char **line, char **content)
{
	char	*tmp;

	*line = ft_strsub(*content, 0, ft_strchr(*content, '\n') - *content);
	tmp = *content;
	*content = ft_strsub(*content, ft_strchr(*content, '\n') - *content + 1,
		ft_strlen(*content) - (ft_strchr(*content, '\n') - *content) - 1);
	ft_strdel(&tmp);
}

static void		add_to_buf(char **content, char *buf)
{
	char	*tmp;

	tmp = *content;
	*content = ft_strjoin(*content, buf);
	ft_strdel(&tmp);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*lst;
	t_list			*elem;
	char			buf[BUFF_SIZE + 1];

	elem = find_elem(&lst, fd);
	if (fd < 0 || read(fd, buf, 0) == -1 || BUFF_SIZE <= 0)
		return (-1);
	while (!ft_strchr(elem->content, '\n'))
	{
		ft_bzero(buf, BUFF_SIZE + 1);
		read(fd, buf, BUFF_SIZE);
		if (ft_strequ(buf, "") == 1 && ft_strequ(elem->content, "") == 1)
			return (0);
		if (ft_strequ(buf, "") == 1)
		{
			*line = ft_strdup(elem->content);
			ft_strclr(elem->content);
			return (1);
		}
		add_to_buf((char**)&elem->content, buf);
	}
	cut_line(line, (char**)&elem->content);
	return (1);
}
