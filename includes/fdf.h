/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osamoile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 16:23:07 by osamoile          #+#    #+#             */
/*   Updated: 2018/06/12 16:24:39 by osamoile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"

# include <fcntl.h>
# include <math.h>
# include <stdio.h> // trash

# define X_AXIS 0
# define Y_AXIS 1
# define Z_AXIS 2

# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_W 13
# define KEY_A 0 // ???????????
# define KEY_S 1
# define KEY_D 2 // ?????????
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_ARROW_UP 116
# define KEY_ARROW_DOWN 121

# define WIN_HEIGHT 720
# define WIN_WIDTH 1280

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
	int		color;
}				t_vector;

typedef struct	s_view
{
	void		*mlx_ptr;
	void		*win_ptr;
	
	t_vector	**base;
	int			rows;
	int			columns;

	int				angleX;
	int				angleY;
	int				angleZ;
	int	zoom;
	float			height;
	int				translateX;
	int				translateY;
	
}				t_view;

void		line(t_view *view, int x0, int y0, int x1, int y1, int c);
int			key_hook(int key, void *v);
void		draw(t_view *view);

// t_vector	**copy(t_view *view); // ?
// void		zoom(t_view *view, t_vector **coord);
// void		heigth(t_view *view, t_vector **coord);
int			get_color(unsigned char red, unsigned char green, unsigned char blue);

void		transformation(t_view *view, t_vector **coord);
// void		rotate(t_view *view, t_vector **coord, int axis, int angle);
// void		translate(t_view *view, t_vector **coord);

t_view		init(char *file);

void		error(char *message);


#endif
