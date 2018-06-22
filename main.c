/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 17:26:19 by osamoile          #+#    #+#             */
/*   Updated: 2018/06/11 17:26:58 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> //trash
#define MIN_GREEN 256
#define MIN_RED 65536

int			color(unsigned char red, unsigned char green, unsigned char blue)
{
	int		color;

	color = red * MIN_RED + green * MIN_GREEN + blue;
	// printf("%d\n", color);
	return (color);
}

void		error(char *message)
{
	ft_putstr("error: ");
	ft_putendl(message);
	exit(0);
}

int			get_x(char *file)
{
	int		fd;
	char	*line;
	int		lines;

	fd = open(file, O_RDONLY);
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

void		read_coord(char *file, t_vector **p, int x, int y)
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


int			exit_func(void)
{
	exit(1);
}

t_view		view_init(char *file)
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
	read_coord(file, view.base, view.rows, view.columns);
	view.mlx_ptr = mlx_init();
	view.win_ptr = mlx_new_window(view.mlx_ptr, WIDTH, HEIGHT, "FdF");
	view.angleX = 40;
	view.angleY = -40;
	view.angleZ = -30;
	view.zoom = 30;
	view.height = -0.2;
	return (view);
}


void		line(t_view *view, int x0, int y0, int x1, int y1, int color)
{
	int		dx = abs(x1 - x0);
	int		dy = abs(y1 - y0);
	int		sx = x1 >= x0 ? 1 : -1;
	int		sy = y1 >= y0 ? 1 : -1;

	if (dy <= dx)
	{
		int		d = (dy << 1) - dx;
		int		d1 = dy << 1;
		int		d2 = (dy - dx) << 1;
		mlx_pixel_put(view->mlx_ptr, view->win_ptr, x0, y0, color);
		int		x = x0 + sx;
		int		i = 1;
		int		y = y0;
		while (i <= dx)
		{
			if (d > 0)
			{
				d += d2;
				y += sy;
			}
			else
				d += d1;
			mlx_pixel_put(view->mlx_ptr, view->win_ptr, x, y, color);
			i++;
			x += sx;
		}
	}
	else
	{
		int		d = (dx << 1) - dy;
		int		d1 = dx << 1;
		int		d2 = (dx - dy) << 1;
		mlx_pixel_put(view->mlx_ptr, view->win_ptr, x0, y0, color);
		int		y = y0 + sy;
		int		i = 1;
		int		x = x0;
		while (i <= dy)
		{
			if (d > 0)
			{
				d += d2;
				x += sx;
			}
			else
				d += d1;
			mlx_pixel_put(view->mlx_ptr, view->win_ptr, x, y, color);
			i++;
			y += sy;
		}
		
		
	}
}



void		zoom(t_view *view, t_vector **coord, float zoom)
{
	int		i;
	int		j;

	i = -1;
	while (++i < view->rows)
	{
		j = -1;
		while (++j < view->columns)
		{
			coord[i][j].x *= zoom;
			coord[i][j].y *= zoom;
		}
	}
}

void		heigth(t_view *view, t_vector **coord, float height)
{
	int		i;
	int		j;

	i = -1;
	while (++i < view->rows)
	{
		j = -1;
		while (++j < view->columns)
		{
			coord[i][j].z *= height;
		}
	}
}

void		rotate(t_view *view, t_vector **coord, int direction, float angle)
{
	int		i;
	int		j;

	i = -1;
	angle = angle * M_PI / 180;
	while (++i < view->rows)
	{
		j = -1;
		while (++j < view->columns)
		{
			if (direction == X_AXIS)
			{
				coord[i][j].y = coord[i][j].y * cos(angle) + coord[i][j].z * sin(angle);
				coord[i][j].z = coord[i][j].z * cos(angle) - coord[i][j].y * sin(angle);
			}
			if (direction == Y_AXIS)
			{
				coord[i][j].x = coord[i][j].x * cos(angle) - coord[i][j].z * sin(angle);
				coord[i][j].z = coord[i][j].z * cos(angle) + coord[i][j].x * sin(angle);
			}
			if (direction == Z_AXIS)
			{
				coord[i][j].x = coord[i][j].x * cos(angle) + coord[i][j].y * sin(angle);
				coord[i][j].y = coord[i][j].y * cos(angle) - coord[i][j].x * sin(angle);
			}
		}
	}
}

t_vector	**copy(t_view *view)
{
	int			i;
	int			j;
	t_vector	**coord;

	coord = (t_vector**)ft_memalloc(sizeof(t_vector*) * view->rows);
	i = -1;
	while (++i < view->rows)
	{
		
		coord[i] = (t_vector*)ft_memalloc(sizeof(t_vector) * view->columns);
		j = -1;
		while (++j < view->columns)
			coord[i][j] = view->base[i][j];
	}
	return (coord);
}

void		print_lines(t_view *view)
{
	int		i;
	int		j;

	t_vector	**new_coord;


	new_coord = copy(view);

	// printf("base: (%f, %f)\n", view->base[3][3].x, view->base[3][3].y);
	// printf("new: (%f, %f)\n", new_coord[3][3].x, new_coord[3][3].y);
	heigth(view, new_coord, view->height);
	rotate(view, new_coord, X_AXIS, view->angleX);
	rotate(view, new_coord, Y_AXIS, view->angleY);
	rotate(view, new_coord, Z_AXIS, view->angleZ);
	zoom(view, new_coord, view->zoom);

	// printf("base: (%f, %f)\n", view->base[3][3].x, view->base[3][3].y);
	// printf("new: (%f, %f)\n", new_coord[3][3].x, new_coord[3][3].y);

	i = -1;
	while (++i < view->rows)
	{
		j = -1;
		while (++j < view->columns)
		{
			if (i < view->rows - 1)
				line(view, (int)new_coord[i][j].x + WIDTH / 2, (int)new_coord[i][j].y + HEIGHT / 2,
							(int)new_coord[i + 1][j].x + WIDTH / 2, (int)new_coord[i + 1][j].y + HEIGHT / 2,
							color(255, 0, 0));
			if (j < view->columns - 1)
				line(view, (int)new_coord[i][j].x + WIDTH / 2, (int)new_coord[i][j].y + HEIGHT / 2,
							(int)new_coord[i][j + 1].x + WIDTH / 2, (int)new_coord[i][j + 1].y + HEIGHT / 2,
							color(255, 0, 0));
		}
	}
}

// void		translate(t_view *view, int direction, int len)
// {
// 	int		i;
// 	int		j;

// 	i = -1;
// 	while (++i < view->rows)
// 	{
// 		j = -1;
// 		while (++j < view->columns)
// 		{
// 			if (direction == X_AXIS)
// 				view->coord[i][j].x += len;
// 			if (direction == Y_AXIS)
// 				view->coord[i][j].y += len;
// 		}
// 	}
// }

int		key_hook(int key, void *v)
{
	t_view		*view;
	

	view = (t_view*)v;
	if (key == ESC)
		exit(1);
	else if (key == LEFT)
		view->angleY += 5;
	else if (key == RIGHT)
		view->angleY -= 5;
	else if (key == UP)
		view->angleX -= 5;
	else if (key == DOWN)
		view->angleX += 5;
	else if (key == PLUS)
		view->zoom += 1;
	else if (key == MINUS)
		view->zoom -= 1;
	else if (key == W)
		view->height -= 0.1;
	else if (key == S)
		view->height += 0.1;
	
	
	
	// // show coordinats
	// int i;
	// int j;
	// i = -1;
	// while (++i < view->rows)
	// {
	// 	j = -1;
	// 	while (++j < view->columns)
	// 		printf("(%d,%d) x: %f y: %f z: %f\n", i, j, view->base[i][j].x, view->base[i][j].y, view->base[i][j].z);
	// }
	// // show coordinats
	mlx_clear_window(view->mlx_ptr, view->win_ptr);


	print_lines(view);

	// else if (key == MINUS)
	// 	zoom(info->coord, info->x, info->y, 1/10);

	// mlx_destroy_window(view->mlx_ptr, view->win_ptr);
	
	// print_lines(view);
	// print_dots(mlx_ptr, win_ptr, coord, x, y);
	return (0);
}

int			main(int args, char **argv)
{
	if (args == 1)
		error("without a file");
	

	t_view	view = view_init(argv[1]);


	// heigth(&view, -0.2);
	// rotate(&view, X_AXIS, 40);
	// rotate(&view, Y_AXIS, -40);
	// rotate(&view, Z_AXIS, -30);
	// zoom(&view, 30);
	// translate(&view, X_AXIS, 400);
	// translate(&view, Y_AXIS, 300);



	print_lines(&view);

	mlx_hook(view.win_ptr, 2, 0, &key_hook, &view); // KEYS
	mlx_hook(view.win_ptr, 17, 0, exit_func, 0); // CLOSE
	mlx_loop(view.mlx_ptr);
	

	return (0);


}
