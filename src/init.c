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
	while (get_next_line(fd, &line))
	{
		lines++;
		ft_strdel(&line);
	}
	close(fd);
	return (lines);
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
			error("error: invalid map");
		ft_arrclr(parsed_line);
	}
	return (elems);
}

void		parse(char *file, t_vector **base, int x, int y)
{
	int		i;
	int		j;
	// t_vector	base;
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
			// base[i][j] = base;
			if (base[i][j].color == 0)
				base[i][j].color = get_color(0, 200, 0);
		}
		ft_arrclr(parsed_line);
	}
}

void		init_img(t_view *view)
{
	
	view->img.img_ptr = mlx_new_image(view->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	
	view->img.img = mlx_get_data_addr(view->img.img_ptr, &view->img.bits_per_pixel, &view->img.size_line, &view->img.endian);
	view->img.bits_per_pixel /= 8;

	// view->img = img;
	// mlx_put_image_to_window(view->mlx_ptr, view->win_ptr, view->img->img_ptr, 0, 0);

	
	// printf("img: %s ptr: %s\n", view->img->img, view->img->img_ptr);

}

t_vector	**create_map(int rows, int columns)
{
	int			i;
	t_vector	**base;

	base = (t_vector**)ft_memalloc(sizeof(t_vector*) * rows);
	i = -1;
	while (++i < rows)
		base[i] = (t_vector*)ft_memalloc(sizeof(t_vector) * columns);
	return (base);
}

void	default_settings(t_view *view)
{
	view->angleX = 0; //45
	view->angleY = 0; //-45
	view->angleZ = 0; //-30
	view->zoom = 1;
	view->height = -0.1;
	// view->translateX = WIN_WIDTH / 2;
	// view->translateY = WIN_HEIGHT / 2;
	view->moveX = 0;
	view->moveY = 0;
}



t_view		init(char *file)
{
	int		i;
	int		j;
	t_view	view;
	// t_img	img;

	view.rows = get_x(file);
	view.columns = get_y(file);
	view.base = create_map(view.rows, view.columns);
	parse(file, view.base, view.rows, view.columns);
	view.modified = create_map(view.rows, view.columns);

	view.mlx_ptr = mlx_init();
	view.win_ptr = mlx_new_window(view.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");

	default_settings(&view);

	init_img(&view);
	// view.img = &img;

	return (view);
}
