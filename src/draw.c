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

void		draw(t_view *view)
{
	int		i;
	int		j;

	t_vector	**new_coord;


	new_coord = copy(view);

	// heigth(view, new_coord);
	
	
	transformation(view, new_coord);
	// rotate(view, new_coord, X_AXIS, view->angleX);
	// rotate(view, new_coord, Y_AXIS, view->angleY);
	// rotate(view, new_coord, Z_AXIS, view->angleZ);

	// zoom(view, new_coord);
	// translate(view, new_coord);
	

	int color;
	i = -1;
	while (++i < view->rows)
	{
		j = -1;
		while (++j < view->columns)
		{
			
			if (i < view->rows - 1)
			{
				line(view, new_coord[i][j].x, new_coord[i][j].y,
						new_coord[i + 1][j].x, new_coord[i + 1][j].y,
						new_coord[i][j].color);

			}
			if (j < view->columns - 1)
			{
				line(view, new_coord[i][j].x, new_coord[i][j].y,
						new_coord[i][j + 1].x, new_coord[i][j + 1].y,
						new_coord[i][j].color);

			}
		}
	}
}
