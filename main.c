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

#include "mlx.h"
#include <unistd.h> //trash
#define MIN_GREEN 256
#define MIN_RED 65536

int			color(int red, int green, int blue)
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

int			main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		x;
	int		y;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx!!!");
	x = 200;
	while (x++ < 300)
	{
		y = 200;
		while (y++ < 300)
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, color(100, 0, 0));
	}
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
	
	// color(0, 0, 0);
	// color(1, 1, 1);
	// color(255, 1, 255);
	return (0);


}
