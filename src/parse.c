/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 14:22:32 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/01 14:22:34 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_parsed_line(int fd, char ***parsed_line)
{
	char	*line;
	int		i;

	if (!get_next_line(fd, &line))
		return (0);
	i = -1;
	while (line[++i])
		if (line[i] == '\t')
			line[i] = ' ';
	*parsed_line = ft_strsplit(line, ' ');
	ft_strdel(&line);
	return (1);
}

int			get_x(char *file)
{
	int		fd;
	char	*line;
	int		lines;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("error: invalid file name");
	lines = 0;
	while (get_next_line(fd, &line) > 0)
	{
		lines++;
		ft_strdel(&line);
	}
	close(fd);
	if (lines == 0)
		error("error: empty file");
	return (lines);
}

int			get_y(char *file)
{
	int		fd;
	char	*line;
	char	**parsed_line;
	int		elems;
	int		st_elems;

	fd = open(file, O_RDONLY);
	elems = -1;
	while (get_parsed_line(fd, &parsed_line))
	{
		st_elems = elems;
		elems = -1;
		while (parsed_line[++elems])
			;
		if (elems != st_elems && st_elems != -1)
			error("error: invalid map");
		ft_arrclr(parsed_line);
	}
	if (elems == 0)
		error("error: empty file");
	return (elems);
}

void		parse(char *file, t_vector **base, int x, int y)
{
	int		i;
	int		j;
	int		fd;
	char	**parsed_line;
	char	**node;

	fd = open(file, O_RDONLY);
	i = -1;
	while (++i < x)
	{
		j = -1;
		get_parsed_line(fd, &parsed_line);
		while (++j < y)
		{
			base[i][j].x = j - y / 2;
			base[i][j].y = i - x / 2;
			node = ft_strsplit(parsed_line[j], ',');
			base[i][j].z = ft_atoi(node[0]);
			base[i][j].color = ft_atoi_base(node[1], 16);
			ft_arrclr(node);
			if (base[i][j].color == 0)
				base[i][j].color = rgb_to_color(0, 255, 0);
		}
		ft_arrclr(parsed_line);
	}
}
