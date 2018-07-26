/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 10:23:21 by osamoile          #+#    #+#             */
/*   Updated: 2018/07/26 10:23:23 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			get_x(char *file)
{
	int		fd;
	char	*line;
	int		lines;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("invalid file name");
	lines = 0;
	while (get_next_line(fd, &line))
		lines++;
	close(fd);
	return (lines);
}

int			get_parsed_line(int fd, char ***parsed_line)
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
	return (1);
}

int			get_y(char *file)
{
	int		fd;
	char	*line;
	char	**parsed_line;
	int		i;
	int		elems;
	int		st_elems;

	fd = open(file, O_RDONLY);
	elems = -1;
	while (get_parsed_line(fd, &parsed_line))
	{
		i = -1;
		st_elems = elems;
		elems = 0;
		while (parsed_line[++i])
			elems++;
		if (elems != st_elems && st_elems != -1)
			error("invalid map");
	}
	return (elems);
}

void		parse(char *file, t_vector **p, int x, int y)
{
	int		i;
	int		j;
	t_vector	base;
	int		fd;
	char	**parsed_line;

	fd = open(file, O_RDONLY);

	i = -1;
	while (++i < x)
	{
		j = -1;
		get_parsed_line(fd, &parsed_line);
		while (++j < y)
		{
			base.x = j - y / 2;
			base.y = i - x / 2;
			base.z = ft_atoi(parsed_line[j]);
			p[i][j] = base;
		}
	}
}

t_view		init(char *file)
{
	int		i;
	int		j;
	t_view	view;

	view.rows = get_x(file);
	view.base = (t_vector**)ft_memalloc(sizeof(t_vector*) * view.rows);
	view.columns = get_y(file);
	i = -1;
	while (++i < view.rows)
		view.base[i] = (t_vector*)ft_memalloc(sizeof(t_vector) * view.columns);
	parse(file, view.base, view.rows, view.columns);
	view.mlx_ptr = mlx_init();
	view.win_ptr = mlx_new_window(view.mlx_ptr, WIDTH, HEIGHT, "FdF");
	view.angleX = 0; //45
	view.angleY = 0; //-45
	view.angleZ = 0; //-30
	view.zoom = 30;
	view.height = -0.05;
	return (view);
}