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

void		transformation(t_view *view, t_vector **coord)
{
	int		j;
	int		i;
	double	tmp[3];
	float	angle;

	float x = view->angleX * M_PI / 180;
	float y = view->angleY * M_PI / 180;
	float z = view->angleZ * M_PI / 180;
	i = -1;
	while (++i < view->rows)
	{
		j = -1;
		while (++j < view->columns)
		{

			coord[i][j].z *= view->height;
			tmp[0] =	(cos(y) * cos(z)) * coord[i][j].x +
						(-cos(y) * sin(z)) * coord[i][j].y +
						(sin(y)) * coord[i][j].z;
			tmp[1] =	(sin(x) * sin(y) * cos(z) + cos(x) * sin(z)) * coord[i][j].x +
						(cos(x) * cos(z) - sin(x) * sin(y) * sin(z)) * coord[i][j].y +
						(-sin(x) * cos(y)) * coord[i][j].z;
			tmp[2] =	(sin(x) * sin(z) - cos(x) * sin(y) * cos(z)) * coord[i][j].x +
						(cos(x) * sin(y) * sin(z) + sin(x) * cos(z)) * coord[i][j].y +
						(cos(x) * cos(y)) * coord[i][j].z;
			coord[i][j].x = tmp[0] * view->zoom + view->translateX;
			coord[i][j].y = tmp[1] * view->zoom + view->translateY;
			coord[i][j].z = tmp[2];

		}
	}

}

// void		rotate(t_view *view, t_vector **coord, int axis, int angle)
// {
// 	float	a;
// 	int		i;
// 	int		j;
// 	double	tmp[3];

// 	a = angle * M_PI / 180;
// 	i = -1;
// 	while (++i < view->rows)
// 	{
// 		j = -1;
// 		while (++j < view->columns)
// 		{
// 			if (axis == X_AXIS)
// 			{
// 				tmp[0] = coord[i][j].x;
// 				tmp[1] = coord[i][j].y * cos(a) - coord[i][j].z * sin(a);
// 				tmp[2] = coord[i][j].y * sin(a) + coord[i][j].z * cos(a);
// 			}
// 			else if (axis == Y_AXIS)
// 			{
// 				tmp[0] = coord[i][j].z * sin(a) + coord[i][j].x * cos(a);
// 				tmp[1] = coord[i][j].y;
// 				tmp[2] = coord[i][j].z * cos(a) - coord[i][j].x * sin(a);
				
// 			}
// 			else if (axis == Z_AXIS)
// 			{
// 				tmp[0] = coord[i][j].x * cos(a) - coord[i][j].y * sin(a);
// 				tmp[1] = coord[i][j].x * sin(a) + coord[i][j].y * cos(a);
// 				tmp[2] = coord[i][j].z;
// 			}
// 			coord[i][j].x = tmp[0];
// 			coord[i][j].y = tmp[1];
// 			coord[i][j].z = tmp[2];
// 		}
// 	}
	
// }




			// angle = view->angleX * M_PI / 180;
			// tmp[0] = coord[i][j].x;
			// tmp[1] = coord[i][j].y * cos(angle) - coord[i][j].z * sin(angle);
			// tmp[2] = coord[i][j].y * sin(angle) + coord[i][j].z * cos(angle);
			// // tmp[0] = rot_all[0][0] * coord[j][i].x + rot_all[0][1] *
			// // 			coord[j][i].y + rot_all[0][2] * coord[j][i].z;
			// // tmp[1] = rot_all[1][0] * coord[j][i].x + rot_all[1][1] *
			// // 			coord[j][i].y + rot_all[1][2] * coord[j][i].z;
			// // tmp[2] = rot_all[2][0] * coord[j][i].x + rot_all[2][1] *
			// // 			coord[j][i].y + rot_all[2][2] * coord[j][i].z;
			// coord[i][j].x = tmp[0];
			// coord[i][j].y = tmp[1];
			// coord[i][j].z = tmp[2];

			// angle = view->angleY * M_PI / 180;
			// tmp[0] = coord[i][j].z * sin(angle)+ coord[i][j].x * cos(angle);
			// tmp[1] = coord[i][j].y;
			// tmp[2] = coord[i][j].z * cos(angle) - coord[i][j].x * sin(angle);
			// coord[i][j].x = tmp[0];
			// coord[i][j].y = tmp[1];
			// coord[i][j].z = tmp[2];

			// angle = view->angleZ * M_PI / 180;
			// tmp[0] = coord[i][j].x * cos(angle) - coord[i][j].y * sin(angle);
			// tmp[1] = coord[i][j].x * sin(angle) + coord[i][j].y * cos(angle);
			// tmp[2] = coord[i][j].z;
