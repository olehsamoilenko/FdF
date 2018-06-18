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

typedef			struct s_coord
{
	// int		name_x;
	// int		name_y;

	int	x;
	int	y;
	int	z;
}				t_coord;

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

void		line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1)
{
	// ft_putstr("I'm in!\n");
	/* y = kx + b */
	float	k;
	float	b;

	if (x1 - x0 != 0)
		k = (float)(y1 - y0) / (float)(x1 - x0);
	else
		k = 0;
	b = y0 - k * x0;

	// printf("y = %fx + %f\n", k, b);

	if (x0 == x1)
		while (y0++ < y1)
			mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, color(255, 0, 0));
	if (y0 == y1)
		while (x0++ < x1)
			mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, color(255, 0, 0));

	int		y = y0;
	int		y_prev;
	while (x0++ < x1)
	{
		y_prev = y;
		y = k * x0 + b;
		mlx_pixel_put(mlx_ptr, win_ptr, x0, y, color(255, 0, 0));
		// printf("(%d,%d)\n", x0, (int)(k * x0 + b));
		while (y - y_prev++ > 1)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x0, y_prev, color(255, 0, 0));
			// printf("dop: (%d,%d)\n", x0, y_prev);
		}
	}
}

void		print_dots(void *mlx_ptr, void *win_ptr, t_coord **coord, int x, int y, int win_x, int win_y)
{
	int		i;
	int		j;

	i = -1;
	while (++i < x)
	{
		j = -1;
		while (++j < y)
		{
			if (j < y - 1)
				line(mlx_ptr, win_ptr, coord[i][j].x, coord[i][j].y, coord[i][j + 1].x, coord[i][j + 1].y);
			if (i < x - 1)
				line(mlx_ptr, win_ptr, coord[i][j].x, coord[i][j].y, coord[i + 1][j].x, coord[i + 1][j].y);
			mlx_pixel_put(mlx_ptr, win_ptr, coord[i][j].x, coord[i][j].y, color(255, 0, 0));
		}
	}
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

void		base_points(char *file, t_coord **p, int x, int y, int win_x, int win_y)
{
	int		i;
	int		j;
	t_coord	base;
	int		fd;
	char	**parsed_line;

	float		delta;

	fd = open(file, O_RDONLY);
	delta = (2 * win_x / 3) / (y - 1);
	int start_x = (win_x - (y - 1) * delta) / 2; // ?
	int start_y = (win_y - (x - 1) * delta) / 2; // ?

	i = -1;
	while (++i < x)
	{
		j = -1;
		// get_next_line(fd, &line);
		get_parsed_line(fd, &parsed_line);
		while (++j < y)
		{
			base.x = start_y + delta * j;
			base.y = start_x + delta * i;
			base.z = ft_atoi(parsed_line[j]);

			// base.y -= base.z * 5; // !!!

			p[i][j] = base;
		}
	}
}



int		key_hook(int key, void *param)
{
	param = 0;
	if (key == ESC)
		exit(1);
	// else if (key == UP)
	// 	translate()
	return (0);
}

int exit_x(void)
{
	exit(1);
}

void		rotate(t_coord **coord, int x, int y, int direction, double angle)
{
	int		i;
	int		j;

	i = -1;
	while (++i < x)
	{
		j = -1;
		while (++j < y)
		{
			if (direction == X)
			{
				coord[i][j].y = coord[i][j].y * cos(angle) - coord[i][j].z * sin(angle);
				coord[i][j].z = coord[i][j].y * sin(angle) + coord[i][j].z * cos(angle);
			}
			if (direction == Y)
			{
				coord[i][j].x = coord[i][j].x * cos(angle) - coord[i][j].y * sin(angle);
				coord[i][j].y = coord[i][j].x * sin(angle) + coord[i][j].y * cos(angle);
			}
			if (direction == Z)
			{
				coord[i][j].z = coord[i][j].z * cos(angle) - coord[i][j].x * sin(angle);
				coord[i][j].x = coord[i][j].z * sin(angle) + coord[i][j].x * cos(angle);
				// coord[i][j].x += 600;
			}
			// coord[i][j].x += 500;
			// coord[i][j].y += 500;
			// coord[i][j].y -= 900;
			// printf("(%d,%d) x: %d y: %d z: %d\n", i, j, coord[i][j].x, coord[i][j].y, coord[i][j].z);
		}
	}
}

void		convert(t_coord **coord, int x, int y)
{
	int		i;
	int		j;
	int		d = 10;

	i = -1;
	while (++i < x)
	{
		j = -1;
		while (++j < y)
		{
			coord[i][j].x = coord[i][j].x * d / (coord[i][j].z + d);
			coord[i][j].y = coord[i][j].y * d / (coord[i][j].z + d);
			printf("(%d,%d) x: %d y: %d z: %d\n", i, j, coord[i][j].x, coord[i][j].y, coord[i][j].z);
		}
	}
}

void		translate(t_coord **coord, int x, int y, int tr_x, int tr_y)
{
	int		i;
	int		j;

	i = -1;
	while (++i < x)
	{
		j = -1;
		while (++j < y)
		{
			coord[i][j].x += tr_x;
			coord[i][j].y += tr_y;
			// printf("(%d,%d) x: %d y: %d z: %d\n", i, j, coord[i][j].x, coord[i][j].y, coord[i][j].z);
		}
	}
}

int			main(int args, char **argv)
{
	int		i;
	int		j;
	int		x;
	int		y;

	int		win_x = 2500;
	int		win_y = 1300;

	t_coord **coord;

	if (args == 1)
		error("without a file");
	x = get_x(argv[1]);
	coord = (t_coord**)ft_memalloc(sizeof(t_coord*) * x);
	y = get_y(argv[1]);
	i = -1;
	while (++i < x)
		coord[i] = (t_coord*)ft_memalloc(sizeof(t_coord) * y);
	base_points(argv[1], coord, x, y, win_x, win_y);

	i = -1;
	while (++i < x)
	{
		j = -1;
		while (++j < y)
		{
			// coord[i][j].y -= coord[i][j].z * 5;
			printf("(%d,%d) x: %d y: %d z: %d\n", i, j, coord[i][j].x, coord[i][j].y, coord[i][j].z);
		}
	}

	

	void	*mlx_ptr = mlx_init();
	void	*win_ptr = mlx_new_window(mlx_ptr, win_x, win_y, "FdF");

	// coord[8][16].x = 200;
	// coord[8][16].y = 200;
	
	// rotate(coord, x, y, Y, 0.2);
	convert(coord, x, y);
	translate(coord, x, y, 100, 100);

	print_dots(mlx_ptr, win_ptr, coord, x, y, win_x, win_y);
	// printf("(%d %d %d)\n", coord[8][16].x, coord[8][16].y, coord[8][16].z);
	
	// printf("(%d %d %d)\n", coord[8][16].x, coord[8][16].y, coord[8][16].z);

	


	ft_putstr("FUCK!\n");

	// mlx_pixel_put(mlx_ptr, win_ptr, 1, 1, color(250, 0, 0));
	// mlx_pixel_put(mlx_ptr, win_ptr, 100, 34, color(250, 0, 0));
	// line(mlx_ptr, win_ptr, 200, 200, 300, 300);
	mlx_hook(win_ptr, 2, 0, &key_hook, 0);
	mlx_hook(win_ptr, 17, 0, exit_x, 0);
	// mlx_key_hook(win_ptr, &key_hook, 0);
	mlx_loop(mlx_ptr);
	

	

	return (0);


}
