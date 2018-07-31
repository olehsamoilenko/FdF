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

# define RED 0
# define GREEN 1
# define BLUE 2


void		pixel_put_img(t_view *view, int x, int y, int color)
{
	if (x <= 0 || x >= WIN_WIDTH || y <= 0 || y >= WIN_HEIGHT)
		return ;
	*(int *)(view->img.img + x * view->img.bits_per_pixel + y * view->img.size_line) = 
	mlx_get_color_value(view->mlx_ptr, color);
	// printf("%d %d\n", color, mlx_get_color_value(view->mlx_ptr, color));
}

// int			get_color(int color, int base_color)
// {
// 	// 

// 	if (base_color == RED)
// 		return (color >> 16 & 0xFF);
// 	else if (base_color == GREEN)
// 		return (color >> 8 & 0xFF);
// 	else if (base_color == BLUE)
// 		return (color & 0xFF);
// 	else
// 		return (0);
// }

float		percent(int middle, int left, int right)
{
	if (right == left)
		return (0);
	return ((float)(middle - left) / (right - left));
}

int			grad_color(int color1, int color2, float percent)
{
	int		red;
	int		green;
	int		blue;

	// red = get_color(color1, RED) + percent * (get_color(color2, RED) - get_color(color1, RED));
	// green = get_color(color1, GREEN) + percent * (get_color(color2, GREEN) - get_color(color1, GREEN));
	// blue = get_color(color1, BLUE) + percent * (get_color(color2, BLUE) - get_color(color1, BLUE));

	red = (color1 >> 16 & 0xFF) + percent * ((color2 >> 16 & 0xFF) - (color1 >> 16 & 0xFF));
	green = (color1 >> 8 & 0xFF) + percent * ((color2 >> 8 & 0xFF) - (color1 >> 8 & 0xFF));
	blue = (color1 & 0xFF) + percent * ((color2 & 0xFF) - (color1 & 0xFF));
	return (red << 16 | green << 8 | blue);
}

void		line(t_view *view, int x0, int y0, int color0, int x1, int y1, int color1)
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
		int		x = x0 + sx;
		pixel_put_img(view, x0, y0, grad_color(color0, color1, percent(x, x0, x1)));
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
			pixel_put_img(view, x, y, grad_color(color0, color1, percent(x, x0, x1)));
			i++;
			x += sx;
		}
	}
	else
	{
		int		d = (dx << 1) - dy;
		int		d1 = dx << 1;
		int		d2 = (dx - dy) << 1;
		int		y = y0 + sy;
		pixel_put_img(view, x0, y0, grad_color(color0, color1, percent(y, y0, y1)));
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
			pixel_put_img(view, x, y, grad_color(color0, color1, percent(y, y0, y1)));
			i++;
			y += sy;
		}
		
		
	}
}
