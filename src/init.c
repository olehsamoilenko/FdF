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

static void		init_img(t_view *view)
{
	view->img.img_ptr = mlx_new_image(view->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	view->img.img = mlx_get_data_addr(view->img.img_ptr,
		&view->img.bits_per_pixel, &view->img.size_line, &view->img.endian);
	view->img.bits_per_pixel /= 8;
}

static t_vector	**create_map(int rows, int columns)
{
	int			i;
	t_vector	**base;

	base = (t_vector**)ft_memalloc(sizeof(t_vector*) * rows);
	i = -1;
	while (++i < rows)
		base[i] = (t_vector*)ft_memalloc(sizeof(t_vector) * columns);
	return (base);
}

void			default_settings(t_view *view)
{
	view->angle_x = -50;
	view->angle_y = 0;
	view->angle_z = 40;
	view->zoom = WIN_WIDTH / (2 * view->columns);
	view->height = -0.1;
	view->move_x = 0;
	view->move_y = 0;
	view->help = 1;
}

t_view			init(char *file)
{
	t_view	view;

	view.rows = get_x(file);
	view.columns = get_y(file);
	view.base = create_map(view.rows, view.columns);
	parse(file, view.base, view.rows, view.columns);
	view.mod = create_map(view.rows, view.columns);
	view.mlx_ptr = mlx_init();
	view.win_ptr = mlx_new_window(view.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "FdF");
	default_settings(&view);
	init_img(&view);
	return (view);
}
