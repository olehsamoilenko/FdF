/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 14:34:25 by osamoile          #+#    #+#             */
/*   Updated: 2018/08/01 14:34:27 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	circle(t_view *view, t_vector center, int radius)
{
	int		x;
	int		y;
	int		delta;
	int		error;

	x = 0;
	y = radius;
	delta = 1 - 2 * radius;
	error = 0;
	while (y >= 0)
	{
		pixel_put_img(view, center.x + x, center.y + y, center.color);
		pixel_put_img(view, center.x + x, center.y - y, center.color);
		pixel_put_img(view, center.x - x, center.y + y, center.color);
		pixel_put_img(view, center.x - x, center.y - y, center.color);
		error = 2 * (delta + y) - 1;
		if ((delta < 0) && (error <= 0))
			delta += 2 * ++x + 1;
		else if ((delta > 0) && (error > 0))
			delta -= 2 * --y + 1;
		else
			delta += 2 * (++x - y--);
	}
}

void		frame_labels(t_view *view)
{
	char	*s;

	s = "FdF";
	mlx_string_put(view->mlx_ptr, view->win_ptr,
		(WIN_WIDTH - ft_strlen(s) * ALPHA_WIDTH) / 2,
		LABEL_SIZE / 2 + ALPHA_HEIGHT / 2, rgb_to_color(255, 255, 255), s);
	s = "osamoile";
	mlx_string_put(view->mlx_ptr, view->win_ptr,
		(WIN_WIDTH - ft_strlen(s) * ALPHA_WIDTH) / 2,
		WIN_HEIGHT - LABEL_SIZE / 2 + ALPHA_HEIGHT / 2, rgb_to_color(255, 255, 255), s);
}

void		frame(t_view *view)
{
	int		i;
	int		j;

	i = -1;
	while (++i < LABEL_SIZE)
	{
		j = -1;
		while (++j < WIN_WIDTH)
		{
			pixel_put_img(view, j, i, rgb_to_color(100, 0, 0));
			pixel_put_img(view, j, WIN_HEIGHT - i, rgb_to_color(100, 0, 0));
		}
	}
	j = -1;
	while (++j < WIN_WIDTH)
	{
		pixel_put_img(view, j, i, rgb_to_color(255, 255, 255));
		pixel_put_img(view, j, WIN_HEIGHT - i, rgb_to_color(255, 255, 255));
	}
}

void		help(t_view *view)
{
	mlx_string_put(view->mlx_ptr, view->win_ptr, 50, 100,
		rgb_to_color(255, 255, 255), "ZOOM     : + -");
	mlx_string_put(view->mlx_ptr, view->win_ptr, 50, 120,
		rgb_to_color(255, 255, 255), "MOVE     : W A S D");
	mlx_string_put(view->mlx_ptr, view->win_ptr, 50, 140,
		rgb_to_color(255, 255, 255), "RELIEF   : PAGE UP / DOWN");
	mlx_string_put(view->mlx_ptr, view->win_ptr, WIN_WIDTH - HELP_MARGIN, 100,
		rgb_to_color(255, 255, 255), "ROTATE X : ARROW UP / DOWN");
	mlx_string_put(view->mlx_ptr, view->win_ptr, WIN_WIDTH - HELP_MARGIN, 120,
		rgb_to_color(255, 255, 255), "ROTATE Y : ARROW LEFT / RIGHT");
	mlx_string_put(view->mlx_ptr, view->win_ptr, WIN_WIDTH - HELP_MARGIN, 140,
		rgb_to_color(255, 255, 255), "ROTATE Z : 1 2");
	mlx_string_put(view->mlx_ptr, view->win_ptr, WIN_WIDTH - HELP_MARGIN, 580,
		rgb_to_color(255, 255, 255), "RESET    : BACKSPACE");
	mlx_string_put(view->mlx_ptr, view->win_ptr, WIN_WIDTH - HELP_MARGIN, 600,
		rgb_to_color(255, 255, 255), "EXIT     : ESC");
	mlx_string_put(view->mlx_ptr, view->win_ptr, 50, 600,
		rgb_to_color(255, 255, 255), "HELP     : H");
}

void		intro(t_view *view)
{
	t_vector	center;
	char		*s;

	center.x = WIN_WIDTH / 2;
	center.y = WIN_HEIGHT / 2;
	center.color = rgb_to_color(100, 0, 0);
	circle(view, center, 200);
	frame(view);
	mlx_put_image_to_window(view->mlx_ptr, view->win_ptr,
		view->img.img_ptr, 0, 0);
	s = "PRESS ANY KEY";
	mlx_string_put(view->mlx_ptr, view->win_ptr,
		(WIN_WIDTH - ft_strlen(s) * ALPHA_WIDTH) / 2,
		(WIN_HEIGHT - ALPHA_HEIGHT) / 2, rgb_to_color(255, 255, 255), s);
	frame_labels(view);
}
