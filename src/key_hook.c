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
	if (key == ESC)
		exit(1);
	else if (key == LEFT)
		view->angleY += 10;
	else if (key == RIGHT)
		view->angleY -= 10;
	else if (key == UP)
		view->angleX -= 10;
	else if (key == DOWN)
		view->angleX += 10;
	else if (key == PLUS)
		view->zoom += 1;
	else if (key == MINUS)
		view->zoom -= 1;
	else if (key == W)
		view->height -= 0.1;
	else if (key == S)
		view->height += 0.1;
	else if (key == ONE)
		view->angleZ += 10;
	else if (key == TWO)
		view->angleZ -= 10;
	mlx_clear_window(view->mlx_ptr, view->win_ptr);
	print_lines(view);
	return (0);
}
