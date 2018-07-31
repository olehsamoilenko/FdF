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

// #define MIN_GREEN 256
// #define MIN_RED 65536



void		error(char *message)
{
	// ft_putstr("error: ");
	ft_putendl(message);
	exit(0);
}




int			exit_func(void)
{
	// delete_coord(view->base);
	// delete_coord(view, view->base);
	exit(1);
}

void		circle(t_view *view, int x0, int y0, int radius, int color)
{
	int		x;
	int		y;

	// int		r2 = radius * radius;
	// i = -radius - 1;
	// while (++i <= radius)
	// {
	// 	j = (int)(sqrt(r2 - i * i) + 0.5);
	// 	pixel_put_img(view, x0 + i, y0 + j, color);
	// 	pixel_put_img(view, x0 + i, y0 - j, color);
	// }

	// int		r2 = radius * radius;
	// pixel_put_img(view, x0, y0 + radius, color);
	// pixel_put_img(view, x0, y0 - radius, color);
	// i = 0;
	// while (++i <= radius)
	// {
	// 	j = (int)(sqrt(r2 - i * i) + 0.5);
	// 	pixel_put_img(view, x0 + i, y0 + j, color);
	// 	pixel_put_img(view, x0 + i, y0 - j, color);
	// 	pixel_put_img(view, x0 - i, y0 + j, color);
	// 	pixel_put_img(view, x0 - i, y0 - j, color);
	// }

	
	x = 0;
	y = radius;
	int delta = 1 - 2 * radius;
	int error = 0;
	while (y >= 0)
	{
		pixel_put_img(view, x0 + x, y0 + y, color);
		pixel_put_img(view, x0 + x, y0 - y, color);
		pixel_put_img(view, x0 - x, y0 + y, color);
		pixel_put_img(view, x0 - x, y0 - y, color);
		error = 2 * (delta + y) - 1;
		if ((delta < 0) && (error <= 0))
			delta += 2 * ++x + 1;
		else if ((delta > 0) && (error > 0))
			delta -= 2 * --y + 1;
		else
			delta += 2 * (++x - y--);
	}

}


void		intro(t_view *view)
{
	int		i;
	int		j;

	i = -1;
	while (++i < 70)
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
	circle(view, WIN_WIDTH / 2, WIN_HEIGHT / 2, 200, rgb_to_color(100, 0, 0));
	line(view, 0, 0, rgb_to_color(250, 0, 0), WIN_WIDTH, WIN_HEIGHT, rgb_to_color(250, 0, 0));
	line(view, 0, WIN_HEIGHT, rgb_to_color(250, 0, 0), WIN_WIDTH, 0, rgb_to_color(250, 0, 0));
	
	mlx_put_image_to_window(view->mlx_ptr, view->win_ptr, view->img.img_ptr, 0, 0);
	char *s = "PRESS ANY KEY";
	mlx_string_put(view->mlx_ptr, view->win_ptr, (WIN_WIDTH - ft_strlen(s) * ALPHA_WIDTH) / 2, (WIN_HEIGHT - ALPHA_HEIGHT) / 2, rgb_to_color(255, 255, 255), s);
	mlx_string_put(view->mlx_ptr, view->win_ptr, 50, 100, rgb_to_color(255, 255, 255), "ZOOM     : + -");
	mlx_string_put(view->mlx_ptr, view->win_ptr, 50, 120, rgb_to_color(255, 255, 255), "MOVE     : W A S D");
	mlx_string_put(view->mlx_ptr, view->win_ptr, 50, 140, rgb_to_color(255, 255, 255), "RELIEF   : PAGE UP / DOWN");
	mlx_string_put(view->mlx_ptr, view->win_ptr, WIN_WIDTH - 320, 100, rgb_to_color(255, 255, 255), "ROTATE X : ARROW UP / DOWN");
	mlx_string_put(view->mlx_ptr, view->win_ptr, WIN_WIDTH - 320, 120, rgb_to_color(255, 255, 255), "ROTATE Y : ARROW LEFT / RIGHT");
	mlx_string_put(view->mlx_ptr, view->win_ptr, WIN_WIDTH - 320, 140, rgb_to_color(255, 255, 255), "ROTATE Z : 1 2");
	mlx_string_put(view->mlx_ptr, view->win_ptr, WIN_WIDTH - 320, 580, rgb_to_color(255, 255, 255), "RESET    : BACKSPACE");
	mlx_string_put(view->mlx_ptr, view->win_ptr, WIN_WIDTH - 320, 600, rgb_to_color(255, 255, 255), "EXIT     : ESC");
	mlx_string_put(view->mlx_ptr, view->win_ptr, 50, 600, rgb_to_color(255, 255, 255), "HELP     : H"); // !
	
}


int			main(int args, char **argv)
{
	t_view	view;

	if (args != 2)
		error("usage: ./fdf [filename]");
	

	view = init(argv[1]);

	// pixel_put_img(&view, 100, 100, get_color(0, 0, 250));
	intro(&view);
	// draw(&view);

	mlx_hook(view.win_ptr, 2, 0, &key_hook, &view); // KEYS
	mlx_hook(view.win_ptr, 17, 0, exit_func, 0); // CLOSE
	
	mlx_loop(view.mlx_ptr);
	return (0);


}
