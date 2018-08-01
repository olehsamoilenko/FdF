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

// # define X_AXIS 0
// # define Y_AXIS 1
// # define Z_AXIS 2

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
# define KEY_BACKSPACE 51
# define KEY_H 4
# define WIN_HEIGHT 720
# define WIN_WIDTH 1280

# define ALPHA_HEIGHT 22
# define ALPHA_WIDTH 10

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
	int		color;
}				t_vector;

typedef struct	s_img
{
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	char		*img;
	char		*img_ptr;
}				t_img;

typedef struct	s_view
{
	void		*mlx_ptr;
	void		*win_ptr;


	t_vector	**base;
	t_vector	**mod;

	int			rows;
	int			columns;

	int			angleX;
	int			angleY;
	int			angleZ;
	int			zoom;
	float		height;
	int			moveX;
	int			moveY;

	t_img		img; // !

	int			help;

}				t_view;



void		line(t_view *view, int x0, int y0, int color0, int x1, int y1, int color1);
int			key_hook(int key, void *v);
void		draw(t_view *view);

// int			get_color(unsigned char red, unsigned char green, unsigned char blue);
void		transformation(t_view *view);

t_view		init(char *file);
void		default_settings(t_view *view);
int			rgb_to_color(unsigned char red, unsigned char green, unsigned char blue);

void		pixel_put_img(t_view *view, int x, int y, int color);

void		error(char *message);

void		help(t_view *view);
void		frame(t_view *view);
void		frame_labels(t_view *view);


#endif
