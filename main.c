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

	// float		delta;

	fd = open(file, O_RDONLY);
	// delta = (2 * win_x / 3) / (y - 1);
	// int start_x = (win_x - (y - 1) * delta) / 2; // ?
	// int start_y = (win_y - (x - 1) * delta) / 2; // ?

	int		start_x = 0;
	int		start_y = 0;

	i = -1;
	while (++i < x)
	{
		j = -1;
		get_parsed_line(fd, &parsed_line);
		while (++j < y)
		{
			base.x = j;
			base.y = i;
			base.z = ft_atoi(parsed_line[j]);

			// base.y -= base.z * 5; // !!!

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
	int		win_x = 1500;
	int		win_y = 800;
	t_view	view;

	view.rows = get_x(file);
	view.coord = (t_vector**)ft_memalloc(sizeof(t_vector*) * view.rows);
	view.columns = get_y(file);
	i = -1;
	while (++i < view.rows)
		view.coord[i] = (t_vector*)ft_memalloc(sizeof(t_vector) * view.columns);
	read_coord(file, view.coord, view.rows, view.columns);
	view.mlx_ptr = mlx_init();
	view.win_ptr = mlx_new_window(view.mlx_ptr, win_x, win_y, "FdF");
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

void		print_lines(t_view *view)
{
	int		i;
	int		j;

	i = -1;
	while (++i < view->rows)
	{
		j = -1;
		while (++j < view->columns)
		{
			if (i < view->rows - 1)
			{
				// printf("(%d,%d) -> (%d,%d)\n", i, j, i+1, j);
				line(view, (int)view->coord[i][j].x, (int)view->coord[i][j].y, (int)view->coord[i + 1][j].x, (int)view->coord[i + 1][j].y, color(255, 0, 0));

			}
			if (j < view->columns - 1)
			{
				// printf("(%d,%d) -> (%d,%d)\n", i, j, i, j+1);
				line(view, (int)view->coord[i][j].x, (int)view->coord[i][j].y, (int)view->coord[i][j + 1].x, (int)view->coord[i][j + 1].y, color(255, 0, 0));
			}
			
			// mlx_pixel_put(mlx_ptr, win_ptr, coord[i][j].x, coord[i][j].y, color(255, 0, 0));
		}
	}
}

void		zoom(t_view *view, float zoom)
{
	int		i;
	int		j;

	i = -1;
	while (++i < view->rows)
	{
		j = -1;
		while (++j < view->columns)
		{
			view->coord[i][j].x *= zoom;
			view->coord[i][j].y *= zoom;
		}
	}
}

void		heigth(t_view *view, float delta)
{
	int		i;
	int		j;

	i = -1;
	while (++i < view->rows)
	{
		j = -1;
		while (++j < view->columns)
		{
			view->coord[i][j].z *= delta;
		}
	}
}

void		rotate(t_view *view, int direction, float angle)
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
				view->coord[i][j].y = view->coord[i][j].y * cos(angle) + view->coord[i][j].z * sin(angle);
				view->coord[i][j].z = view->coord[i][j].z * cos(angle) - view->coord[i][j].y * sin(angle);
			}
			if (direction == Y_AXIS)
			{
				view->coord[i][j].x = view->coord[i][j].x * cos(angle) - view->coord[i][j].z * sin(angle);
				view->coord[i][j].z = view->coord[i][j].z * cos(angle) + view->coord[i][j].x * sin(angle);
			}
			if (direction == Z_AXIS)
			{
				view->coord[i][j].x = view->coord[i][j].x * cos(angle) + view->coord[i][j].y * sin(angle);
				view->coord[i][j].y = view->coord[i][j].y * cos(angle) - view->coord[i][j].x * sin(angle);
			}
		}
	}
}

void		translate(t_view *view, int direction, int len)
{
	int		i;
	int		j;

	i = -1;
	while (++i < view->rows)
	{
		j = -1;
		while (++j < view->columns)
		{
			if (direction == X_AXIS)
				view->coord[i][j].x += len;
			if (direction == Y_AXIS)
				view->coord[i][j].y += len;
		}
	}
}

int		key_hook(int key, t_view *view)
{
	if (key == ESC)
		exit(1);
	else if (key == LEFT)
		rotate(view, Y_AXIS, 10);
	else if (key == RIGHT)
		rotate(view, Y_AXIS, -10);
	else if (key == UP)
		rotate(view, X_AXIS, 10);
	else if (key == DOWN)
		rotate(view, X_AXIS, -10);
	else if (key == PLUS)
		mlx_clear_window(view->mlx_ptr, view->win_ptr);
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

	// float	heigth = -1/5;

	heigth(&view, -0.2);
	printf("(%f,%f,%f)\n", view.coord[3][3].x, view.coord[3][3].y, view.coord[3][3].z);
	rotate(&view, X_AXIS, 40);
	rotate(&view, Y_AXIS, -40);
	rotate(&view, Z_AXIS, -30);
	printf("(%f,%f,%f)\n", view.coord[3][3].x, view.coord[3][3].y, view.coord[3][3].z);

	
	// rotate(&view, Y_AXIS, 40);
	
	zoom(&view, 30);
	
	
	translate(&view, X_AXIS, 400);
	translate(&view, Y_AXIS, 300);

	// show coordinats
	int i;
	int j;
	i = -1;
	while (++i < view.rows)
	{
		j = -1;
		while (++j < view.columns)
			printf("(%d,%d) x: %f y: %f z: %f\n", i, j, view.coord[i][j].x, view.coord[i][j].y, view.coord[i][j].z);
	}
	// show coordinats


	// line(&view, 100, 0, 0, 100);
	print_lines(&view);
	mlx_hook(view.win_ptr, 2, 0, &key_hook, 0); // KEYS
	mlx_hook(view.win_ptr, 17, 0, exit_func, 0); // CLOSE
	mlx_loop(view.mlx_ptr);
	

	return (0);


}
