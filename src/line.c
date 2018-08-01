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

static float	percent(int middle, int left, int right)
{
	if (right == left)
		return (0);
	return ((float)(middle - left) / (right - left));
}

static int		grad_color(int color1, int color2, float percent)
{
	int		red;
	int		green;
	int		blue;

	red = (color1 >> 16 & 0xFF) +
		percent * ((color2 >> 16 & 0xFF) - (color1 >> 16 & 0xFF));
	green = (color1 >> 8 & 0xFF) +
		percent * ((color2 >> 8 & 0xFF) - (color1 >> 8 & 0xFF));
	blue = (color1 & 0xFF) +
		percent * ((color2 & 0xFF) - (color1 & 0xFF));
	return (rgb_to_color(red, green, blue));
}

static void		line_x(t_view *view, t_vector dot1, t_vector dot2,
	t_bresenham br)
{
	int		x;
	int		i;
	int		y;

	x = dot1.x + br.sx;
	i = 0;
	y = dot1.y;
	br.d = 2 * br.dy - br.dx;
	br.d1 = 2 * br.dy;
	br.d2 = 2 * (br.dy - br.dx);
	pixel_put_img(view, dot1.x, dot1.y, grad_color(dot1.color, dot2.color,
		percent(x, dot1.x, dot2.x)));
	while (++i <= br.dx)
	{
		if (br.d > 0)
		{
			br.d += br.d2;
			y += br.sy;
		}
		else
			br.d += br.d1;
		pixel_put_img(view, x, y, grad_color(dot1.color, dot2.color,
			percent(x, dot1.x, dot2.x)));
		x += br.sx;
	}
}

static void		line_y(t_view *view, t_vector dot1, t_vector dot2,
	t_bresenham br)
{
	int		y;
	int		i;
	int		x;

	y = dot1.y + br.sy;
	i = 0;
	x = dot1.x;
	br.d = 2 * br.dx - br.dy;
	br.d1 = 2 * br.dx;
	br.d2 = 2 * (br.dx - br.dy);
	pixel_put_img(view, dot1.x, dot1.y, grad_color(dot1.color, dot2.color,
		percent(y, dot1.y, dot2.y)));
	while (++i <= br.dy)
	{
		if (br.d > 0)
		{
			br.d += br.d2;
			x += br.sx;
		}
		else
			br.d += br.d1;
		pixel_put_img(view, x, y, grad_color(dot1.color, dot2.color,
			percent(y, dot1.y, dot2.y)));
		y += br.sy;
	}
}

void			line(t_view *view, t_vector dot1, t_vector dot2)
{
	t_bresenham	br;

	br.dx = abs((int)dot2.x - (int)dot1.x);
	br.dy = abs((int)dot2.y - (int)dot1.y);
	br.sx = dot2.x >= dot1.x ? 1 : -1;
	br.sy = dot2.y >= dot1.y ? 1 : -1;
	if (br.dy <= br.dx)
		line_x(view, dot1, dot2, br);
	else
		line_y(view, dot1, dot2, br);
}
