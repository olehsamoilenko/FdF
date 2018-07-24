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

void		print_lines(t_view *view)
{
	int		i;
	int		j;

	t_vector	**new_coord;


	new_coord = copy(view);
	
	heigth(view, new_coord, view->height);
	rotate_all(view, new_coord);
	
	
	
	zoom(view, new_coord, view->zoom);


	i = -1;
	while (++i < view->rows)
	{
		j = -1;
		while (++j < view->columns)
		{
			if (i < view->rows - 1)
				line(view, (int)new_coord[i][j].x + WIDTH / 2, (int)new_coord[i][j].y + HEIGHT / 2,
							(int)new_coord[i + 1][j].x + WIDTH / 2, (int)new_coord[i + 1][j].y + HEIGHT / 2,
							color(255, 0, 0));
			if (j < view->columns - 1)
				line(view, (int)new_coord[i][j].x + WIDTH / 2, (int)new_coord[i][j].y + HEIGHT / 2,
							(int)new_coord[i][j + 1].x + WIDTH / 2, (int)new_coord[i][j + 1].y + HEIGHT / 2,
							color(255, 0, 0));
		}
	}
}
