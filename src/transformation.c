/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 11:33:58 by osamoile          #+#    #+#             */
/*   Updated: 2018/07/25 11:34:12 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vector	rotate_dot(t_view *view, t_vector dot)
{
	t_vector	tmp;
	float		x;
	float		y;
	float		z;

	x = view->angle_x * M_PI / 180;
	y = view->angle_y * M_PI / 180;
	z = view->angle_z * M_PI / 180;
	tmp.x = (cos(y) * cos(z)) * dot.x +
			(-cos(y) * sin(z)) * dot.y +
			(sin(y)) * dot.z;
	tmp.y = (sin(x) * sin(y) * cos(z) + cos(x) * sin(z)) * dot.x +
			(cos(x) * cos(z) - sin(x) * sin(y) * sin(z)) * dot.y +
			(-sin(x) * cos(y)) * dot.z;
	tmp.z = (sin(x) * sin(z) - cos(x) * sin(y) * cos(z)) * dot.x +
			(cos(x) * sin(y) * sin(z) + sin(x) * cos(z)) * dot.y +
			(cos(x) * cos(y)) * dot.z;
	return (tmp);
}

void			transformation(t_view *view)
{
	int			j;
	int			i;
	t_vector	tmp;

	i = -1;
	while (++i < view->rows)
	{
		j = -1;
		while (++j < view->columns)
		{
			view->mod[i][j].z *= view->height;
			tmp = rotate_dot(view, view->mod[i][j]);
			view->mod[i][j].x = view->zoom * (tmp.x + view->move_x)
				+ WIN_WIDTH / 2;
			view->mod[i][j].y = view->zoom * (tmp.y + view->move_y)
				+ WIN_HEIGHT / 2;
			view->mod[i][j].z = tmp.z;
		}
	}
}
