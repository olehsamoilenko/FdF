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

	float	x;
	float	y;
	float	z;
}				t_coord;

int			color(unsigned char red, unsigned char green, unsigned char blue)
{
	int		color;

	color = red * MIN_RED + green * MIN_GREEN + blue;
	// printf("%d\n", color);
	return (color);
}

int			deal_key(int key, void *param)
{
	write (1, &"X", 1);
	return (0);
}

char			***create_array(char *file)
{
	int		fd;

	char	*line;
	char	**parsed_line;
	char	***res;

	int		i;
	int		count;
	int		points;
	int		lines;

	fd = open(file, O_RDONLY);
	lines = 0;
	while (get_next_line(fd, &line))
		lines++;
	res = ft_memalloc(sizeof(char**) * (lines + 1));
	res[lines] = 0;
	close(fd);
	fd = open(file, O_RDONLY);
	points = -1;
	lines = 0;
	while (get_next_line(fd, &line))
	{
		i = -1;
		while (line[++i])
			if (line[i] == '\t')
				line[i] = ' ';
		parsed_line = ft_strsplit(line, ' ');
		i = -1;
		count = 0;
		while (parsed_line[++i])
			count++;
		if (count != points && points != -1)
		{
			ft_putstr("error: invalid map\n");
			return (0);
		}
		else
			points = count;
		res[lines++] = parsed_line;

	}
	close(fd);
	return (res);
}

void		print_dots(t_coord **coord, int x, int y, int win_x, int win_y)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		i;
	int		j;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, win_x, win_y, "mlx!!!");
	i = -1;
	while (++i < x)
	{
		j = -1;
		while (++j < y)
			mlx_pixel_put(mlx_ptr, win_ptr, coord[i][j].x, coord[i][j].y, color(100, 100, 0));
	}
	// mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
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

int			get_y(char *file)
{
	int		fd;
	char	*line;
	char	**parsed_line;
	int		i;
	int		elems;

	fd = open(file, O_RDONLY);
	get_next_line(fd, &line);
	i = -1;
	while (line[++i])
		if (line[i] == '\t')
			line[i] = ' ';
	parsed_line = ft_strsplit(line, ' ');
	elems = 0;
	i = -1;
	while (parsed_line[++i])
		elems++;
	return (elems);
}

void		base_points(t_coord **p, int x, int y, int win_x, int win_y)
{
	int		i;
	int		j;
	t_coord	base;

	float		delta;

	delta = (2 * win_x / 3) / (y - 1);
	// delta = 10;

	int start_x = win_x / 6;
	int start_y = win_y / 6;

	i = -1;
	while (++i < x)
	{
		j = -1;
		while (++j < y)
		{
			base.x = start_y + delta * j;
			base.y = start_x + delta * i;
			p[i][j] = base;
		}
	}
}

void		line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1)
{
	int		dx = abs(x0 - x1);
	int		dy = abs(y0 - y1);

	float	error = 0;
	float	dError = dy;

	int		x = x0;
	int		y = y0;
	int		diry = y1 - y0;

	if (dy > 0)
		diry = 1;
	if (dy < 0)
		diry = -1;
	while (x++ < x1)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x, y, color(100, 100, 0));
		error = error + dError;
		if (2 * error >= dx)
			y = y + diry;
		error = error - dy;
	}

}

int			main(int args, char **argv)
{
	int		i;
	int		j;
	int		x;
	int		y;

	int		win_x = 700;
	int		win_y = 500;

	t_coord **coord;

	if (args == 1)
	{
		ft_putstr("error: without a file\n");
		return (0);
	}

	// x = get_x(argv[1]);
	// coord = (t_coord**)ft_memalloc(sizeof(t_coord*) * x);
	// y = get_y(argv[1]);
	// i = -1;
	// while (++i < x)
	// 	coord[i] = (t_coord*)ft_memalloc(sizeof(t_coord) * y);
	// base_points(coord, x, y, win_x, win_y);
	// i = -1;
	// while (++i < x)
	// {
	// 	j = -1;
	// 	while (++j < y)
	// 		printf("(%d,%d) x: %f y: %f z: %f\n", i, j, coord[i][j].x, coord[i][j].y, coord[i][j].z);
	// }
	// print_dots(coord, x, y, win_x, win_y);

	void	*mlx_ptr = mlx_init();
	void	*win_ptr = mlx_new_window(mlx_ptr, win_x, win_y, "mlx!!!");

	mlx_pixel_put(mlx_ptr, win_ptr, 10, 10, color(250, 0, 0));
	mlx_pixel_put(mlx_ptr, win_ptr, 200, 300, color(250, 0, 0));
	line(mlx_ptr, win_ptr, 10, 10, 200, 300);

	mlx_loop(mlx_ptr);
	

	

	return (0);


}
