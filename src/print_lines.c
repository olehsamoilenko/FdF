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

void		show_coord(t_view *view, t_vector **new_coord)
{
	int i = -1;
	int j;
	while (++i < view->rows)
	{
		j = -1;
		while (++j < view->columns)
			printf("(%i,%i) x: %f y: %f z: %f\n", i, j, new_coord[i][j].x, new_coord[i][j].y, new_coord[i][j].z);
	}
}

void		print_lines(t_view *view)
{
	int		i;
	int		j;

	t_vector	**new_coord;


	new_coord = copy(view);
	// printf("copy\n"); show_coord(view, new_coord);
	heigth(view, new_coord);
	// printf("heigth\n"); show_coord(view, new_coord);
	// rotate_all(view, new_coord);
	rotate(view, new_coord, X_AXIS, view->angleX);
	rotate(view, new_coord, Y_AXIS, view->angleY);
	rotate(view, new_coord, Z_AXIS, view->angleZ);
	// printf("rotate\n"); show_coord(view, new_coord);
	
	
	
	zoom(view, new_coord, view->zoom);

	int color;
	i = -1;
	while (++i < view->rows)
	{
		j = -1;
		while (++j < view->columns)
		{
			
			if (i < view->rows - 1)
			{
				if (view->base[i][j].z == 0 && view->base[i + 1][j].z == 0)
					color = get_color(255, 0, 0);
				else
					color = get_color(255, 255, 255);
				// if (view->base[i][j].z == 0)
					line(view, (int)new_coord[i][j].x + WIDTH / 2, (int)new_coord[i][j].y + HEIGHT / 2,
								(int)new_coord[i + 1][j].x + WIDTH / 2, (int)new_coord[i + 1][j].y + HEIGHT / 2,
								color);
				// else
				// 	line(view, (int)new_coord[i][j].x + WIDTH / 2, (int)new_coord[i][j].y + HEIGHT / 2,
				// 				(int)new_coord[i + 1][j].x + WIDTH / 2, (int)new_coord[i + 1][j].y + HEIGHT / 2,
				// 				color(255, 255, 255));
			}
			if (j < view->columns - 1)
			{
				if (view->base[i][j].z == 0 && view->base[i][j + 1].z == 0)
					color = get_color(255, 0, 0);
				else
					color = get_color(255, 255, 255);
				// if (view->base[i][j].z == 0)
					line(view, (int)new_coord[i][j].x + WIDTH / 2, (int)new_coord[i][j].y + HEIGHT / 2,
								(int)new_coord[i][j + 1].x + WIDTH / 2, (int)new_coord[i][j + 1].y + HEIGHT / 2,
								color);
				// else
					// line(view, (int)new_coord[i][j].x + WIDTH / 2, (int)new_coord[i][j].y + HEIGHT / 2,
					// 			(int)new_coord[i][j + 1].x + WIDTH / 2, (int)new_coord[i][j + 1].y + HEIGHT / 2,
					// 			color(255, 255, 255));
			}
		}
	}
}
