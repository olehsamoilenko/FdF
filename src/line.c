/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 18:10:38 by osamoile          #+#    #+#             */
/*   Updated: 2018/07/24 18:10:53 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		pixel_put_img(t_view *view, int x, int y, int color)
{
	if (x <= 0 || x >= WIN_WIDTH || y <= 0 || y >= WIN_HEIGHT)
		return ;
	*(int *)(view->img.img + x * view->img.bits_per_pixel + y * view->img.size_line) = 
	mlx_get_color_value(view->mlx_ptr, color);
	// printf("%d %d\n", color, mlx_get_color_value(view->mlx_ptr, color));
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
		// mlx_pixel_put(view->mlx_ptr, view->win_ptr, x0, y0, color);
		pixel_put_img(view, x0, y0, color);
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
			// mlx_pixel_put(view->mlx_ptr, view->win_ptr, x, y, color);
			pixel_put_img(view, x, y, color);
			i++;
			x += sx;
		}
	}
	else
	{
		int		d = (dx << 1) - dy;
		int		d1 = dx << 1;
		int		d2 = (dx - dy) << 1;
		// mlx_pixel_put(view->mlx_ptr, view->win_ptr, x0, y0, color);
		pixel_put_img(view, x0, y0, color);
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
			// mlx_pixel_put(view->mlx_ptr, view->win_ptr, x, y, color);
			pixel_put_img(view, x, y, color);
			i++;
			y += sy;
		}
		
		
	}
}
