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

void		delete_coord(t_view *view, t_vector **coord)
{
	int			i;

	i = -1;
	while (++i < view->rows)
		free(coord[i]);
	free(coord);
}

t_vector	**copy(t_view *view) // ?
{
	int			i;
	int			j;
	t_vector	**coord;

	coord = (t_vector**)ft_memalloc(sizeof(t_vector*) * view->rows);
	i = -1;
	while (++i < view->rows)
	{
		
		coord[i] = (t_vector*)ft_memalloc(sizeof(t_vector) * view->columns);
		j = -1;
		while (++j < view->columns)
			coord[i][j] = view->base[i][j];
	}
	return (coord);
}



void		draw(t_view *view)
{
	int		i;
	int		j;

	t_vector	**new_coord;
	new_coord = copy(view);

	transformation(view, new_coord);

	

	i = -1;
	while (++i < view->rows)
	{
		j = -1;
		while (++j < view->columns)
		{
			if (i < view->rows - 1)
				line(view, new_coord[i][j].x, new_coord[i][j].y,
						new_coord[i + 1][j].x, new_coord[i + 1][j].y,
						new_coord[i][j].color);
			if (j < view->columns - 1)
				line(view, new_coord[i][j].x, new_coord[i][j].y,
						new_coord[i][j + 1].x, new_coord[i][j + 1].y,
						new_coord[i][j].color);
		}
	}
	// mlx_put_image_to_window(view->mlx_ptr, view->win_ptr, view->img->img_ptr, 0, 0);
	delete_coord(view, new_coord);
}
