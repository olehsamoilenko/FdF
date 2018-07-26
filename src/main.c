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

int			get_color(unsigned char red, unsigned char green, unsigned char blue)
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
	view.angleX = 0; //45
	view.angleY = 0; //-45
	view.angleZ = 0; //-30
	view.zoom = 30;
	view.height = -0.05;
	return (view);
}






void		zoom(t_view *view, t_vector **coord, int zoom)
{
	int		i;
	int		j;

	if (zoom < 0)
		zoom = 0;
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

void		heigth(t_view *view, t_vector **coord)
{
	int		i;
	int		j;

	i = -1;
	while (++i < view->rows)
	{
		j = -1;
		while (++j < view->columns)
		{
			coord[i][j].z = view->base[i][j].z * view->height;
		}
	}
}



t_vector	**copy(t_view *view) // ?
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




int			main(int args, char **argv)
{
	if (args == 1)
		error("without a file");
	

	t_view	view = view_init(argv[1]);

	draw(&view);

	mlx_hook(view.win_ptr, 2, 0, &key_hook, &view); // KEYS
	mlx_hook(view.win_ptr, 17, 0, exit_func, 0); // CLOSE
	mlx_loop(view.mlx_ptr);
	

	return (0);


}
