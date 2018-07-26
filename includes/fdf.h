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

# define ESC 53
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define W 13
# define A 0 // ???????????
# define S 1
# define D 2 // ?????????
# define ONE 18
# define TWO 19
# define PLUS 24
# define MINUS 27
# define ARROW_UP 116
# define ARROW_DOWN 121

# define HEIGHT 800
# define WIDTH 1500

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
	int		color;
}				t_vector;

// typedef struct	s_params
// {
// 	int			angleX;
// 	int			angleY;
// 	int			angleZ;
// 	int			zoom;
// 	float		height;
// }				t_params;

typedef struct	s_view
{
	void		*mlx_ptr;
	void		*win_ptr;
	
	t_vector	**base;
	int			rows;
	int			columns;

	int			angleX;
	int			angleY;
	int			angleZ;
	int			zoom;
	float		height;
	int			translateX;
	int			translateY;
	
}				t_view;

void		line(t_view *view, int x0, int y0, int x1, int y1, int c);
int			key_hook(int key, void *v);
void		draw(t_view *view);

t_vector	**copy(t_view *view); // ?
void		zoom(t_view *view, t_vector **coord, int zoom);
void		heigth(t_view *view, t_vector **coord);
int			get_color(unsigned char red, unsigned char green, unsigned char blue);

void		rotate_all(t_view *view, t_vector **coord);
void		rotate(t_view *view, t_vector **coord, int axis, int angle);
void		translate(t_view *view, t_vector **coord);

t_view		init(char *file);

void		error(char *message);


#endif
