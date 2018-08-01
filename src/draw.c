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

// void		show_coord(t_view *view, t_vector **new_coord)
// {
// 	int i = -1;
// 	int j;
// 	while (++i < view->rows)
// 	{
// 		j = -1;
// 		while (++j < view->columns)
// 			printf("(%i,%i) x: %f y: %f z: %f\n", i, j, new_coord[i][j].x, new_coord[i][j].y, new_coord[i][j].z);
// 	}
// }


// void		delete_coord(t_view *view, t_vector **coord)
// {
// 	int			i;

// 	i = -1;
// 	while (++i < view->rows)
// 		free(coord[i]);
// 	free(coord);
// }

void	copy(t_vector **from, t_vector **where, int rows, int columns) // ?
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

	// t_vector	**new_coord;
	copy(view->base, view->mod, view->rows, view->columns);


	transformation(view);

	

	i = -1;
	while (++i < view->rows)
	{
		j = -1;
		while (++j < view->columns)
		{
			if (i < view->rows - 1)
				line(view, view->mod[i][j].x, view->mod[i][j].y, view->mod[i][j].color,
						view->mod[i + 1][j].x, view->mod[i + 1][j].y, view->mod[i + 1][j].color);
			if (j < view->columns - 1)
				line(view, view->mod[i][j].x, view->mod[i][j].y, view->mod[i][j].color,
						view->mod[i][j + 1].x, view->mod[i][j + 1].y, view->mod[i][j + 1].color);
		}
	}
	frame(view);

	
	// t_img *img = view->img;
	mlx_put_image_to_window(view->mlx_ptr, view->win_ptr, view->img.img_ptr, 0, 0);
	frame_labels(view);
	if (view->help)
		help(view);
	// delete_coord(view, new_coord);
}
