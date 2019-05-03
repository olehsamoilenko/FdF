/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 17:26:19 by osamoile          #+#    #+#             */
/*   Updated: 2018/06/11 17:26:58 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	exit_func(void)
{
	exit(1);
}

int			main(int args, char **argv)
{
	t_view	view;

	if (args != 2)
		error("usage: ./fdf [filename]");
	view = init(argv[1]);
	intro(&view);
	mlx_hook(view.win_ptr, EVENT_KEY_PRESS, EVENT_KEY_RELEASE, &key_hook, &view);
	mlx_hook(view.win_ptr, EVENT_CLOSE, 0, &exit_func, 0);
	mlx_loop(view.mlx_ptr);
	return (0);
}
