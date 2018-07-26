/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 18:01:23 by osamoile          #+#    #+#             */
/*   Updated: 2018/07/24 18:01:35 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_hook(int key, void *v)
{
	t_view		*view;
	
	view = (t_view*)v;
	if (key == KEY_ESC)
		exit(1);
	else if (key == KEY_LEFT)
		view->angleY += 10;
	else if (key == KEY_RIGHT)
		view->angleY -= 10;
	else if (key == KEY_UP)
		view->angleX -= 10;
	else if (key == KEY_DOWN)
		view->angleX += 10;
	else if (key == KEY_PLUS)
		view->zoom += 1;
	else if (key == KEY_MINUS)
	{
		view->zoom -= 1;
		if (view->zoom < 0)
			view->zoom = 0;
	}
	else if (key == KEY_W)
		view->translateY += 5;
	else if (key == KEY_S)
		view->translateY -= 5;
	else if (key == KEY_A)
		view->translateX += 5;
	else if (key == KEY_D)
		view->translateX -= 5;
	else if (key == KEY_ONE)
		view->angleZ += 10;
	else if (key == KEY_TWO)
		view->angleZ -= 10;
	else if (key == KEY_ARROW_UP)
		view->height -= 0.1;
	else if (key == KEY_ARROW_DOWN)
		view->height += 0.1;

	mlx_clear_window(view->mlx_ptr, view->win_ptr);
	draw(view);
	return (0);
}
