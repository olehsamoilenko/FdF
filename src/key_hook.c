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

void	error(char *message)
{
	ft_putendl(message);
	exit(0);
}

int		key_hook(int key, void *v)
{
	t_view		*view;

	view = (t_view*)v;
	key == KEY_ESC ? exit(1) : 0;
	key == KEY_LEFT ? view->angle_y += 10 : 0;
	key == KEY_RIGHT ? view->angle_y -= 10 : 0;
	key == KEY_UP ? view->angle_x -= 10 : 0;
	key == KEY_DOWN ? view->angle_x += 10 : 0;
	key == KEY_ONE ? view->angle_z -= 10 : 0;
	key == KEY_TWO ? view->angle_z += 10 : 0;
	key == KEY_PLUS ? view->zoom += 1 : 0;
	key == KEY_MINUS && view->zoom != 0 ? view->zoom -= 1 : 0;
	key == KEY_W ? view->move_y += 1 + view->rows / 50 : 0;
	key == KEY_S ? view->move_y -= 1 + view->rows / 50 : 0;
	key == KEY_A ? view->move_x += 1 + view->rows / 50 : 0;
	key == KEY_D ? view->move_x -= 1 + view->rows / 50 : 0;
	key == KEY_ARROW_UP ? view->height -= 0.1 : 0;
	key == KEY_ARROW_DOWN ? view->height += 0.1 : 0;
	key == KEY_BACKSPACE ? default_settings(view) : 0;
	key == KEY_H ? view->help = (view->help + 1) % 2 : 0;
	ft_bzero(view->img.img, WIN_WIDTH * WIN_HEIGHT * view->img.bits_per_pixel);
	draw(view);
	return (0);
}
