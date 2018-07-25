/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 11:33:58 by osamoile          #+#    #+#             */
/*   Updated: 2018/07/25 11:34:12 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		rotate(t_view *view, t_vector **coord, int axis, int angle)
{
	float	a;
	int		i;
	int		j;
	double	tmp[3];

	a = angle * M_PI / 180;
	i = -1;
	while (++i < view->rows)
	{
		j = -1;
		while (++j < view->columns)
		{
			if (axis == X_AXIS)
			{
				tmp[0] = coord[i][j].x;
				tmp[1] = coord[i][j].y * cos(a) - coord[i][j].z * sin(a);
				tmp[2] = coord[i][j].y * sin(a) + coord[i][j].z * cos(a);
			}
			else if (axis == Y_AXIS)
			{
				tmp[0] = coord[i][j].z * sin(a) + coord[i][j].x * cos(a);
				tmp[1] = coord[i][j].y;
				tmp[2] = coord[i][j].z * cos(a) - coord[i][j].x * sin(a);
				
			}
			else if (axis == Z_AXIS)
			{
				tmp[0] = coord[i][j].x * cos(a) - coord[i][j].y * sin(a);
				tmp[1] = coord[i][j].x * sin(a) + coord[i][j].y * cos(a);
				tmp[2] = coord[i][j].z;
			}
			coord[i][j].x = tmp[0];
			coord[i][j].y = tmp[1];
			coord[i][j].z = tmp[2];
		}
	}
	
}

// void		rotate_all(t_view *view, t_vector **coord)
// {
// 	int		x;
// 	int		y;
// 	double	tmp[3];
// 	double	rot_all[3][3];

// 	matrix_init(view, rot_all);
// 	y = -1;
// 	while (++y < view->rows)
// 	{
// 		x = -1;
// 		while (++x < view->columns)
// 		{
// 			tmp[0] = 
// 			// tmp[0] = rot_all[0][0] * coord[y][x].x + rot_all[0][1] *
// 			// 			coord[y][x].y + rot_all[0][2] * coord[y][x].z;
// 			// tmp[1] = rot_all[1][0] * coord[y][x].x + rot_all[1][1] *
// 			// 			coord[y][x].y + rot_all[1][2] * coord[y][x].z;
// 			// tmp[2] = rot_all[2][0] * coord[y][x].x + rot_all[2][1] *
// 			// 			coord[y][x].y + rot_all[2][2] * coord[y][x].z;
// 			coord[y][x].x = tmp[0];
// 			coord[y][x].y = tmp[1];
// 			coord[y][x].z = tmp[2];
// 		}
// 	}
// }
