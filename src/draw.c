/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 18:14:00 by osamoile          #+#    #+#             */
/*   Updated: 2018/07/24 18:14:16 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		pixel_put_img(t_view *view, int x, int y, int color)
{
	if (x <= 0 || x >= WIN_WIDTH || y <= 0 || y >= WIN_HEIGHT)
		return ;
	*(int *)(view->img.img + x * view->img.bits_per_pixel +
		y * view->img.size_line) = mlx_get_color_value(view->mlx_ptr, color);
}

int			rgb_to_color(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16 | g << 8 | b);
}

static void	copy(t_vector **from, t_vector **where, int rows, int columns)
{
	int			i;
	int			j;

	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (++j < columns)
			where[i][j] = from[i][j];
	}
}

void		draw(t_view *view)
{
	int		i;
	int		j;

	copy(view->base, view->mod, view->rows, view->columns);
	transformation(view);
	i = -1;
	while (++i < view->rows)
	{
		j = -1;
		while (++j < view->columns)
		{
			if (i < view->rows - 1)
				line(view, view->mod[i][j], view->mod[i + 1][j]);
			if (j < view->columns - 1)
				line(view, view->mod[i][j], view->mod[i][j + 1]);
		}
	}
	frame(view);
	mlx_put_image_to_window(view->mlx_ptr, view->win_ptr,
		view->img.img_ptr, 0, 0);
	frame_labels(view);
	if (view->help)
		help(view);
}
