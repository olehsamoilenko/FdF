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

// void		zoom(t_view *view, t_vector **coord)
// {
// 	int		i;
// 	int		j;

// 	if (view->zoom < 0)
// 		view->zoom = 0;
// 	i = -1;
// 	while (++i < view->rows)
// 	{
// 		j = -1;
// 		while (++j < view->columns)
// 		{
// 			coord[i][j].x *= view->zoom;
// 			coord[i][j].y *= view->zoom;
// 		}
// 	}
// }

// void		heigth(t_view *view, t_vector **coord)
// {
// 	int		i;
// 	int		j;

// 	i = -1;
// 	while (++i < view->rows)
// 	{
// 		j = -1;
// 		while (++j < view->columns)
// 		{
// 			coord[i][j].z = view->base[i][j].z * view->height;
// 		}
// 	}
// }

// void		translate(t_view *view, t_vector **coord)
// {
// 	int		i;
// 	int		j;

// 	i = -1;
// 	while (++i < view->rows)
// 	{
// 		j = -1;
// 		while (++j < view->columns)
// 		{
// 			coord[i][j].x += view->translateX;
// 			coord[i][j].y += view->translateY;
// 		}
// 	}
// }




int			main(int args, char **argv)
{
	if (args != 2)
		error("usage: ./fdf [filename]");
	

	t_view	view = init(argv[1]);

	draw(&view);

	mlx_hook(view.win_ptr, 2, 0, &key_hook, &view); // KEYS
	mlx_hook(view.win_ptr, 17, 0, exit_func, 0); // CLOSE
	
	mlx_loop(view.mlx_ptr);
	return (0);


}
